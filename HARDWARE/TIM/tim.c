#include "sys.h"
#include "tim.h"
#include "led.h"
#include "usart.h"
#include "led.h"


//��ʱ������ʼ��
void TIM2_Init(u16 ARR, u16 PSC)
{
	//RCC->APB1RSTR |= 1;
	RCC->APB1ENR |= 1;//tim2ʱ��ʹ��
	TIM2->ARR = ARR;//��װ
	TIM2->PSC = PSC;//��Ƶ
	TIM2->DIER |= 1<<6;//�����жϸ���
	TIM2->CR1 |= 1;//������ʱ��
	MY_NVIC_Init(1,2,TIM2_IRQn,2);//��ռ2�������ȼ�2����2
}

//��ʱ�����жϴ�����
void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001)//����ж�
	{
		
		
	}
	TIM2->SR &= ~(1<<0);//������λ
}


//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
	RCC->APB2ENR|=1<<3;	//ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<2;	//ʹ��PORTAʱ��
	GPIOA->CRL&=0XF0FFFFFF;	//PA6 7���
	GPIOA->CRL|=0X0B000000;	//���ù������
//	GPIOB->CRL&=0XFFFFFF00;	//PB0 1���
//	GPIOB->CRL|=0X000000BB;	//���ù������

	TIM3->ARR=arr;			//�趨�������Զ���װֵ 
	TIM3->PSC=psc;			//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM1ģʽ		 
	TIM3->CCMR1|=1<<3;	//CH1Ԥװ��ʹ��	   
	TIM3->CCER|=1<<0;   //OC1 ���ʹ��
	
	TIM3->CCMR1|=6<<12;	//CH2 PWM1ģʽ		 
	TIM3->CCMR1|=1<<11;	//CH2Ԥװ��ʹ��	   
	TIM3->CCER|=1<<4;		//OC2 ���ʹ��
	
	TIM3->CCMR2|=6<<4;	//CH3 PWM1ģʽ		 
	TIM3->CCMR2|=1<<3;	//CH3Ԥװ��ʹ��	   
	TIM3->CCER|=1<<8;		//OC3 ���ʹ��
	
	TIM3->CCMR2|=6<<12;	//CH4 PWM1ģʽ		 
	TIM3->CCMR2|=1<<11;	//CH4Ԥװ��ʹ��	   
	TIM3->CCER|=1<<12;	//OC4 ���ʹ��
	
	TIM3->CR1=0x0080;   	//ARPEʹ�� 
	TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��3 											  
}


//TIM2 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;			//TIM2ʱ��ʹ��    
	RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��	
//	GPIOA->CRL&=0XFFFF0000;	//P0 1 2 3
//	GPIOA->CRL|=0X0000BBBB;	//���ù������ 	  	
	GPIOA->CRL&=0XFFFFFFF0;	//PA0 1 2
	GPIOA->CRL|=0X0000000B;	//���ù������ 	  	

	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ������Ƶ
	
	TIM2->CCMR1|=6<<4;  //CH1 PWM1ģʽ		 
	TIM2->CCMR1|=1<<3;	//CH1Ԥװ��ʹ��	   
	TIM2->CCER|=1<<0;   //OC1 ���ʹ��
	
//	TIM2->CCMR1|=6<<12;	//CH2 PWM1ģʽ		 
//	TIM2->CCMR1|=1<<11;	//CH2Ԥװ��ʹ��	   
//	TIM2->CCER|=1<<4;		//OC2 ���ʹ��
//	
//	TIM2->CCMR2|=6<<4;	//CH3 PWM1ģʽ		 
//	TIM2->CCMR2|=1<<3;	//CH3Ԥװ��ʹ��	   
//	TIM2->CCER|=1<<8;		//OC3 ���ʹ��
	
//	TIM2->CCMR2|=6<<12;	//CH4 PWM1ģʽ		 
//	TIM2->CCMR2|=1<<11;	//CH4Ԥװ��ʹ��	   
//	TIM2->CCER|=1<<12;	//OC4 ���ʹ��
  
	TIM2->CR1=0x0080;   	//ARPEʹ�� 
	TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��2											  
} 


