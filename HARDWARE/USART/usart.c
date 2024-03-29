//�������ú���
//����1��������λ��ͨ�Ų�����Ϊ115200δʹ��DMA
//����2��������Ļͨ�Ų�����Ϊ9600 ʹ����DMA�ķ���

#include "usart.h"
#include "sys.h"
#include "led.h"
#include "stdio.h"	 


u8 RX2_Data=0;//����2���յ�������


//����1��ʼ��
void USART1_Init(u32 pclk2, u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
	mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬���� 
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж� 
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(2,2,USART1_IRQn,2);//��2��������ȼ�
}


//USART1����ascll���͵�����
//dataΪ�ַ������׵�ַ
void USART1_Txdata( u8 *data )
{
	u8 i=0;
	while(data[i] != '\0')
	{
		USART1->DR = data[i];//����һ���ֽ�
		while( (USART1->SR&0x40)==0);//�ȴ��������
		i++;
	}
}


//USART1����ascll���͵�����
//number��Ҫд�������
void USART1_Txnumber(u32 number)
{
	u32 data=1;
	u8 bit;
	if(number<=0)
	{
		USART1->DR='0';
		while((USART1->SR&0x40)==0);
		return;
	}
	while(number>=data)data*=10;//���㳤��
	while(1)
	{
		data /= 10;
		bit = number/data;
		number %= data;
		USART1->DR=bit+'0';
		while((USART1->SR&0x40)==0);
		if(data==1)return;
	}
}


//����2����len���ȵ�����
void USART2_Txdata( u16 len, u8 *data )
{
	u16 i=0;
	
	for( i=0; i<len; i++ )
	{
		USART2->DR = data[i];//����һ���ֽ�
		while( (USART2->SR&0x40)==0);//�ȴ��������
	}
}
 


//����2��ʼ�� PA2ΪTx PA3ΪRx
void USART2_Init(u32 pclk1, u32 bound)
{
	float temp;
	u16 integer;//usartdiv����
	u16 decimal;//usartdivС��
	
	RCC->APB1ENR |= 1<<17;//��������2��ʱ��
	RCC->APB1RSTR |= 1<<17;//����USART2��λ
	RCC->APB1RSTR &= ~(1<<17);//�ر�USART2��λ
	RCC->APB2ENR |= 1<<2;//����GPIOA��ʱ��
	
	GPIOA->CRL &= ~(0xF<<8);//��λPA2������
	GPIOA->CRL &= ~(0xF<<12);//��λPA3������
	GPIOA->CRL |= 0xB<<8;//����PA2ΪTX
	GPIOA->CRL |= 4<<12;//����PA3ΪRX
	
	temp = (pclk1*1000000)/(bound*16);//�õ�usartdiv
	integer = temp;//�õ���������
	decimal = (temp-integer)*16;//�õ�С������(��16���ǽ�С����ǰ��4λ)
	USART2->BRR = decimal+(integer<<4);//�õ����ò�����Ҫд��usartdiv��ֵ
	MY_NVIC_Init(1,1,38,2);//��ռ2��Ӧ2
	USART2->CR1 |= 1<<5;//���ջ���ǿ��ж�
	USART2->CR1 |= 1<<2;//����ʹ��
	USART2->CR1 |= 1<<3;//����ʹ��
	USART2->CR1 |= 1<<13;//����2ʹ��
}


//printf���λ 0-USART1 1-USART2
u8 USART_PRINTF=0;

#pragma import(__use_no_semihosting)   
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{
	if(USART_PRINTF==0)
	{
		while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
		USART1->DR = (u8) ch;      	//дDR,����1����������
	}else
	{
		while((USART2->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
		USART2->DR = (u8) ch;      	//дDR,����2����������
	}
	return ch;
}


