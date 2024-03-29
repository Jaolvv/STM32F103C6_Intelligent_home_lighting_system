//1602液晶驱动显示
#include "lcd1602.h"
#include "sys.h"
#include "delay.h"
#include "string.h"

//RS变量 显示在0页 占用2位 初始值0 最大值0 最小值0 小数0位 不支持映射 //人数
u32 RS = 0;
//RSY变量 显示在0页 占用2位 初始值10 最大值0 最小值0 小数0位 支持修改 每次增减0 不支持映射 //人数阈值
u32 RSY = 10;
//SD变量 显示在0页 占用3位 初始值0 最大值0 最小值0 小数0位 不支持映射 //人数
u32 SD = 0;
//SDY变量 显示在0页 占用3位 初始值50 最大值0 最小值0 小数0位 支持修改 每次增减0 不支持映射 //人数阈值
u32 SDY = 50;
//ZL变量 显示在0页 占用5位 初始值0 最大值0 最小值0 小数0位 不支持映射 //人数
u32 ZL = 0;
//ZLY变量 显示在0页 占用5位 初始值2000 最大值0 最小值0 小数0位 支持修改 每次增减0 不支持映射 //人数阈值
u32 ZLY = 2000;



//设置IO口 data为要写的数据
void LCD1602_SetIO( u8 data )
{
	LCD1602_D0=data&0x01;data>>=1;
	LCD1602_D1=data&0x01;data>>=1;
	LCD1602_D2=data&0x01;data>>=1;
	LCD1602_D3=data&0x01;data>>=1;
	LCD1602_D4=data&0x01;data>>=1;
	LCD1602_D5=data&0x01;data>>=1;
	LCD1602_D6=data&0x01;data>>=1;
	LCD1602_D7=data&0x01;
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
	
	//IO重定义
	RCC->APB2ENR |= 1<<0;//打开复用功能时钟
	AFIO->MAPR |= 1<<25;
	
	//配置PB9为推挽输出 初始输出状态为:0
	GPIOB->CRH &= 0xFFFFFF0F;//复位IO口模式
	GPIOB->CRH |= 0x00000030;//设置IO口模式
	PBout(9) = 0;//设置IO初始输出状态

	//配置PB8为推挽输出 初始输出状态为:0
	GPIOB->CRH &= 0xFFFFFFF0;//复位IO口模式
	GPIOB->CRH |= 0x00000003;//设置IO口模式
	PBout(8) = 0;//设置IO初始输出状态

	//配置PB7为推挽输出 初始输出状态为:0
	GPIOB->CRL &= 0x0FFFFFFF;//复位IO口模式
	GPIOB->CRL |= 0x30000000;//设置IO口模式
	PBout(7) = 0;//设置IO初始输出状态

	//配置PB6为推挽输出 初始输出状态为:0
	GPIOB->CRL &= 0xF0FFFFFF;//复位IO口模式
	GPIOB->CRL |= 0x03000000;//设置IO口模式
	PBout(6) = 0;//设置IO初始输出状态

	//配置PB5为推挽输出 初始输出状态为:0
	GPIOB->CRL &= 0xFF0FFFFF;//复位IO口模式
	GPIOB->CRL |= 0x00300000;//设置IO口模式
	PBout(5) = 0;//设置IO初始输出状态

	//配置PB4为推挽输出 初始输出状态为:0
	GPIOB->CRL &= 0xFFF0FFFF;//复位IO口模式
	GPIOB->CRL |= 0x00030000;//设置IO口模式
	PBout(4) = 0;//设置IO初始输出状态

	//配置PB3为推挽输出 初始输出状态为:0
	GPIOB->CRL &= 0xFFFF0FFF;//复位IO口模式
	GPIOB->CRL |= 0x00003000;//设置IO口模式
	PBout(3) = 0;//设置IO初始输出状态

	//配置PA15为推挽输出 初始输出状态为:0
	GPIOA->CRH &= 0x0FFFFFFF;//复位IO口模式
	GPIOA->CRH |= 0x30000000;//设置IO口模式
	PAout(15) = 0;//设置IO初始输出状态

	//配置PA12为推挽输出 初始输出状态为:0
	GPIOA->CRH &= 0xFFF0FFFF;//复位IO口模式
	GPIOA->CRH |= 0x00030000;//设置IO口模式
	PAout(12) = 0;//设置IO初始输出状态

	//配置PA11为推挽输出 初始输出状态为:0
	GPIOA->CRH &= 0xFFFF0FFF;//复位IO口模式
	GPIOA->CRH |= 0x00003000;//设置IO口模式
	PAout(11) = 0;//设置IO初始输出状态

	//配置PA8为推挽输出 初始输出状态为:0
	GPIOA->CRH &= 0xFFFFFFF0;//复位IO口模式
	GPIOA->CRH |= 0x00000003;//设置IO口模式
	PAout(8) = 0;//设置IO初始输出状态

	//屏幕按键 初始化

	//配置PB15为上下拉输入 初始输出状态为:1
	GPIOB->CRH &= 0x0FFFFFFF;//复位IO口模式
	GPIOB->CRH |= 0x80000000;//设置IO口模式
	PBout(15) = 1;//设置IO初始输出状态

	//配置PB14为上下拉输入 初始输出状态为:1
	GPIOB->CRH &= 0xF0FFFFFF;//复位IO口模式
	GPIOB->CRH |= 0x08000000;//设置IO口模式
	PBout(14) = 1;//设置IO初始输出状态

	//配置PB13为上下拉输入 初始输出状态为:1
	GPIOB->CRH &= 0xFF0FFFFF;//复位IO口模式
	GPIOB->CRH |= 0x00800000;//设置IO口模式
	PBout(13) = 1;//设置IO初始输出状态

	
	LCD1602_RW=0;LCD1602_E=0;
	LCD1602_WriteCmd(0x38);delay_ms(3);
	LCD1602_WriteCmd(0x0C);delay_ms(3);
	LCD1602_WriteCmd(0x06);delay_ms(3);
	LCD1602_WriteCmd(0x01);delay_ms(3);
}


