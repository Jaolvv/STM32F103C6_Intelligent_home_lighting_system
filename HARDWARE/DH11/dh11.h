#ifndef __DH11_H__
#define __DH11_H__

#include "sys.h"

extern u8 TMP_Data;//温度
extern u8 HUM_Data;//湿度

//IO口方向
#define dht11_gpio_input()	{GPIOB->CRH &=  0xFFFFF0FF; GPIOB->CRH |= 0x00000800; }//输入模式
#define dht11_gpio_output() {GPIOB->CRH &= 0xFFFFF0FF; GPIOB->CRH |= 0x00000300; }//输出模式

//IO口操作函数
#define DHT11_OUT	PBout(10)
#define DHT11_IN	PBin(10)


void DH11_Init( void );//初始化
void dht11_reset(void);//开始信号
u16 dht11_read_bit(void);//读取一位
u16 dht11_read_byte(void);//读取一个字节 8位
u16 dht11_read_data(void);//获取数据


#endif
