# STM32F103C6_Intelligent_home_lighting_system
CQEVI_Graduation_物联网智能家庭照明系统

# 主控电路STM32F103C6
在基于物联网的智能家庭照明系统主控电路设计中，我们选择采用的是STM32F103C6作为其主控核心，如图3.2所示。STM32F103C6是一款基于 ARM Cortex M3 内核的 32 位通用微控制器芯片:STM32F103系列芯片，优异的性能，资源丰富，性价比超高，本文和后续教程选用STM32F103C6这款芯片的开发板是因为这款芯片成本较低，主频高达72Mhz，且具备非常丰富的片上资源，完全可以满足STM32学习的需求。最小系统板STM32F103C6原理电路示意图
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/31402d69-d1fd-4882-9576-ffc7c1ed74f0)
最小系统是能够维持MCU工作的一个最精简的电路，最小系统一般由电源、外部复位电路外部时钟电路以及MCU本体构成，开发板就是一个最小系统。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/a5e46a2f-33d4-4352-ad57-ea93a24149a2)
## 晶振电路以及复位电路
这部分电路使用了一个8MHz的石英晶体振荡器（X1），这是MCU主要的时钟源。它通过两个20pF的电容（C1和C3）与地（GND）相连，这些电容与晶振形成了皮尔斯振荡器，用来稳定振荡频率。振荡器的两个引脚分别接到MCU的OSC_IN和OSC_OUT引脚上，提供精确的时钟信号供MCU工作。
后备晶振使用的是一个32.768kHz的石英晶体振荡器（X2），它通常用于实时时钟（RTC）或需要较低频率时钟的其他低功耗模式。同样的，它通过两个20pF的电容（C6和C7）与地（GND）相连，确保稳定振荡。该晶振连接至MCU的PC14和PC15引脚。
复位电路由一个10KΩ的上拉电阻（R1）和一个104（100nF）电容（C14）组成，构成了MCU的复位电路。R1保证了在没有外部复位信号时，MCU_RST引脚保持在高电平状态（VCC），而C14在有复位按钮按下时提供瞬间的低电平信号。复位按钮（SW5）在按下时会将MCU_RST引脚接地，这会产生一个低电平信号，使MCU复位。释放按钮后，C14会充电，并且R1会将MCU_RST引脚拉回高电平，结束复位过程。
这个设计思路是为了确保MCU有一个稳定的主时钟源供日常操作使用，一个较低频率的后备时钟源用于特定功能（如RTC），以及一个可靠的复位机制以便在需要时重启MCU，原理图如下图所示。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/7db09129-8b57-4465-9407-41637e9b45d4)
## S8050插件三极管
S8050是一种高电流和低电压晶体管，如图3.7所示。其集电极电流为700mA，集电极-发射极电压(VCE)为25V。为了非常安全地操作该晶体管，该晶体管的基极电流必须限制在5mA以内。该晶体管是一个三端元件，包括发射极、基极和集电极，可用于通过不同的电路进行外部连接。与集电极和基极这两个端子相比，无论发射极掺杂程度如何，这三个端子的掺杂浓度都是不同的。工作原理：在S8050 NPN晶体管中，当基极接地时，发射极和集电极等两个端子都将反向偏置，当向基极引脚提供信号时，它们将关闭(正向偏置)。该晶体管的最大增益值为300，此值将决定放大能力。如果放大率很高，则将其用于放大。但是，集电极电流的增益值将是110，并且整个集电极端子的最大电流供应是700mA，因此无法通过该晶体管通过700mA以上的电流来控制不同的负载。一旦向必须限制在5mA的基极引脚提供电流供应，晶体管就可以被偏置。如果品体管完全偏置，则它允许高达700mA的电流通过发射极和集电极端子提供，因此该阶段称为饱和区。VCE或VCB上使用的典型电压相应为20V和30V。一旦在晶体管的基极端移除电流源，它将被关闭，因此这个阶段称为截止区域。
2N2369、2N3904、2N3055、MPSA42、BC547、S9014、2N3906、SS8050等可以替代S8050晶体管。
## LED发光二极管模块
发光二极管（Light-Emitting Diode，简称LED）是一种半导体器件，能够将电能直接转化为光能的固态光源。当正向电流通过LED时，电子从较高能级跃迁到较低能级，释放出能量并以光的形式辐射出来。不同的材料和掺杂方式决定了发射的光波长。LED具有诸多优势。发光二极管电路图如下图所示。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/2a62be89-a431-41e3-b357-fe1dfbc7967b)
## ASR-PRO智能语音识别模块AI离线识别开发板
ASR语音识别模块是一款基于深度学习技术的语音识别模块，它采用了常见的语音识别技术，包括声学模型、语言模型和解码器通过对声学信号进行特征提取和模式识别来识别语音。电路图、语音识别微控制器的引脚配置如下图所示。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/8c83f8af-22d0-426e-8f8a-686ae0f65ff4)
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/b49dc905-611b-4d1f-8afa-f11cbd3c722c)
## TCRT5000红外反射传感器红外传感器模块
该传感器模块对环境光线适应能力强，其具有一对红外线发射与接收管，发射管发射出一定频率的红外线，当检测方向遇到障碍物（反射面）时，红外线反射回来被接收管接收，经过比较器电路处理之后，绿色指示灯会亮起，同时信号输出接口输出数字信号（一个低电平信号），可通过电位器旋钮调节检测距离，有效距离范围2~30厘米，工作电压为3.3V-5V。广泛应用于需要检测人体活动的项目中，如自动照明系统、安全报警、自动门控等。这种传感器专门设计用于检测人体的红外辐射，以感知人体的运动。
工作原理为红外发射: 发光二极管（在左上角标记为“发射管”）发射红外光。光线反射: 当有物体靠近传感器时，红外光会被反射回来，并被光电晶体管（位于电路图中央的TCRT5000符号内）检测到。信号比较: LM393是一种双路差动比较器，用于比较两个输入信号。在这个电路中，一个输入（非反相输入，标记为“+”）连接到一个可变电阻VR1，用于设置参考电压。另一个输入（反相输入，标记为“-”）连接到TCRT5000的输出。可变电阻调整: 通过调整可变电阻VR1，可以设置当光电晶体管检测到的光强达到某个阈值时，LM393输出状态的变化。输出状态: LM393比较器的输出（标记为“DO”）会随着检测到的光强和设定的阈值变化而改变状态。这个输出可以直接驱动一些电子设备或与微控制器接口。模拟输出: TCRT5000还提供了一个模拟输出（标记为“A0”），直接反映了光电晶体管检测到的光强度。供电: 整个电路由VCC提供电源。这个电路常用于测距、检测物体是否存在于传感器前方、线路跟踪（如在机器人上）等应用场合。电阻器的数值（如1K、10K等）是用于设定电路中电流的大小和传感器的灵敏度。TCRT5000红外反射传感器参考电路示意图如下所示。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/a8540fa7-20db-405f-baca-28a85363b327)
## LCD1602液晶显示屏模组
此模组用于显示定时的时间和定时的开启或关闭状态，1602液晶也叫1602字符型液晶，它是一种专门用来显示字母、数字、符号等的点阵型液晶模块。它由若干个5X7或者5X11等点阵字符位组成，每个点阵字符位都可以显示一个字符，每位之间有一个点距的间隔，每行之间也有间隔，起到了字符间距和行间距的作用，正因为如此所以它不能很好地显示图形（用自定义CGRAM，显示效果也不好）。内部框架图如下图所示。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/9bf2f723-0fe5-4061-a18d-963f96943ea3)
1602LCD是指显示的内容为16X2,即可以显示两行，每行16个字符液晶模块（显示字符和数字）。市面上字符液晶大多数是基于HD44780液晶芯片的，控制原理是完全相同的，因此基于HD44780写的控制程序可以很方便地应用于市面上大部分的字符型液晶。HD44780内置了DDRAM、CGROM、CGRAM.其中要让lcd显示就需要将DDRAM的相应地址写入数据。原理图如下图所示。
![image](https://github.com/Jaolvv/STM32F103C6_Intelligent_home_lighting_system/assets/51476712/8eb17495-bc70-4dde-97b1-cb9ed097f913)
4 智能家庭照明系统软件设计
4.1 软件总体设计
在系统启动时会进行初始化的设置，启动包括语音识别模块人体检测模块等在内的各种传感器、WiFi通信模块以及LED灯的初始化配置。智能家庭照明系统采用传统三层软件架构，确保系统的高效性和可扩展性：
感知层：感知层主要负责收集信息，是物联网的“感官”。检测人体是否靠近或离开，根据检测结果自动控制灯光的开或关，实现智能化的人体感应照明。
通过接收并识别用户的语音指令（如“开灯”或“关灯”），将语音信息转换成电子信号，从而控制灯光的开关。
网络层：红外传感器、语音识别模块等传感器模块通过电气接口与主控芯片（STM32F103C6）连接。传感器模块检测到的信息（如人体活动、语音指令）被传输到主控芯片，以触发相应的操作。
应用层：直接与硬件交互，执行开关灯、调整亮度和颜色等操作以及语音控制。同时，从传感器模块收集数据和能耗信息，上报给网络层。
4.1.1 开发环境搭建
首先前往Keil官网（https://www.keil.com/download/product/）下载STM32开发环境。如图4.1所示。
 
图4.1 Keil官网开发环境下载示意图
再安装Keil.STM32F4xx_DFP.2.16.0.pack以及Keil.STM32F1xx_DFP.2.4.0.pack软件支持包。Keil.stm32f4xx dfp.2.16.0.pack是Keil公司为STM32F4xx系列微控制器开发套件提供的一个软件插件包，其全称为Keil.STM32F4xx DFP.DeviceFamilyPack.2.16.0.pack。这个插件包提供了一系列针对STM32F4xx系列微控制器的设备支持文件，可以帮助开发人员更方便、快速地编写STM32F4xx系列微控制器的应用程序。Kei公司是一家专门从事嵌入式系统开发工具的公司，他们提供了一系列开发环境和工具，协助嵌入式系统开发者设计和开发高质量的嵌入式系统，并在市场上享有很高的声誉。
4.1.2 软件代码结构
如下图4.2所示，代码结构主要分为系统代码、STM32驱动代码、硬件传感器代码三个部分：
系统代码，主体为STM32微控制器的启动和配置代码，主要作用是初始化系统，配置中断优先级，设置外部中断，并提供了一些控制函数，如进入待机模式、系统软复位等。
STM32驱动代码，在构思STM32F103单片机的驱动代码时，需要考虑项目的具体需求，例如控制LED灯、读取传感器数据和通过网络发送数据等功能。。
传感器硬件代码，分别为LCD1602液晶显示屏、人体红外传感器、语音识别模块进行初始化和数据读取。
 
图4.2代码结构图
4.2 LCD液晶显示屏程序设计
为了驱动LCD1602液晶显示屏，这块显示屏用于显示文本信息比如灯光打开状态和定时信息等。代码使用C语言编写，适用于嵌入式系统，特别是基于STM32微控制器的系统。以下概述了代码的主要功能：。
		引入必要的头文件：lcd1602.h，sys.h，delay.h，string.h 分别用于LCD相关的操作、系统配置、延时处理和字符串操作。
		变量定义：
定义了一系列全局变量，如RS、RSY、SD等，用于在LCD上显示相关的数据，以及对应的阈值设置。
		IO口设置函数（LCD1602_SetIO）：
用于设置LCD的数据引脚状态。这些引脚通常用于发送数据和命令给LCD显示屏。
		写指令函数（LCD1602_WriteCmd）和写数据函数（LCD1602_WriteData）：
这两个函数分别用于向LCD发送控制指令和显示数据。
		LCD初始化函数（LCD1602_Init）：
初始化LCD显示屏，包括配置相关的GPIO引脚，以及向LCD发送一系列的初始化指令。
		设置显示位置函数（LCD1602_SetPlace）：用于设置LCD上文本显示的具体位置。
显示文本函数（LCD1602_Show）：用于在特定的LCD位置显示字符串。
显示数字函数（LCD1602_ShowNmber）和显示小数函数（LCD1602_ShowDecimals）：这两个函数分别用于在LCD上显示整数和小数。
屏幕按键初始化和GPIO配置：设置GPIO引脚的模式和状态，这里包括设置PB9、PB8、PB7等多个引脚。
屏幕按键初始化和GPIO配置：设置GPIO引脚的模式和状态，这里包括设置PB9、PB8、PB7等多个引脚。
		整个代码是为了在LCD上显示各种文本信息，并提供用户交互的可能性，如数字和阈值的实时显示，这在各种控制系统和用户界面中非常有用。 
 
4.3 STM32驱动代码设计
这部分代码是针对STM32微控制器的系统配置和中断管理的一部分。它主要包括以下核心功能：
向量表设置 (MY_NVIC_SetVectorTable):
这个函数用于设置中断向量表的基地址和偏移量。这是系统启动时的关键配置，确保中断服务程序(ISR)可以被正确地定位和执行。
NVIC分组配置 (MY_NVIC_PriorityGroupConfig):
用于配置嵌套向量中断控制器(NVIC)的优先级分组。STM32有多个优先级分组选项，这决定了可用的抢占优先级和子优先级的位数,如代码4.1所示。


代码4.1 设置向量表偏移地址过程
 
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)
{
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//取后三位
	temp1<<=8;
	temp=SCB->AIRCR;  //读取先前的设置
	temp&=0X0000F8FF; //清空先前分组
	temp|=0X05FA0000; //写入钥匙
	temp|=temp1;	   
	SCB->AIRCR=temp;  //设置分组
}
 
