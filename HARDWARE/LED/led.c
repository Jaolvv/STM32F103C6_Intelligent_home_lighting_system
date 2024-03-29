#include "sys.h"
#include "led.h"


//LED初始化函数
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;//使能PORTA时钟
	RCC->APB2ENR|=1<<3;//使能PORTB时钟
	RCC->APB2ENR|=1<<4;//使能PORTC时钟
	
	GPIOC->CRH|=3<<20;//配置PC13的模式
	GPIOC->ODR|=1<<13;//PB13 输出高
	GPIOA->CRH|=3<<0;//配置PA8
	PAout(8)=1;//关闭指示灯
	//蜂鸣器
	GPIOB->CRH|=3<<8;//配置PB10
	PBout(10)=1;//关闭蜂鸣器
}


void KEY_Init( void )
{
	RCC->APB2ENR|=1<<2;//使能PORTA时钟
	RCC->APB2ENR|=1<<3;//使能PORTB时钟
	RCC->APB2ENR|=1<<4;//使能PORTC时钟
	GPIOA->CRH&=0xFFF00FFF;//复位PA11 12
	GPIOA->CRH|=0x00088000;//设置输入模式
	PAout(11) = 1;
	PAout(12) = 1;
}


