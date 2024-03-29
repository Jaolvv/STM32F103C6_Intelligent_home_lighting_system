#include "sys.h"
#include "delay.h"
#include "lcd1602.h"
#include "usart.h"
#include "stdio.h"
#include "dh11.h"

#define key1 PBin(15)
#define key2 PBin(14)
#define key3 PBin(13)
#define key4 PBin(12)


//指示灯
#define LED0	PCout(13)	//状态灯

#define IN1		PAin(2)		//红外

#define LED2	PAout(0)		//黄色
#define LED1	PAout(1)		//白色
//数值
u32 data2[5];
u32 Kdssj=0; //开定时间

 u32 S=0;
u32 LW=0;

//接收数据
u8 U2data=0;
void USART1_IRQHandler(void)
{
	if(USART1->SR&(1<<5))	//接收到数据
	{
		U2data = USART1->DR;//读取数据x
		switch(U2data)
      {
         case 'A':LED1=1;break; //打开白色灯光
         case 'B':LED1=0;LED2=0;break; //打开白色,黄色灯光
         case 'C':if(LED1==1){ LED2=1;LED1=0;}else {LED2=0;LED1=1;} break; //灯光调节
      }
	}
}

void show(void)
{

   LCD1602_ShowNmber( 3,0,Kdssj,5);
   if(S==1)LCD1602_Show(13,0,"ON ");else LCD1602_Show(13,0,"OFF");

}


int main( void )
{
	u32 data_time=0;	//系统运行的时间
   u8 X=0;
   
	//系统时钟设置
	Stm32_Clock_Init(9);
	//延时初始化
	delay_Init(72);
	//IO重定义
	RCC->APB2ENR |= 1<<0;//打开复用功能时钟
	AFIO->MAPR |= 1<<25;
	delay_ms(100);
   
   
	RCC->APB2ENR |= 1<<2;//打开PA时钟
	RCC->APB2ENR |= 1<<3;//打开PB时钟
	RCC->APB2ENR |= 1<<4;//打开PC时钟
	GPIOA->CRL &= 0xFFFFF000;//复位PA6 7
	GPIOA->CRL |= 0x00000833;
	GPIOA->CRH &= 0xFFFFFFFF;//复位PA
	GPIOA->CRH |= 0x00000000;
	GPIOB->CRL &= 0xFFFFFFFF;//复位PB0 1
	GPIOB->CRL |= 0x00000000;
	GPIOB->CRH &= 0x0000FFFF;//复位PB15 14 13 12
	GPIOB->CRH |= 0x88880000;
	GPIOC->CRH &= 0xFF0FFFFF;//复位PC13
	GPIOC->CRH |= 0x00300000;
	PBout(15)=1; PBout(14)=1; PBout(13)=1; PBout(12)=1;
	LED0=1;	LED1=0; LED2=0;//关闭LED0
	
   //LCS1602
   LCD1602_Init();
   //串口1初始化 
	USART1_Init(72,9600);
   
   LCD1602_Show(0,0,"TIM00000  DS:OFF   "); //定时  定时的开启/关闭
   LCD1602_Show(0,1,"                   "); //

	while(1)
	{
		//周期时间
		delay_ms(1);
		data_time++;

		if(data_time%500==0)
		{
          //设置特定时间，打开灯光
         if( Kdssj!=0 && S==1)
         {
           
            Kdssj--;
            
            if( Kdssj==0 && (IN1==0 || IN1==1))
            {
               LED1=1;
                
               
            }
         } 
         if(S==1) //定时之后灯光打开，红外如果被触发再被不触发就关灯
         {
            if(IN1==0 && X==0 && Kdssj==0)
            {
               
              if( LED1==1){ LED1=1;LED2=0;}else if(LED2==1){LED2=1;LED1=0;}X=1; 
            } else if(IN1==1 && X==1&& S==1 )
            {
               LED1=0;LED2=0;S=0;X=0;
            }
         }

        

         show();
		}

      
      
      
		//按键1 选择
		if( key1==0 )
		{
			delay_ms(5);
			if( key1==0 )
			{
            Kdssj+=5;
             show();
            while(key1==0);
			}
		}
		
		//按键2 增加
		if( key2==0 )
		{
			delay_ms(5);
			if( key2==0)
			{
            Kdssj-=5;
             show();
				while(key2==0);
			}
		}
		
		//按键3 减少
		if( key3==0 )
		{
			delay_ms(5);
			if( key3==0 )
			{
            if( LED2==1)
            {
               LED1=1; 
               LED2=0;
            }else
            {
               LED1=0;  LED2=1;
            }          
				while(key3==0);
			}
		}
		
      
      //按键4 联网
		if( key4==0 )
		{
			delay_ms(5);
			if( key4==0 )
			{
            S=!S;
				while(key4==0);
			}
		}
	}
}



