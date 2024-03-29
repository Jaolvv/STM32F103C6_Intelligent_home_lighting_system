#include "dma.h"
#include "sys.h"
#include "delay.h"


u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度


//DMA初始化
//DMA_CHx为DMA通道DMA1_Channelx CPA
//CPAR为外设地址 CMAR为存储器地址 CNDTR为传输数据量
void MYDMA_Init( DMA_Channel_TypeDef *DMA_CHx, u32 CPAR, u32 CMAR, u32 CNDTR )
{
	RCC->AHBENR |= 1;//开启DMA时钟
	delay_ms(5);//等待DMA稳定
	
	DMA_CHx->CPAR = CPAR;//外设地址
	DMA_CHx->CMAR = CMAR;//存储器地址
	DMA1_MEM_LEN = CNDTR;//传输数据量
	DMA_CHx->CNDTR = CNDTR;//传输数据量
	DMA_CHx->CCR = 0;//复位配置
	DMA_CHx->CCR |= 0<<1;//传输所以中断事件不开启
	DMA_CHx->CCR |= 1<<4;//传输方向 从存储器读
	DMA_CHx->CCR |= 0<<5;//非循环模式
	DMA_CHx->CCR |= 0<<6;//外设地址非增量
	DMA_CHx->CCR |= 1<<7;//存储器地址增量
	DMA_CHx->CCR |= 0<<8;//8位外设数据宽度
	DMA_CHx->CCR |= 0<<10;//8位存储器数据宽度
	DMA_CHx->CCR |= 2<<12;//数据优先级为中
	DMA_CHx->CCR |= 0<<14;//非存储器到存储器模式
}


//开启一次DMA传输
void DMA_Enable( DMA_Channel_TypeDef *DMA_CHx )
{
	DMA_CHx->CCR &= ~1;//关闭DMA传输
	DMA_CHx->CNDTR = DMA1_MEM_LEN;//传输数据量
	DMA_CHx->CCR |= 1;//开启DMA传输
}




