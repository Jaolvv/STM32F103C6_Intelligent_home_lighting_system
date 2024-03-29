#ifndef __DELAY_H__
#define __DELAY_H__

#include "overall.h"


void delay_Init( u8 SYSCLK );//delay延迟初始化
void delay_us( u32 nus );//微秒级的延迟
void delay_ms( u32 nms );//毫秒级的延迟




#endif
