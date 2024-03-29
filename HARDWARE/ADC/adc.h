#ifndef __ADC_H__
#define __ADC_H__
#include "sys.h"


void ADC1_Init(void);//ADC1初始化
//ADC1通道0数据采集输出
u16 ADC1_CH0gather(u8 ch);
void ADC1_INtemperture( void );//ADC读取内部温度值初始化


#endif

