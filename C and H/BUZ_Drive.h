#ifndef BUZ_Drive
#define BUZ_Drive

sbit BUZ=P5^0;		//·äÃùÆ÷
extern u8  xdata BUZ_Write_Go;
extern u8  xdata Mach_Count;

extern void Timer4_Init();
extern void Buz_Ser();

#endif