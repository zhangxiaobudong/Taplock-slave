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
sbit OLED_RES=P5^4;			//��λ����

sbit LED_W=P5^5;			//���ϵ�

sbit Cy_Side=P3^5;			//��������
sbit Cy_Front=P3^6;			//ǰ������
sbit Cy_Rear=P3^7;			//��������

sbit KEY_Run=P3^3;			//����/ֹͣ/���㰴��
//sbit KEY_Run=P1^5;		//����/ֹͣ/���㰴��
//sbit KEY_EME=P3^7;		//Ӧ������

sbit RS485_ReadWrite=P3^2;	//RS485��дʹ��    0��ȡ����   1��������

sbit Limit=P3^4;			//��λ�����ź�1
sbit Hall=P1^2;				//�����ź�1
//sbit Mach1_Start=P1^3;	//���1�����źţ��͵�ƽ������
sbit Mach1_INA=P1^3;		//���1
sbit Mach1_INB=P1^4;		//���1
