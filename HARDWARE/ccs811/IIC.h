#ifndef _IIC_H
#define _IIC_H
#include "stm32f10x.h"

#define IIC_SCL		PBout(7)
#define IIC_SDA		PBout(8)
#define READ_SDA	PBin(8)

//IO口方向
#define SDA_IN() 	{GPIOB->CRH &= ~(0xF<<0); GPIOB->CRH |= 8<<0; }//输入模式
#define SDA_OUT()	{GPIOB->CRH &= ~(0xF<<0); GPIOB->CRH |= 3<<0; }//输出模式


#define  ON_CS()    {PBout(9)=0;}//delay_us(1);
#define  OFF_CS()   {PBout(9)=1;}//delay_us(1);



#define CCS811_Add  0x5A<<1
#define STATUS_REG 0x00
#define MEAS_MODE_REG 0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA 0x05
#define NTC_REG 0x06
#define THRESHOLDS 0x10
#define BASELINE 0x11
#define HW_ID_REG 0x20
#define ERROR_ID_REG 0xE0
#define APP_START_REG 0xF4
#define SW_RESET 0xFF
#define CCS_811_ADDRESS 0x5A
#define GPIO_WAKE 0x5
#define DRIVE_MODE_IDLE 0x0
#define DRIVE_MODE_1SEC 0x10
#define DRIVE_MODE_10SEC 0x20
#define DRIVE_MODE_60SEC 0x30
#define INTERRUPT_DRIVEN 0x8
#define THRESHOLDS_ENABLED 0x4



void I2C_GPIO_Config(void);
u8 Single_WriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 data);
u8 Single_MWriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length);
u8 Single_ReadI2C(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length);


#endif
