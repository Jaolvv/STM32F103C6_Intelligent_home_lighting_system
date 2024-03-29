//ϵͳ�ӳٺ�������
#include "sys.h"

static u8 fac_us=0;//ÿ��us��Ҫ��systickʱ����
static u16 fac_ms=0;//ÿ��ms��Ҫ��systickʱ����


//delay�ӳٳ�ʼ��
void delay_Init( u8 SYSCLK )
{
	SysTick->CTRL&=~(1<<2);//����systick��ʱ��Դ
	fac_us=SYSCLK/8;//���һ��USҪ����SYSTICK������
	fac_ms=(u16)fac_us*1000;//���ÿ��ms��Ҫ��systickʱ����
}


//΢�뼶���ӳ�
void delay_us( u32 nus )
{
	u32 temp;
	SysTick->LOAD = nus*fac_us;//��ʱ����ص�systick����ȥ
	SysTick->VAL=0x00;//���systick������
	SysTick->CTRL=0x01;//��ʼ����
	do
	{
		temp=SysTick->CTRL;//��ȡ�Ƶ��Ĵ���
	}while( (temp&0x01)&&!(temp&(1<<16)));//�жϵȴ�ʱ���Ƿ񵽴�
	SysTick->CTRL=0x00;//�رռ�����
	SysTick->VAL =0X00;//��ռ�����
}


//���뼶���ӳ�
//ע: SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=0xffffff*8*1000/SYSCLK ��168M������,nms<=798ms 
void delay_ms( u32 nms )
{
	u32 temp;		   
	SysTick->LOAD = (u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00;//��ռ�����
	SysTick->CTRL = 0x01;//��ʼ����
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;//�رռ�����
	SysTick->VAL =0X00;//��ռ�����	 
}




