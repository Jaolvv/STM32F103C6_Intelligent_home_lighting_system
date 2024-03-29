#ifndef __WSR18B20_H__
#define __WSR18B20_H__

#include "1602.h"

//IO��������
#define DS18B20_IO_IN()  {GPIOA->CRL&=0xF0FFFFFF;GPIOA->CRL|=0x08000000;}
#define DS18B20_IO_OUT() {GPIOA->CRL&=0xF0FFFFFF;GPIOA->CRL|=0x03000000;}
////IO��������											   
#define	DS18B20_DQ_OUT PAout(6) //���ݶ˿�
#define	DS18B20_DQ_IN  PAin(6)  //���ݶ˿�
   	
u8 DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    


#endif



