//RTC��ʵʱ�ӳ�ʼ��

#include "rtc.h"
#include "sys.h"
#include "delay.h"


//��ʼ��ʱ�䶨��
u8 time_buf[8] = {20,17,01,01,15,55,50,02};


//����DS1302��ʵʱʱ��/////////////////////////////////////////

//DS1302��ʼ��
void DS_IIC_Init(void)
{
   RCC->APB2ENR |= 1<<3;//����GPIOA��ʱ��

	GPIOB->CRH &= 0xFFFF00FF;//��λPB11 10
	GPIOB->CRH |= 0x00003300;
   GPIOB->CRL &= 0xFFFFFF0F;//��λPB1
	GPIOB->CRL |= 0x00000030;
	DS1302_DATA_OUT=1;
	DS1302_RST=0;
	DS1302_SCK=0;
}

//��DS1302д��һ���ֽ�����
void DS1302_Write_Byte(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //ֹͣDS1302����
	delay_us(10);
	DS1302_RST = 1;      //����DS1302����
	addr = addr & 0xFE;  //���λ���㣬д����
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //д��ַ
	{
	  if (addr & 0x01)DS1302_DATA_OUT = 1;
		else DS1302_DATA_OUT = 0;
		DS1302_SCK = 1;    //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //д����
	{
	  if(data & 0x01)DS1302_DATA_OUT = 1;
		else DS1302_DATA_OUT = 0;
		DS1302_SCK = 1;   //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //ֹͣDS1302����
}

//��DS1302����һ���ֽ�����
u8 DS1302_Read_Byte(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //ֹͣDS1302����
	delay_us(10);
	DS1302_RST = 1;      //����DS1302����
	addr = addr | 0x01;  //���λ�øߣ�������
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //д��ַ
	{
	  if (addr & 0x01) DS1302_DATA_OUT = 1;
		else DS1302_DATA_OUT = 0;
		DS1302_SCK = 1;    //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //������
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN) temp |= 0x80;
		else temp &= 0x7F;
		DS1302_SCK = 1;   //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //ֹͣDS1302����
	return temp;
}

//��DS1302д��ʱ������
void DS1302_Write_Time(void)
{
	u8 data[8];
	u8 i;
	
	//ת��bcd¼��
	for(i=0; i<8; i++)
	{
		data[i] = ((time_buf[i]/10)<<4) | (time_buf[i]%10);
	}
	
  DS1302_Write_Byte(ds1302_control_add, 0x00);      //�ر�д����
  DS1302_Write_Byte(ds1302_sec_add, 0x80);          //��ͣʱ��
	
	DS1302_Write_Byte(ds1302_year_add,	data[1]);		//�� 
	DS1302_Write_Byte(ds1302_month_add,	data[2]);	//�� 
	DS1302_Write_Byte(ds1302_date_add,	data[3]);		//�� 
	DS1302_Write_Byte(ds1302_hr_add,		data[4]);		  //ʱ 
	DS1302_Write_Byte(ds1302_min_add,		data[5]);		//��
	DS1302_Write_Byte(ds1302_sec_add,		data[6]);		//��
	//DS1302_Write_Byte(ds1302_day_add,		data[7]);		//�� 
	DS1302_Write_Byte(ds1302_control_add,0x80);		    //��д���� 
}

//��DS302����ʱ������
void DS1302_Read_Time(void)  
{
	u8 i,time=0;
	time_buf[1] = DS1302_Read_Byte(ds1302_year_add);		   //�� 
	time_buf[2] = DS1302_Read_Byte(ds1302_month_add);		   //�� 
	time_buf[3] = DS1302_Read_Byte(ds1302_date_add);		   //�� 
	time_buf[4] = DS1302_Read_Byte(ds1302_hr_add);		     //ʱ 
	time_buf[5] = DS1302_Read_Byte(ds1302_min_add);		     //�� 
	time_buf[6] = (DS1302_Read_Byte(ds1302_sec_add))&0x7f; //�룬������ĵ�7λ�����ⳬ��59
	time_buf[7] = DS1302_Read_Byte(ds1302_day_add);		     //�� 	
	for(i=1;i<8;i++)
	{
		time = time_buf[i];
		time_buf[i] = (time/16*10)+(time%16);
	}
}
