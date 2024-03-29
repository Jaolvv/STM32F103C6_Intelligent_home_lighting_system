#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "sys.h"

//将PB9重命名为LCD1602_RS
#define LCD1602_RS		PBout(9)
//将PB8重命名为LCD1602_RW
#define LCD1602_RW		PBout(8)
//将PB7重命名为LCD1602_E
#define LCD1602_E		PBout(7)
//将PB6重命名为LCD1602_D0
#define LCD1602_D0		PBout(6)
//将PB5重命名为LCD1602_D1
#define LCD1602_D1		PBout(5)
//将PB4重命名为LCD1602_D2
#define LCD1602_D2		PBout(4)
//将PB3重命名为LCD1602_D3
#define LCD1602_D3		PBout(3)
//将PA15重命名为LCD1602_D4
#define LCD1602_D4		PAout(15)
//将PA12重命名为LCD1602_D5
#define LCD1602_D5		PAout(12)
//将PA11重命名为LCD1602_D6
#define LCD1602_D6		PAout(11)
//将PA8重命名为LCD1602_D7
#define LCD1602_D7		PAout(8)
//将PB15重命名为LCD_KEY1
#define LCD_KEY1		PBin(15)
//将PB14重命名为LCD_KEY2
#define LCD_KEY2		PBin(14)
//将PB13重命名为LCD_KEY3
#define LCD_KEY3		PBin(13)


//1602液晶初始化
void LCD1602_Init( void );

//LCD设置显示位置 x与y是位置
void LCD1602_SetPlace(u8 x, u8 y);

void LCD1602_Show( u8 x, u8 y, char *Data );

//显示整数 Data数据 nmb数字的位数
void LCD1602_ShowNmber( u8 x, u8 y, u32 Data, u8 nmb );




#endif
