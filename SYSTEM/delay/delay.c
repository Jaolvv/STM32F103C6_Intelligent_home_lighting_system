//系统延迟函数设置
#include "sys.h"

static u8 fac_us=0;//每个us需要的systick时钟数
static u16 fac_ms=0;//每个ms需要的systick时钟数


//delay延迟初始化
void delay_Init( u8 SYSCLK )
{
	SysTick->CTRL&=~(1<<2);//设置systick的时钟源
	fac_us=SYSCLK/8;//算出一个US要多少SYSTICK的钟数
	fac_ms=(u16)fac_us*1000;//算出每个ms需要的systick时钟数
}


//微秒级的延迟
void delay_us( u32 nus )
{
	u32 temp;
	SysTick->LOAD = nus*fac_us;//将时间加载到systick里面去
	SysTick->VAL=0x00;//清空systick计数器
	SysTick->CTRL=0x01;//开始倒数
	do
	{
		temp=SysTick->CTRL;//读取计到的次数
	}while( (temp&0x01)&&!(temp&(1<<16)));//判断等待时间是否到达
	SysTick->CTRL=0x00;//关闭计数器
	SysTick->VAL =0X00;//清空计数器
}


//毫秒级的延迟
//注: SysTick->LOAD为24位寄存器,所以,最大延时为:nms<=0xffffff*8*1000/SYSCLK 对168M条件下,nms<=798ms 
void delay_ms( u32 nms )
{
	u32 temp;		   
	SysTick->LOAD = (u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;//清空计数器
	SysTick->CTRL = 0x01;//开始倒数
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;//关闭计数器
	SysTick->VAL =0X00;//清空计数器	 
}




