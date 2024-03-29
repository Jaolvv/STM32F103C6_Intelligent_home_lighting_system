#ifndef __1602_H__
#define __1602_H__

#include "sys.h"

//������
#define LCD1602_RS	PAout(8)
#define LCD1602_RW	PAout(11)
#define LCD1602_E	PAout(12)


//���������� ���
#define LCD1602_D0 PAout(15)
#define LCD1602_D1 PBout(3)
#define LCD1602_D2 PBout(4)
#define LCD1602_D3 PBout(5)
#define LCD1602_D4 PBout(6)
#define LCD1602_D5 PBout(7)
#define LCD1602_D6 PBout(8)
#define LCD1602_D7 PBout(9)


//1602Һ����ʼ��
void LCD1602_Init( void );

void LCD_Show( u8 x, u8 y, char *Data );

//��ʾ���� Data���� nmb���ֵ�λ��
void LCD_ShowNmber( u8 x, u8 y, u32 Data, u8 nmb );


#endif
