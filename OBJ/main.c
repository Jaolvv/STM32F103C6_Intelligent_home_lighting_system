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


//ָʾ��
#define LED0	PCout(13)	//״̬��

#define IN1		PAin(2)		//����

#define LED2	PAout(0)		//��ɫ
#define LED1	PAout(1)		//��ɫ
//��ֵ
u32 data2[5];
u32 Kdssj=0; //����ʱ��

 u32 S=0;
u32 LW=0;

//��������
u8 U2data=0;
void USART1_IRQHandler(void)
{
	if(USART1->SR&(1<<5))	//���յ�����
	{
		U2data = USART1->DR;//��ȡ����x
		switch(U2data)
      {
         case 'A':LED1=1;break; //�򿪰�ɫ�ƹ�
         case 'B':LED1=0;LED2=0;break; //�򿪰�ɫ,��ɫ�ƹ�
         case 'C':if(LED1==1){ LED2=1;LED1=0;}else {LED2=0;LED1=1;} break; //�ƹ����
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
	u32 data_time=0;	//ϵͳ���е�ʱ��
   u8 X=0;
   
	//ϵͳʱ������
	Stm32_Clock_Init(9);
	//��ʱ��ʼ��
	delay_Init(72);
	//IO�ض���
	RCC->APB2ENR |= 1<<0;//�򿪸��ù���ʱ��
	AFIO->MAPR |= 1<<25;
	delay_ms(100);
   
   
	RCC->APB2ENR |= 1<<2;//��PAʱ��
	RCC->APB2ENR |= 1<<3;//��PBʱ��
	RCC->APB2ENR |= 1<<4;//��PCʱ��
	GPIOA->CRL &= 0xFFFFF000;//��λPA6 7
	GPIOA->CRL |= 0x00000833;
	GPIOA->CRH &= 0xFFFFFFFF;//��λPA
	GPIOA->CRH |= 0x00000000;
	GPIOB->CRL &= 0xFFFFFFFF;//��λPB0 1
	GPIOB->CRL |= 0x00000000;
	GPIOB->CRH &= 0x0000FFFF;//��λPB15 14 13 12
	GPIOB->CRH |= 0x88880000;
	GPIOC->CRH &= 0xFF0FFFFF;//��λPC13
	GPIOC->CRH |= 0x00300000;
	PBout(15)=1; PBout(14)=1; PBout(13)=1; PBout(12)=1;
	LED0=1;	LED1=0; LED2=0;//�ر�LED0
	
   //LCS1602
   LCD1602_Init();
   //����1��ʼ�� 
	USART1_Init(72,9600);
   
   LCD1602_Show(0,0,"TIM00000  DS:OFF   "); //��ʱ  ��ʱ�Ŀ���/�ر�
   LCD1602_Show(0,1,"                   "); //

	while(1)
	{
		//����ʱ��
		delay_ms(1);
		data_time++;

		if(data_time%500==0)
		{
          //�����ض�ʱ�䣬�򿪵ƹ�
         if( Kdssj!=0 && S==1)
         {
           
            Kdssj--;
            
            if( Kdssj==0 && (IN1==0 || IN1==1))
            {
               LED1=1;
                
               
            }
         } 
         if(S==1) //��ʱ֮��ƹ�򿪣���������������ٱ��������͹ص�
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

      
      
      
		//����1 ѡ��
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
		
		//����2 ����
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
		
		//����3 ����
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
		
      
      //����4 ����
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



