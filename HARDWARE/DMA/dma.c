#include "dma.h"
#include "sys.h"
#include "delay.h"


u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ���


//DMA��ʼ��
//DMA_CHxΪDMAͨ��DMA1_Channelx CPA
//CPARΪ�����ַ CMARΪ�洢����ַ CNDTRΪ����������
void MYDMA_Init( DMA_Channel_TypeDef *DMA_CHx, u32 CPAR, u32 CMAR, u32 CNDTR )
{
	RCC->AHBENR |= 1;//����DMAʱ��
	delay_ms(5);//�ȴ�DMA�ȶ�
	
	DMA_CHx->CPAR = CPAR;//�����ַ
	DMA_CHx->CMAR = CMAR;//�洢����ַ
	DMA1_MEM_LEN = CNDTR;//����������
	DMA_CHx->CNDTR = CNDTR;//����������
	DMA_CHx->CCR = 0;//��λ����
	DMA_CHx->CCR |= 0<<1;//���������ж��¼�������
	DMA_CHx->CCR |= 1<<4;//���䷽�� �Ӵ洢����
	DMA_CHx->CCR |= 0<<5;//��ѭ��ģʽ
	DMA_CHx->CCR |= 0<<6;//�����ַ������
	DMA_CHx->CCR |= 1<<7;//�洢����ַ����
	DMA_CHx->CCR |= 0<<8;//8λ�������ݿ��
	DMA_CHx->CCR |= 0<<10;//8λ�洢�����ݿ��
	DMA_CHx->CCR |= 2<<12;//�������ȼ�Ϊ��
	DMA_CHx->CCR |= 0<<14;//�Ǵ洢�����洢��ģʽ
}


//����һ��DMA����
void DMA_Enable( DMA_Channel_TypeDef *DMA_CHx )
{
	DMA_CHx->CCR &= ~1;//�ر�DMA����
	DMA_CHx->CNDTR = DMA1_MEM_LEN;//����������
	DMA_CHx->CCR |= 1;//����DMA����
}