NVIC初始化 (MY_NVIC_Init):
用于初始化特定中断的NVIC设置，包括设置中断优先级、子优先级和中断通道。,如代码4.2所示。
代码4.2 初始化中断NVIC设置过程
 
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)
{ 
	u32 temp;	
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//设置分组
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//取低四位  
	NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//使能中断位(要清除的话,相反操作就OK) 
	NVIC->IP[NVIC_Channel]|=temp<<4;//设置响应优先级和抢断优先级   	    	  				
}
 
外部中断配置 (Ex_NVIC_Config):
设置GPIO引脚为外部中断输入，配置触发模式（上升沿、下降沿、任意电平变化触发）。如代码4.3所示。该函数一次只能配置1个IO口,多个IO口,需多次调用且会自动开启对应中断,以及屏蔽线。
代码4.3 外部中断配置函数过程
 
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM)
{
	u8 EXTADDR;
	u8 EXTOFFSET;
	EXTADDR=BITx/4;//得到中断寄存器组的编号
	EXTOFFSET=(BITx%4)*4; 
	RCC->APB2ENR|=0x01;//使能io复用时钟			 
	AFIO->EXTICR[EXTADDR]&=~(0x000F<<EXTOFFSET);//清除原来设置！！！
	AFIO->EXTICR[EXTADDR]|=GPIOx<<EXTOFFSET;//EXTI.BITx映射到GPIOx.BITx 
	//自动设置
	EXTI->IMR|=1<<BITx;//  开启line BITx上的中断
	//EXTI->EMR|=1<<BITx;//不屏蔽line BITx上的事件 (如果不屏蔽这句,在硬件上是可以的,但是在软件仿真的时候无法进入中断!)
 	if(TRIM&0x01)EXTI->FTSR|=1<<BITx;//line BITx上事件下降沿触发
	if(TRIM&0x02)EXTI->RTSR|=1<<BITx;//line BITx上事件上升降沿触发
}
 
