#include "IIC.h"
#include "delay.h"


void I2C_GPIO_Config(void)
{
	RCC->APB2ENR|=1<<2;//使能PORTA时钟
	RCC->APB2ENR|=1<<3;//使能PORTB时钟
	RCC->APB2ENR|=1<<4;//使能PORTC时钟
	
	GPIOB->CRH &= 0xFFFFFF00;
	GPIOB->CRH |= 0x00000033;//PB8 9
	GPIOB->CRL &= 0x0FFFFFFF;
	GPIOB->CRL |= 0x30000000;//PB7
	
	GPIOB->ODR |= 1<<7;
	GPIOB->ODR |= 1<<8;
	GPIOB->ODR |= 1<<7;
}


////////IIC起始函数//////////
u8 I2C_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
	return 0;
}


//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}


//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	


//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
}


//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}	

//IIC发送一个字节
//返回从机有无应答	  
void IIC_Send_Byte(u8 txd)
{                        
	u8 t;   
	SDA_OUT(); 	    
	IIC_SCL=0;//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{              
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
	}	 
} 	


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


//向IIC设备写入一个字节数据
u8 Single_WriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 data)
{
	
	//起始信号
	I2C_Start();

	IIC_Send_Byte(Slave_Address);   //发送设备地址+写信号
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	IIC_Send_Byte(REG_Address);    //内部寄存器地址，
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	IIC_Send_Byte(data);       //内部寄存器数据，
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
		
	IIC_Stop();   //发送停止信号
		
	return SET;
}


u8 Single_MWriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length)
{
	//起始信号
	I2C_Start();         

	IIC_Send_Byte(Slave_Address);   //发送设备地址+写信号
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	IIC_Send_Byte(REG_Address);    //内部寄存器地址，
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	while(length)
	{
		IIC_Send_Byte(*data++);       //内部寄存器数据，
		if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
		length--;
	}
	IIC_Stop();   //发送停止信号
	return SET;
}


//**************************************
//从IIC设备读取一个字节数据
//**************************************
u8 Single_ReadI2C(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length)
{
	//起始信号
	I2C_Start();               
	 
	IIC_Send_Byte(Slave_Address);    //发送设备地址+写信号
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	IIC_Send_Byte(REG_Address);     //发送存储单元地址
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	//起始信号
	I2C_Start();            

	IIC_Send_Byte(Slave_Address+1);  //发送设备地址+读信号
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	while(length-1)
	{
		*REG_data++=IIC_Read_Byte(1);       //读出寄存器数据
		length--;
	}
	*REG_data=IIC_Read_Byte(0);  //发送停止传输信号
	IIC_Stop();                    //停止信号
	return SET;
}



