#ifndef __USART_H__
#define __USART_H__

#include "sys.h"

extern u8 USART_PRINTF;
void USART1_Init(u32 pclk2, u32 bound);//串口1初始化
void USART1_Txdata( u8 *data );//发送一串字符
void USART1_Txnumber(u32 number);//USART1发送ascll类型的数字
void USART2_Init(u32 pclk2, u32 bound);//串口2初始化
//串口2发送len长度的数据
void USART2_Txdata( u16 len, u8 *data );

//串口1发送len长度的数据
void USART1_TxBuf( u16 len, u8 *data );

#endif
