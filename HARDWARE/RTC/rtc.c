//RTC事实时钟初始化

#include "rtc.h"
#include "sys.h"
#include "delay.h"


//初始化时间定义
u8 time_buf[8] = {20,17,01,01,15,55,50,02};


//运用DS1302当实时时钟/////////////////////////////////////////

//DS1302初始化
void DS_IIC_Init(void)
{
   RCC->APB2ENR |= 1<<3;//开启GPIOA的时钟

	GPIOB->CRH &= 0xFFFF00FF;//复位PB11 10
	GPIOB->CRH |= 0x00003300;
   GPIOB->CRL &= 0xFFFFFF0F;//复位PB1
	GPIOB->CRL |= 0x00000030;
	DS1302_DATA_OUT=1;
	DS1302_RST=0;
	DS1302_SCK=0;
}

//向DS1302写入一个字节数据
void DS1302_Write_Byte(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr & 0xFE;  //最低位置零，写数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)DS1302_DATA_OUT = 1;
		else DS1302_DATA_OUT = 0;
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //写数据
	{
	  if(data & 0x01)DS1302_DATA_OUT = 1;
		else DS1302_DATA_OUT = 0;
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //停止DS1302总线
}

//从DS1302读出一个字节数据
u8 DS1302_Read_Byte(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr | 0x01;  //最低位置高，读数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01) DS1302_DATA_OUT = 1;
		else DS1302_DATA_OUT = 0;
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //读数据
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN) temp |= 0x80;
		else temp &= 0x7F;
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //停止DS1302总线
	return temp;
}

//向DS1302写入时间数据
void DS1302_Write_Time(void)
{
	u8 data[8];
	u8 i;
	
	//转成bcd录入
	for(i=0; i<8; i++)
	{
		data[i] = ((time_buf[i]/10)<<4) | (time_buf[i]%10);
	}
	
  DS1302_Write_Byte(ds1302_control_add, 0x00);      //关闭写保护
  DS1302_Write_Byte(ds1302_sec_add, 0x80);          //暂停时钟
	
	DS1302_Write_Byte(ds1302_year_add,	data[1]);		//年 
	DS1302_Write_Byte(ds1302_month_add,	data[2]);	//月 
	DS1302_Write_Byte(ds1302_date_add,	data[3]);		//日 
	DS1302_Write_Byte(ds1302_hr_add,		data[4]);		  //时 
	DS1302_Write_Byte(ds1302_min_add,		data[5]);		//分
	DS1302_Write_Byte(ds1302_sec_add,		data[6]);		//秒
	//DS1302_Write_Byte(ds1302_day_add,		data[7]);		//周 
	DS1302_Write_Byte(ds1302_control_add,0x80);		    //打开写保护 
}

//从DS302读出时钟数据
void DS1302_Read_Time(void)  
{
	u8 i,time=0;
	time_buf[1] = DS1302_Read_Byte(ds1302_year_add);		   //年 
	time_buf[2] = DS1302_Read_Byte(ds1302_month_add);		   //月 
	time_buf[3] = DS1302_Read_Byte(ds1302_date_add);		   //日 
	time_buf[4] = DS1302_Read_Byte(ds1302_hr_add);		     //时 
	time_buf[5] = DS1302_Read_Byte(ds1302_min_add);		     //分 
	time_buf[6] = (DS1302_Read_Byte(ds1302_sec_add))&0x7f; //秒，屏蔽秒的第7位，避免超出59
	time_buf[7] = DS1302_Read_Byte(ds1302_day_add);		     //周 	
	for(i=1;i<8;i++)
	{
		time = time_buf[i];
		time_buf[i] = (time/16*10)+(time%16);
	}
}
