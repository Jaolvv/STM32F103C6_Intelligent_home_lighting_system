#include "sys.h"
#include "tim.h"
#include "led.h"
#include "usart.h"
#include "led.h"


//定时器二初始化
void TIM2_Init(u16 ARR, u16 PSC)
{
	//RCC->APB1RSTR |= 1;
	RCC->APB1ENR |= 1;//tim2时钟使能
	TIM2->ARR = ARR;//重装
	TIM2->PSC = PSC;//分频
	TIM2->DIER |= 1<<6;//允许中断更新
	TIM2->CR1 |= 1;//开启定时器
	MY_NVIC_Init(1,2,TIM2_IRQn,2);//抢占2，子优先级2，组2
}

//定时器二中断处理函数
void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001)//溢出中断
	{
		
		
	}
	TIM2->SR &= ~(1<<0);//清除标记位
}


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
	RCC->APB2ENR|=1<<3;	//使能PORTB时钟
	RCC->APB2ENR|=1<<2;	//使能PORTA时钟
	GPIOA->CRL&=0XF0FFFFFF;	//PA6 7输出
	GPIOA->CRL|=0X0B000000;	//复用功能输出
//	GPIOB->CRL&=0XFFFFFF00;	//PB0 1输出
//	GPIOB->CRL|=0X000000BB;	//复用功能输出

	TIM3->ARR=arr;			//设定计数器自动重装值 
	TIM3->PSC=psc;			//预分频器不分频
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM1模式		 
	TIM3->CCMR1|=1<<3;	//CH1预装载使能	   
	TIM3->CCER|=1<<0;   //OC1 输出使能
	
	TIM3->CCMR1|=6<<12;	//CH2 PWM1模式		 
	TIM3->CCMR1|=1<<11;	//CH2预装载使能	   
	TIM3->CCER|=1<<4;		//OC2 输出使能
	
	TIM3->CCMR2|=6<<4;	//CH3 PWM1模式		 
	TIM3->CCMR2|=1<<3;	//CH3预装载使能	   
	TIM3->CCER|=1<<8;		//OC3 输出使能
	
	TIM3->CCMR2|=6<<12;	//CH4 PWM1模式		 
	TIM3->CCMR2|=1<<11;	//CH4预装载使能	   
	TIM3->CCER|=1<<12;	//OC4 输出使能
	
	TIM3->CR1=0x0080;   	//ARPE使能 
	TIM3->CR1|=0x01;    	//使能定时器3 											  
}


//TIM2 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;			//TIM2时钟使能    
	RCC->APB2ENR|=1<<2;    	//使能PORTA时钟	
//	GPIOA->CRL&=0XFFFF0000;	//P0 1 2 3
//	GPIOA->CRL|=0X0000BBBB;	//复用功能输出 	  	
	GPIOA->CRL&=0XFFFFFFF0;	//PA0 1 2
	GPIOA->CRL|=0X0000000B;	//复用功能输出 	  	

	TIM2->ARR=arr;			//设定计数器自动重装值 
	TIM2->PSC=psc;			//预分频器不分频
	
	TIM2->CCMR1|=6<<4;  //CH1 PWM1模式		 
	TIM2->CCMR1|=1<<3;	//CH1预装载使能	   
	TIM2->CCER|=1<<0;   //OC1 输出使能
	
//	TIM2->CCMR1|=6<<12;	//CH2 PWM1模式		 
//	TIM2->CCMR1|=1<<11;	//CH2预装载使能	   
//	TIM2->CCER|=1<<4;		//OC2 输出使能
//	
//	TIM2->CCMR2|=6<<4;	//CH3 PWM1模式		 
//	TIM2->CCMR2|=1<<3;	//CH3预装载使能	   
//	TIM2->CCER|=1<<8;		//OC3 输出使能
	
//	TIM2->CCMR2|=6<<12;	//CH4 PWM1模式		 
//	TIM2->CCMR2|=1<<11;	//CH4预装载使能	   
//	TIM2->CCER|=1<<12;	//OC4 输出使能
  
	TIM2->CR1=0x0080;   	//ARPE使能 
	TIM2->CR1|=0x01;    	//使能定时器2											  
} 


