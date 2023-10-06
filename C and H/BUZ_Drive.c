#include "all.h"

u8 xdata BUZ_Write_Go=0;
u8 xdata BUZ_count;
u8 xdata Mach_Count;

void Timer4_Init()	//��ʱ20MS
{ 
	T4T3M &= 0xDF;		//��ʱ��ʱ��12Tģʽ
	T4L = 0xB0;			//���ö�ʱ��ֵ
	T4H = 0x3C;			//���ö�ʱ��ֵ
	T4T3M |= 0x80;		//��ʱ��4��ʼ��ʱ
	IE2|=0x40;
	EA =1;
}
void Buz_Ser()
{
	switch(BUZ_Write_Go)
	{
		case 0:	BUZ_count=0;BUZ=1;break;
		case 1:	if(BUZ_count>=30)		//���д�����λ
				{
					BUZ=~BUZ;
					BUZ_count=0;
				}break;	
		case 2:	BUZ=0;break;			//���ִ���
	}
}
void Timer4_Routine() interrupt 20
{
	BUZ_count++;
	Mach_Count++;
}