系统时钟复位 (MYRCC_DeInit):
复位所有时钟，将系统时钟恢复到默认状态，是系统重置或重新配置时钟的基础步骤。注意不能在这里执行所有外设复位，否则至少引起串口不工作， 如代码4.4所示。
代码4.4 把所有时钟寄存器复位过程
 
void MYRCC_DeInit(void)
{
 	RCC->APB1RSTR = 0x00000000;//复位结束			 
	RCC->APB2RSTR = 0x00000000; 
	  
	RCC->AHBENR = 0x00000014;  //睡眠模式闪存和SRAM时钟使能.其他关闭.	  
	RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //关闭所有中断		 
	//配置向量表				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(0x20000000, 0x0);
#else   
	MY_NVIC_SetVectorTable(0x08000000,0x0);
#endif
}
 
执行WFI指令 (WFI_SET):
执行“等待中断”指令，该指令会使CPU进入休眠模式，直到下一个中断到来。

中断使能/禁用 (INTX_DISABLE, INTX_ENABLE):
这两个函数分别用于全局禁用和使能中断。

进入待机模式 (Sys_Standby):
配置并进入STM32的待机模式，该模式下功耗极低，只能通过设置的唤醒引脚来唤醒设备。如代码4.5所示。
代码4.5 进入待机模式配置函数过程
 
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//使能SLEEPDEEP位 (SYS->CTRL)	   
  	RCC->APB1ENR|=1<<28;     //使能电源时钟	    
 	PWR->CSR|=1<<8;          //设置WKUP用于唤醒
	PWR->CR|=1<<2;           //清除Wake-up 标志
	PWR->CR|=1<<1;           //PDDS置位		  
	WFI_SET();				 //执行WFI指令		 
}
 
