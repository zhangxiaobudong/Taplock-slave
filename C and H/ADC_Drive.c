#include "all.h"

//bit idata Hall_Flag=0;
u16 xdata Hall_Current=0;
u32 xdata Motor_Current=0;
u8  xdata ADC_Read_Byte=0;
u8  xdata ADC_Reference=0;

void ADC_Init()
{
	ADC_RES=0;
	P1ASF=0X03;
}
void ADC_Read_Data_Drive(u8 ADC_Write_Byte)//ADC_Write_Byte:0-检测电机电流，1-检测霍尔电流
{
	ADC_CONTR=0xE8|ADC_Write_Byte;
	while(1)
	{
		if(ADC_CONTR&0x10)
			break;
	}
	ADC_CONTR=0;
	ADC_Read_Byte=ADC_RES;
}

void Hall_Current_Calculate()
{
	ADC_Read_Data_Drive(Hall_Read_Current);		//捕捉霍尔电流值
	Hall_Current = ADC_Read_Byte-ADC_Reference;	
	Hall_Current *= 26;		//2500*1024/(100*1000)
	Hall_Current /= ADC_Reference;	//ADC_Reference
	if(Hall==0)  Hall_Current += 3;
}
void Motor_Current_Calculate()
{
	ADC_Read_Data_Drive(Motor_Read_Current);		//捕捉电机电流值
	Motor_Current = ADC_Read_Byte-ADC_Reference;	//ADC_Reference
	Motor_Current *= 2125;	//2490*1024/(150*8)
	Motor_Current /= ADC_Reference;//ADC_Reference
	Motor_Current *= 1001;
	Motor_Current -= 19099;
	Motor_Current >>= 10;
}
