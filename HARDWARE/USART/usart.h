#ifndef __USART_H__
#define __USART_H__

#include "sys.h"

extern u8 USART_PRINTF;
void USART1_Init(u32 pclk2, u32 bound);//����1��ʼ��
void USART1_Txdata( u8 *data );//����һ���ַ�
void USART1_Txnumber(u32 number);//USART1����ascll���͵�����
void USART2_Init(u32 pclk2, u32 bound);//����2��ʼ��
//����2����len���ȵ�����
void USART2_Txdata( u16 len, u8 *data );

//����1����len���ȵ�����
void USART1_TxBuf( u16 len, u8 *data );

#endif
