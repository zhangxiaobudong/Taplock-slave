#include "all.h"

u8 xdata BUZ_Write_Go=0;
u8 xdata BUZ_count;
u8 xdata Mach_Count;

void Timer4_Init()	//定时20MS
{ 
	T4T3M &= 0xDF;		//定时器时钟12T模式
	T4L = 0xB0;			//设置定时初值
	T4H = 0x3C;			//设置定时初值
	T4T3M |= 0x80;		//定时器4开始计时
	IE2|=0x40;
	EA =1;
}
void Buz_Ser()
{
	switch(BUZ_Write_Go)
	{
		case 0:	BUZ_count=0;BUZ=1;break;
		case 1:	if(BUZ_count>=30)		//运行次数到位
				{
					BUZ=~BUZ;
					BUZ_count=0;
				}break;	
		case 2:	BUZ=0;break;			//出现错误
	}
}
void Timer4_Routine() interrupt 20
{
	BUZ_count++;
	Mach_Count++;
}