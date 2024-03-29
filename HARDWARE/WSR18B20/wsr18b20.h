#ifndef __WSR18B20_H__
#define __WSR18B20_H__

#include "1602.h"

//IO方向设置
#define DS18B20_IO_IN()  {GPIOA->CRL&=0xF0FFFFFF;GPIOA->CRL|=0x08000000;}
#define DS18B20_IO_OUT() {GPIOA->CRL&=0xF0FFFFFF;GPIOA->CRL|=0x03000000;}
////IO操作函数											   
#define	DS18B20_DQ_OUT PAout(6) //数据端口
#define	DS18B20_DQ_IN  PAin(6)  //数据端口
   	
u8 DS18B20_Init(void);			//初始化DS18B20
short DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20    


#endif



