#include "all.h"

u8 xdata Read_Byte_key=KEY_NO;
u8 xdata Key_Save=0;

void KEY_Init()
{
	KEY_Run=1;
}

void KEY_Scan_Ser()
{
	static xdata u8 count=0,key_flag=1;
	
	if(KEY_Run==0 && key_flag==1)
	{
		count++;
		if(count>200)
		{
			count=0;
			if(KEY_Run==0)
			{
				key_flag=0;
				if(Run_Flag)
				{
					if(RS485_Flag==0 && RS485_Busy==0)
					{
						Read_Byte_key=KEY_M;	
						RS485_Flag=1;
						Key_Save = KEY_M;
					}
				}
				else
				{
					if(RS485_Flag==0 && RS485_Busy==0)
					{
						Read_Byte_key=KEY_S;	
						RS485_Flag=1;
						Key_Save = KEY_S;
					}
				}	
			}
		}
	}
	else if(KEY_Run==1)
	{
		key_flag=1;
	}
}


