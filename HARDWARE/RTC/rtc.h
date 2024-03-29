#ifndef __RTC_H__
#define __RTC_H__

#include "sys.h"

extern u8 time_buf[8];

//DS1302��ַ����
#define ds1302_sec_add			  0x80		//�����ݵ�ַ
#define ds1302_min_add			  0x82		//�����ݵ�ַ
#define ds1302_hr_add			    0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			  0x86		//�����ݵ�ַ
#define ds1302_month_add		  0x88		//�����ݵ�ַ
#define ds1302_day_add			  0x8a		//�������ݵ�ַ
#define ds1302_year_add			  0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

//����DS1307��ʵʱʱ��//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DS1302_IO_IN()  {GPIOB->CRH&=0xFFFFF0FF;GPIOB->CRH|=0x00000800;}
#define DS1302_IO_OUT() {GPIOB->CRH&=0xFFFFF0FF;GPIOB->CRH|=0x00000300;}

#define DS1302_RST				PBout(11) 	//CS
#define DS1302_SCK				PBout(1) 		//SCL
#define DS1302_DATA_OUT		PBout(10) 	//SDA	 
#define DS1302_DATA_IN		PBin(10)  	//����SDA

void DS_IIC_Init(void);
void DS1302_Write_Byte(u8 addr, u8 data);
u8 DS1302_Read_Byte(u8 addr);
void DS1302_Write_Time(void);
void DS1302_Read_Time(void);
#endif





