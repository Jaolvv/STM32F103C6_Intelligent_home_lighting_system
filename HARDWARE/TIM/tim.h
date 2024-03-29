#ifndef __TIM_H__
#define __TIM_H__
#include "sys.h"

void TIM2_Init(u16 ARR, u16 PSC);//定时器2初始化
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc);

//TIM2 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr,u16 psc);

#endif
