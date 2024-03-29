#ifndef __DH11_H__
#define __DH11_H__

#include "sys.h"

extern u8 TMP_Data;//�¶�
extern u8 HUM_Data;//ʪ��

//IO�ڷ���
#define dht11_gpio_input()	{GPIOB->CRH &=  0xFFFFF0FF; GPIOB->CRH |= 0x00000800; }//����ģʽ
#define dht11_gpio_output() {GPIOB->CRH &= 0xFFFFF0FF; GPIOB->CRH |= 0x00000300; }//���ģʽ

//IO�ڲ�������
#define DHT11_OUT	PBout(10)
#define DHT11_IN	PBin(10)


void DH11_Init( void );//��ʼ��
void dht11_reset(void);//��ʼ�ź�
u16 dht11_read_bit(void);//��ȡһλ
u16 dht11_read_byte(void);//��ȡһ���ֽ� 8λ
u16 dht11_read_data(void);//��ȡ����


#endif
