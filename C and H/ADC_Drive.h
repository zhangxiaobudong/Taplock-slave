#ifndef ADC_Drive
#define ADC_Drive

//extern bit idata Hall_Flag;
extern u16 xdata Hall_Current;
extern u32 xdata Motor_Current;
extern u8  xdata ADC_Read_Byte;
extern u8  xdata ADC_Reference;

#define Hall_Read_Current	0x01
#define Motor_Read_Current	0x00

extern void ADC_Init();
//extern void ADC_Read_Data_Drive(u8 ADC_Write_Byte);
extern void Hall_Current_Calculate();	//捕获霍尔电流
extern void Motor_Current_Calculate();	//捕获电机电流

#endif