软复位 (Sys_Soft_Reset):
触发一个软复位，该操作会重置微控制器，类似于硬件上的复位操作。
JTAG接口配置 (JTAG_Set):
配置调试接口模式，允许全JTAG、只使用SWD或者完全关闭JTAG/SWD接口，以允许这些引脚作为普通I/O使用。

系统时钟初始化 (Stm32_Clock_Init):
配置和启动内部或外部高速时钟源，设置并启用PLL，以达到所需的系统时钟频率,如代码4.6所示。
代码4.6 系统时钟初始化函数配置函数过程
 
void Stm32_Clock_Init(u8 PLL)
{
	unsigned char temp=0;   
	MYRCC_DeInit();		  //复位并配置向量表
 	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
	while(!(RCC->CR>>17));//等待外部时钟就绪
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;				  //抵消2个单位（因为是从2开始的，设置0就是2）
	RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2个延时周期
	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	RCC->CFGR|=0x00000002;//PLL作为系统时钟	 
	while(temp!=0x02)     //等待PLL作为系统时钟设置成功
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}
 
这些函数组成了STM32微控制器在不同应用中的基础配置，使其可以适应各种硬件环境和功能需求。在物联网智能家庭照明系统中，这些配置是确保系统稳定运行和响应外部事件的基础。 
 

