#include "IIC.h"
#include "delay.h"


void I2C_GPIO_Config(void)
{
	RCC->APB2ENR|=1<<2;//ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<3;//ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<4;//ʹ��PORTCʱ��
	
	GPIOB->CRH &= 0xFFFFFF00;
	GPIOB->CRH |= 0x00000033;//PB8 9
	GPIOB->CRL &= 0x0FFFFFFF;
	GPIOB->CRL |= 0x30000000;//PB7
	
	GPIOB->ODR |= 1<<7;
	GPIOB->ODR |= 1<<8;
	GPIOB->ODR |= 1<<7;
}


////////IIC��ʼ����//////////
u8 I2C_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	return 0;
}


//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}


//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	


//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
}


//����ACKӦ��
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

//������ACKӦ��		    
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

//IIC����һ���ֽ�
//���شӻ�����Ӧ��	  
void IIC_Send_Byte(u8 txd)
{                        
	u8 t;   
	SDA_OUT(); 	    
	IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
	{              
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
	}	 
} 	


//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


//��IIC�豸д��һ���ֽ�����
u8 Single_WriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 data)
{
	
	//��ʼ�ź�
	I2C_Start();

	IIC_Send_Byte(Slave_Address);   //�����豸��ַ+д�ź�
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	IIC_Send_Byte(data);       //�ڲ��Ĵ������ݣ�
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
		
	IIC_Stop();   //����ֹͣ�ź�
		
	return SET;
}


u8 Single_MWriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length)
{
	//��ʼ�ź�
	I2C_Start();         

	IIC_Send_Byte(Slave_Address);   //�����豸��ַ+д�ź�
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
	while(length)
	{
		IIC_Send_Byte(*data++);       //�ڲ��Ĵ������ݣ�
		if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
		length--;
	}
	IIC_Stop();   //����ֹͣ�ź�
	return SET;
}


//**************************************
//��IIC�豸��ȡһ���ֽ�����
//**************************************
u8 Single_ReadI2C(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length)
{
	//��ʼ�ź�
	I2C_Start();               
	 
	IIC_Send_Byte(Slave_Address);    //�����豸��ַ+д�ź�
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	IIC_Send_Byte(REG_Address);     //���ʹ洢��Ԫ��ַ
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	//��ʼ�ź�
	I2C_Start();            

	IIC_Send_Byte(Slave_Address+1);  //�����豸��ַ+���ź�
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	while(length-1)
	{
		*REG_data++=IIC_Read_Byte(1);       //�����Ĵ�������
		length--;
	}
	*REG_data=IIC_Read_Byte(0);  //����ֹͣ�����ź�
	IIC_Stop();                    //ֹͣ�ź�
	return SET;
}



