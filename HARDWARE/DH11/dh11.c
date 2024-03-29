#include "sys.h"
#include "dh11.h"
#include "delay.h"

u8 DHT11_buffer[5]={0};// 湿度温度 读取到的数据存放数组
u8 TMP_Data;//温度
u8 HUM_Data;//湿度

//初始化
void DH11_Init( void )
{
	//开启GPIOA的时钟
	RCC->APB2ENR |= 1<<2;
   RCC->APB2ENR |= 1<<3;
//	GPIOA->CRL &= 0xFFF0FFFF;//PA7
//	GPIOA->CRL |= 0x00030000;
   
   GPIOB->CRH &= 0xFFFFF0FF;//PB10
	GPIOB->CRH |= 0x00000300;
}


//开始信号
void dht11_reset(void)
{
	dht11_gpio_output();
	DHT11_OUT = 0;;
	delay_us(18000);
	DHT11_OUT = 1;
	delay_us(30);
	dht11_gpio_input();
}


//读取一位
u16 dht11_read_bit(void)
{
	u8 a=0;
	while (DHT11_IN == RESET)
	{
		a++;
		if(a>=100)return 1;
		delay_us(1);
	}a=0;
	delay_us(40);
	if (DHT11_IN == SET)
	{
		while(DHT11_IN == SET)
		{
			a++;
			if(a>=100)return 1;
			delay_us(1);
		}a=0;
		return 1;
	}else return 0;
}


//读取一个字节 8位
u16 dht11_read_byte(void)
{
	u16 i;
	u16 data = 0;
	for (i = 0; i < 8; i++)
	{
		data <<= 1;
		data |= dht11_read_bit();
	}
	return data;
}


//获取数据
u16 dht11_read_data(void)
{
	u8 a=0;
	u16 i = 0;
	u8 checksum;
	
	dht11_reset();//起始信号
	if(DHT11_IN == RESET)
	{
		while(DHT11_IN == RESET)
		{
			a++;
			if(a>=100)return 1;
			delay_us(1);
		}a=0;
		while (DHT11_IN == SET)
		{
			a++;
			if(a>=100)return 1;
			delay_us(1);
		}a=0;
		for (i = 0; i < 5; i++)DHT11_buffer[i] = dht11_read_byte();
		while(DHT11_IN == RESET)
		{
			a++;
			if(a>=100)return 1;
			delay_us(1);
		}a=0;
		dht11_gpio_output();
		DHT11_OUT=1;
		
		checksum = DHT11_buffer[0] + DHT11_buffer[1] + DHT11_buffer[2] + DHT11_buffer[3];//对读取到的值进行校准
		if (checksum != DHT11_buffer[4])return 1;//如果校验位有误则返回错误
	}
	HUM_Data = DHT11_buffer[0];//湿度
	TMP_Data = DHT11_buffer[2];//温度
	return 0;
}