4.4 语音识别模块程序设计
首先下载天问Block软件，（下载地址：http://www.twen51.com/new/twen51/index.php）它是单片机开发利器，一站式的开发工具，通过简单易用的图形化模式和代码模式编程，让天问51开发变得简单和高效，如图4.3所示。天问Block主要包括项目创建和云保存，代码编辑，调试配置，程序下载和调试等功能，结合图形化、代码编程以及丰富的软件资源，减少重复工作，提高开发效率。天问Block无缝对接在线平台，支持账号管理，支持C51、STC12、STC15、STC8、STC16、STC32G、CH32V003、CH32V103、CH57X、TW32F003、TWEN-ASR、ASRPRO、ASR-MCU、TWEN32等硬件芯片离线环境下编程，并可以查看案例、上传作品，轻松保存程序。适用win7以上32位、64位操作系统。它的图形化模块编程可自动生成专业代码，方便快速配置外设，不需要翻手册，查寄存器，把更多精力放在逻辑应用层。图形化串口绘图工具，绘制数据波形，清晰直观，简单易用。
 
图4.3天问Block软件界面图
注意需要安装驱动。使用LU-ASR01模块需要下载CH340/CH341驱动；打开软件后选择设备TWEN-ASR，如图4.4所示。
 
图4.4天问Block选择设备界面图
之后配置串口通信如下语句，如图4.5所示。
 
图4.5编写语句图
编译下载前，注意模块是否与电脑连接，如图4.6所示。可以通过电脑设备管理器中的端口查看端口号；(如果正确接上模块，会自主识别)。编译下载需要等待一分钟左右，下载完成后ASR01会播报“智能管家”(即我们设置的ASR01的欢迎词)。
 
图4.6编译示意图

4.5 TCRT5000红外反射传感器代码设计
当模块检测到前方障碍物信号时，电路板上绿色指示灯点亮电平，同时OUT端口持续输出低电平信号,该模块检测距离2~30cm，检测角度35°，检测距离可以通过电位器进行调节，顺时针调电位器，检测距离增加;逆时针调电位器，检测距离减少。传感器主动红外线反射探测,因此目标的反射率和形状是探测距离的关键。其中黑色探测距离最小,白色最大;小面积物体距离小,大面积距离大。传感器模块输出端口OUT可直接与单片机I0口连接即可，也可以直接驱动一个5V继电器;连接方式:VCC-VCC;GND-GND;OUT-I0。

如代码4.7所示，是一个人体红外感应与自动灯光延迟关闭的示例代码。
代码4.7 人体红外感应与自动灯光延迟关闭实例代码 
1 const int pirPin = 2; // 红外传感器引脚连接到单片机的数字引脚2
const int ledPin = 9; // 灯光控制引脚连接到单片机的数字引脚9
const unsigned long delayTime = 5000; // 延迟关闭时间（单位：毫秒）
unsignedlong lastTriggerTime = 0; // 上次触发时间
void setup() {
  pinMode(pirPin, INPUT); // 初始化红外传感器引脚为输入模式
  pinMode(ledPin, OUTPUT); // 初始化灯光控制引脚为输出模式
}
void loop() {
  int pirValue = digitalRead(pirPin); // 读取红外传感器的值
  if (pirValue == HIGH) {
    digitalWrite(ledPin, HIGH); // 打开灯光
    lastTriggerTime = millis(); // 记录触发时间
  } else {
    unsigned long elapsedTime = millis() - lastTriggerTime; // 计算自上次触发经过的时间
    if (elapsedTime >= delayTime) {
      digitalWrite(ledPin, LOW); // 关闭灯光
    }
  }
} 

这个程序在人体红外感应触发后，打开灯光，并在一定延迟时间后自动关闭灯光。引入了一个新的变量 lastTriggerTime 用来记录上次触发的时间。
使用 millis() 函数获取当前时间，计算自上次触发经过的时间。如果红外传感器检测到人体，打开灯光并更新 lastTriggerTime。如果红外传感器没有检测到人体，判断自上次触发经过的时间是否超过设定的延迟时间，如果超过，则关闭灯光。
