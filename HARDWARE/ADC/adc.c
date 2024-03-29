#include "adc.h"
#include "sys.h"
#include "delay.h"


//ADC1初始化
void ADC1_Init(void)
{
	RCC->APB2ENR |= 1<<2;//打开PA的时钟
	RCC->APB2ENR |= 1<<9;//打开ADC1的时钟
	RCC->APB2RSTR |= 1<<9;//ADC1复位
	RCC->APB2RSTR &= ~(1<<9);//ADC1复位结束
	GPIOA->CRL &= 0xFFFFFFF0;//PA0设置成模拟输入模式
	RCC->CFGR &= ~(3<<14);//ADC分频清0
	RCC->CFGR |= 1<<15;//设置ADC频率为12WHZ
	
	ADC1->CR1 &= ~(0xf<<16);//ADC模式清除
	ADC1->CR1 |= 0<<16;//ADC1使用独立模式
	ADC1->CR1 &= ~(1<<8);//非扫描模式
	ADC1->CR2 &= ~(1<<1);//单次转换模式
	ADC1->CR2 &= ~(0x7<<17);//清楚转换触发控制
	ADC1->CR2 |= 0x7<<17;//软件控制转换
	ADC1->CR2 |= 1<<20;//使用外部启动转换
	ADC1->CR2 &= ~(1<<11);//数据向右对齐
	ADC1->SQR1 &= ~(0xF<<20);//规则通道长度 只通道1转换 ADC1_IN0

	ADC1->SMPR2&=~(3*0);   //通道0采样时间清空	  
 	ADC1->SMPR2|=7<<(3*0); //通道0  239.5周期,提高采样时间可以提高精确度	 
	
//	ADC1->SMPR2&=~(3*1);   //通道1采样时间清空	  
// 	ADC1->SMPR2|=7<<(3*1); //通道1  239.5周期,提高采样时间可以提高精确度	 
	
//	ADC1->SMPR2&=~(3*2);   //通道2采样时间清空	  
// 	ADC1->SMPR2|=7<<(3*2); //通道2  239.5周期,提高采样时间可以提高精确度	 
	
	ADC1->CR2 |= 1;//唤醒AD1转换
	ADC1->CR2 |= 1<<3;//使能复位校准
	while(ADC1->CR2&(1<<3));//等待校验结束
	ADC1->CR2 |= 1<<2;//开启AD校验
	while(ADC1->CR2&(1<<2));//等待AD校验结束
}


//ADC1通道0数据采集输出
u16 ADC1_CH0gather(u8 ch)
{
	ADC1->SQR3 &= 0XFFFFFFE0;//执行通道1清除
	ADC1->SQR3 |= ch;//设置在第一个通道
	ADC1->CR2 |= 1<<22;//开始转换规则通道
	while(!(ADC1->SR&(1<<1)));//等待转换结束
	return ADC1->DR;//数据输出
}


//ADC读取内部温度值初始化
void ADC1_INtemperture( void )
{
	RCC->APB2ENR |= 1<<9;//打开ADC1的时钟
	RCC->APB2RSTR |= 1<<9;//开启ADC1的接口复位
	RCC->APB1RSTR &= ~(1<<9);//关闭ADC1的接口复位
	RCC->CFGR &= ~(3<<14);//清除ADC预分频位
	RCC->CFGR |= 2<<14;//6分频后ADC频率为12MHZ
	
	ADC1->CR1 &= 0XF0FFFF;//ADC双模式位清除
	ADC1->CR1 |= 0<<16;//开启独立模式
	ADC1->CR2 &= ~(1<<1);//非连续转换模式
	ADC1->CR1 &= ~(1<<8);//关闭扫描模式
	ADC1->CR2 &= ~(7<<17);
	ADC1->CR2 |= 7<<17;//软件触发转换
	ADC1->CR2 |= (1<<20);//使用外部事件启动转换
	ADC1->CR2 &= ~(1<<11);//开启数据右对齐
	
	ADC1->CR2 |= (1<<23);//使能内部温度传感器
	
	ADC1->SQR1 &= ~(0xF<<20);//清除规则通道转换序列长度
	ADC1->SQR1 |= 0<<20;//设置规则转换通道转换序列长度为1
	
	ADC1->SMPR1 &= ~(7<<18);//清除内部温度传感器的采样时间
	ADC1->SMPR1 |= 7<<18;//设置通道16内部温度传感器采样周期为41.5
	
	ADC1->SMPR2&=~(3*0);   //通道0采样时间清空	  
 	ADC1->SMPR2|=7<<(3*0); //通道0  239.5周期,提高采样时间可以提高精确度	 
	
	ADC1->SMPR2&=~(3*1);   //通道1采样时间清空	  
 	ADC1->SMPR2|=7<<(3*1); //通道1  239.5周期,提高采样时间可以提高精确度	 
	
	ADC1->SMPR2&=~(3*2);   //通道2采样时间清空	  
 	ADC1->SMPR2|=7<<(3*2); //通道2  239.5周期,提高采样时间可以提高精确度	 
	
	ADC1->CR2 |= 1;//开AD转换
	ADC1->CR2 |= 1<<3;//开启ADC1的复位
	while(ADC1->CR2&1<<3);//判断复位有没有结束
	ADC1->CR2 |= 1<<2;//开启ADC1的校准
	while(ADC1->CR2&1<<2);//判断ADC1的校准有没有结束

}


////ADC1_2外部中断
//void ADC1_2_IRQHandler(void)
//{
//	float data;
//	u16 data2;u8 integer;
//	
//	USART1_Txdata("ADC IN OK");
//	if(ADC1->SR&(1<<1))//转换完成呢
//	{
//		data = ADC1->DR;
//		data = data*(3.3/4096);//得到电压值
//		integer = data;//得到整数部分
//		data -= integer;
//		data2 = data*100;
//		USART1_Txnumber(integer);USART1_Txdata(".");USART1_Txnumber(data2);USART1_Txdata("V");
//	}
//	ADC1->SR &= ~(1<<1);//清除转换完成标志位
//






