#ifndef __DAC_H__
#define __DAC_H__
#include "sys.h"

//DMA��ʼ��
//DMA_CHxΪDMAͨ��DMA1_Channelx CPA
//CPARΪ�����ַ CMARΪ�洢����ַ CNDTRΪ����������
void MYDMA_Init( DMA_Channel_TypeDef *DMA_CHx, u32 CPAR, u32 CMAR, u32 CNDTR );

//����һ��DMA����
void DMA_Enable( DMA_Channel_TypeDef *DMA_CHx );

#endif
