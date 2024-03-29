#ifndef __DAC_H__
#define __DAC_H__
#include "sys.h"

//DMA初始化
//DMA_CHx为DMA通道DMA1_Channelx CPA
//CPAR为外设地址 CMAR为存储器地址 CNDTR为传输数据量
void MYDMA_Init( DMA_Channel_TypeDef *DMA_CHx, u32 CPAR, u32 CMAR, u32 CNDTR );

//开启一次DMA传输
void DMA_Enable( DMA_Channel_TypeDef *DMA_CHx );

#endif