//LCD设置显示位置 x与y是位置
void LCD1602_SetPlace( u8 x, u8 y )
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
void LCD1602_Show( u8 x, u8 y, char *Data )
{
	u8 temp,a=0;
	//设置开始位置
	LCD1602_SetPlace(x,y);
	for( temp=strlen(Data); temp>0; temp-- )
	{
		LCD1602_WriteData(Data[a]);
		x++;a++;
		delay_us(20);	
		if( x>19 )
		{
			y++;x=0;
			if( y==4 )return;
			LCD1602_SetPlace(x,y);
		}
	}
}


//显示整数 Data数据 nmb数字的位数
void LCD1602_ShowNmber( u8 x, u8 y, u32 Data, u8 nmb )
{
	u8 i,I;
	char temp[20]={0};

	I=nmb;
	for( i=0; i<nmb; i++ )
	{	 
		I--;
		temp[I] = Data%10+'0';Data/=10;
	}
	LCD1602_Show( x,y,temp);
	delay_us(3);
}


//显示小数 Dec小数位数
void LCD1602_ShowDecimals(u8 x, u8 y, u32 Data, u8 nmb, u8 Dec)
{
	u8 i = 0;
	u32 l = 1;
	//获取整数与小数的倍数关系
	for (i = 0; i < Dec; i++)
	{
		l *= 10;
	}
	//没有整数部分 只有小数部分
	if ((Dec + 1) == nmb)
	{
		LCD1602_Show(x,y,".");//显示小数点
		LCD1602_ShowNmber(x+1, y, Data%l, Dec);//显示小数部分
	}
	//既有整数部分 又有小数部分
	else if ((Dec + 1) < nmb)
	{
		LCD1602_ShowNmber(x, y, Data/l, (nmb-1-Dec));//显示整数部分
		LCD1602_Show((x+nmb-1-Dec), y, ".");//显示小数点
		LCD1602_ShowNmber((x+nmb-Dec), y, Data%l, Dec);//显示小数部分
	}
	//小数部分都不够显示时 不显示
}

