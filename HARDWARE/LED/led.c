#include "sys.h"
#include "led.h"


//LED��ʼ������
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;//ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<3;//ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<4;//ʹ��PORTCʱ��
	
	GPIOC->CRH|=3<<20;//����PC13��ģʽ
	GPIOC->ODR|=1<<13;//PB13 �����
	GPIOA->CRH|=3<<0;//����PA8
	PAout(8)=1;//�ر�ָʾ��
	//������
	GPIOB->CRH|=3<<8;//����PB10
	PBout(10)=1;//�رշ�����
}


void KEY_Init( void )
{
	RCC->APB2ENR|=1<<2;//ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<3;//ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<4;//ʹ��PORTCʱ��
	GPIOA->CRH&=0xFFF00FFF;//��λPA11 12
	GPIOA->CRH|=0x00088000;//��������ģʽ
	PAout(11) = 1;
	PAout(12) = 1;
}


