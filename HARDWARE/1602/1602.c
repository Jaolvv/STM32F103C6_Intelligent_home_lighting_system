//1602Һ��������ʾ
#include "1602.h"
#include "sys.h"
#include "delay.h"
#include "string.h"


//����IO�� dataΪҪд������
void LCD1602_SetIO( u8 data )
{
	LCD1602_D0=data&0x01;data>>=1;LCD1602_D1=data&0x01;data>>=1;
	LCD1602_D2=data&0x01;data>>=1;LCD1602_D3=data&0x01;data>>=1;
	LCD1602_D4=data&0x01;data>>=1;LCD1602_D5=data&0x01;data>>=1;
	LCD1602_D6=data&0x01;data>>=1;LCD1602_D7=data&0x01;
}


//��1602дָ��
void LCD1602_WriteCmd( u8 cmd )
{
	LCD1602_SetIO(cmd);//дָ��
	LCD1602_RS=0;//дָ��ģʽ
	LCD1602_E=0;
	delay_ms(3);
	LCD1602_E=1;
	delay_ms(3);
	LCD1602_E=0;
}


//��1602д����
void LCD1602_WriteData( u8 data )
{
	LCD1602_SetIO( data );
	LCD1602_RS=1;//д����ģʽ
	LCD1602_E=0;
	delay_ms(3);
	LCD1602_E=1;
	delay_ms(3);
	LCD1602_E=0;
}


//1602Һ����ʼ��
void LCD1602_Init( void )
{
	RCC->APB2ENR |= 1<<2;//��PAʱ��
	RCC->APB2ENR |= 1<<3;//��PBʱ��
	RCC->APB2ENR |= 1<<4;//��PCʱ��

	GPIOA->CRL &= 0xFFFFFFFF;//��λPA
	GPIOA->CRL |= 0x00000000;
	GPIOA->CRH &= 0x0FF00FF0;//��λPA8 11 12 15
	GPIOA->CRH |= 0x30033003;
	GPIOB->CRL &= 0x00000FFF;//��λPB3 4 5 6 7
	GPIOB->CRL |= 0x33333000;
	GPIOB->CRH &= 0xFFFFFF00;//��λPB8 9
	GPIOB->CRH |= 0x00000033;
	
	LCD1602_RW=0;LCD1602_E=0;
	LCD1602_WriteCmd(0x38);delay_ms(3);
	LCD1602_WriteCmd(0x0C);delay_ms(3);
	LCD1602_WriteCmd(0x06);delay_ms(3);
	LCD1602_WriteCmd(0x01);delay_ms(3);
}


//LCD������ʾλ�� x��y��λ��
void LCD_SetPlace( u8 x, u8 y )
{
	if( x<=20 )
	{
		switch( y )
		{
			case 0:LCD1602_WriteCmd(0x80+x);break;
			case 1:LCD1602_WriteCmd(0xC0+x);break;
			case 2:LCD1602_WriteCmd(0x94+x);break;
			case 3:LCD1602_WriteCmd(0xD4+x);break;
		}
		delay_us(20);	
	}
}



//LCD��ʾASCLL 
//x<20 y<4һ��д���Զ�������һ��
void LCD_Show( u8 x, u8 y, char *Data )
{
	u8 temp,a=0;
	//���ÿ�ʼλ��
	LCD_SetPlace(x,y);
	for( temp=strlen(Data); temp>0; temp-- )
	{
		LCD1602_WriteData(Data[a]);
		x++;a++;
		delay_us(20);	
		if( x>19 )
		{
			y++;x=0;
			if( y==4 )return;
			LCD_SetPlace(x,y);
		}
	}
}




//��ʾ���� Data���� nmb���ֵ�λ��
void LCD_ShowNmber( u8 x, u8 y, u32 Data, u8 nmb )
{
	u8 i,I;
	char temp[20]={0};

	I=nmb;
	for( i=0; i<nmb; i++ )
	{	 
		I--;
		temp[I] = Data%10+'0';Data/=10;
	}
	LCD_Show( x,y,temp);
	delay_us(3);
}

