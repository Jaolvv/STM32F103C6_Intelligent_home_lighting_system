#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

#define LED0 PCout(13)//ָʾ��

#define LED1 PAout(8)//ָʾ��

#define BEEP PBout(10)//������

//����
#define KEY1 PBin(14)
#define KEY2 PBin(15)
#define KEY3 PAin(11)
#define KEY4 PAin(12)


//LED��ʼ������
void LED_Init(void);

void KEY_Init( void );


#endif
