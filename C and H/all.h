#include "STC15.h"
#include "intrins.h"
//#include "string.h"
//#include "stdio.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define Open		1
#define Close 		0

#include "ASCLL.h"
#include "ADC_Drive.h"
#include "Lock_Drive.h"
#include "EEPROM.h"
#include "Cylinder_Drive.h"
#include "IIC_Drive.h"
#include "OLED_Drive.h"
#include "LED_Drive.h"
#include "KEY_Drive.h"
#include "RS485_Drive.h"

/*************************************/
sbit IIC_SCL=P1^6;		
sbit IIC_SDA=P1^7;		
sbit OLED_RES=P5^4;			//复位引脚

sbit LED_W=P5^5;			//故障灯

sbit Cy_Side=P3^5;			//侧面气缸
sbit Cy_Front=P3^6;			//前面气缸
sbit Cy_Rear=P3^7;			//后面气缸

sbit KEY_Run=P3^3;			//运行/停止/清零按键
//sbit KEY_Run=P1^5;		//运行/停止/清零按键
//sbit KEY_EME=P3^7;		//应急按键

sbit RS485_ReadWrite=P3^2;	//RS485读写使能    0读取数据   1发送数据

sbit Limit=P3^4;			//限位开关信号1
sbit Hall=P1^2;				//霍尔信号1
//sbit Mach1_Start=P1^3;	//电机1启动信号（低电平启动）
sbit Mach1_INA=P1^3;		//电机1
sbit Mach1_INB=P1^4;		//电机1
