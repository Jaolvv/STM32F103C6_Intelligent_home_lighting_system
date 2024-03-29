//1602液晶驱动显示
#include "1602.h"
#include "sys.h"
#include "delay.h"
#include "string.h"


//设置IO口 data为要写的数据
void LCD1602_SetIO( u8 data )
{
	LCD1602_D0=data&0x01;data>>=1;LCD1602_D1=data&0x01;data>>=1;
	LCD1602_D2=data&0x01;data>>=1;LCD1602_D3=data&0x01;data>>=1;
	LCD1602_D4=data&0x01;data>>=1;LCD1602_D5=data&0x01;data>>=1;
	LCD1602_D6=data&0x01;data>>=1;LCD1602_D7=data&0x01;
}


//向1602写指令
void LCD1602_WriteCmd( u8 cmd )
{
	LCD1602_SetIO(cmd);//写指令
	LCD1602_RS=0;//写指令模式
	LCD1602_E=0;
	delay_ms(3);
	LCD1602_E=1;
	delay_ms(3);
	LCD1602_E=0;
}


//向1602写数据
void LCD1602_WriteData( u8 data )
{
	LCD1602_SetIO( data );
	LCD1602_RS=1;//写数据模式
	LCD1602_E=0;
	delay_ms(3);
	LCD1602_E=1;
	delay_ms(3);
	LCD1602_E=0;
}


//1602液晶初始化
void LCD1602_Init( void )
{
	RCC->APB2ENR |= 1<<2;//打开PA时钟
	RCC->APB2ENR |= 1<<3;//打开PB时钟
	RCC->APB2ENR |= 1<<4;//打开PC时钟

	GPIOA->CRL &= 0xFFFFFFFF;//复位PA
	GPIOA->CRL |= 0x00000000;
	GPIOA->CRH &= 0x0FF00FF0;//复位PA8 11 12 15
	GPIOA->CRH |= 0x30033003;
	GPIOB->CRL &= 0x00000FFF;//复位PB3 4 5 6 7
	GPIOB->CRL |= 0x33333000;
	GPIOB->CRH &= 0xFFFFFF00;//复位PB8 9
	GPIOB->CRH |= 0x00000033;
	
	LCD1602_RW=0;LCD1602_E=0;
	LCD1602_WriteCmd(0x38);delay_ms(3);
	LCD1602_WriteCmd(0x0C);delay_ms(3);
	LCD1602_WriteCmd(0x06);delay_ms(3);
	LCD1602_WriteCmd(0x01);delay_ms(3);
}


//LCD设置显示位置 x与y是位置
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



//LCD显示ASCLL 
//x<20 y<4一行写满自动跳到下一行
void LCD_Show( u8 x, u8 y, char *Data )
{
	u8 temp,a=0;
	//设置开始位置
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




//显示整数 Data数据 nmb数字的位数
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

