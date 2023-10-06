#include "all.h"

void LED_Ser()
{
	if(Run_State)
		LED_W=LED_Open;
	else
		LED_W=LED_Close;
}
//u8 xdata Version_LED_Flag=0;
//u8 xdata State_LED_Flag=0;

//void Version_LED_Ser()
//{
//	static u16 xdata count=0;
//	if(Version_LED_Flag)
//	{
//		count++;
//		if(count==1)
//		{
//			LED_W=LED_Close;
//		}
//		if(count==1000)
//		{
//			LED_W=LED_Open;
//			
//		}
//		if(count==2000)
//		{
//			LED_W=LED_Close;
//			Version_LED_Flag--;
//			count=0;
//		}
//	}
//}
//void State_LED_Ser()
//{
//	static u16 xdata count=0;
//	if(State_LED_Flag)
//	{
//		count++;
//		if(count==1000)
//		{
//			LED_W=LED_Close;
//		}
//		if(count==2000)
//		{
//			LED_W=LED_Open;
//			State_LED_Flag--;
//			count=0;
//		}
//	}
//}
//void LED_Ser()
//{
//	Version_LED_Ser();
//	State_LED_Ser();
//}