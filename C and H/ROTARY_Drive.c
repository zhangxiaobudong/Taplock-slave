#include "all.h"

u16 xdata ROTARY_Read_Byte_ROTARY=10;
u8  xdata ROTARY_Read_Byte_key=ROTARY_KEY_NO;
u8  xdata Set_Num_Flag=0;
bit idata cursor_position=0;
//bit idata ROTARY_Flag=0;

void ROTARY_Init()
{
	ROTARY_MUTE=1;
	ROTARY_A=1;
	ROTARY_B=1;
}
void ROTARY_ROTARY_Scan_Drive()
{
	static bit idata ROTARY_Flag=0, Turn_Right=0, Turn_Left=0;
	if(cursor_position==1)
	{
		if(ROTARY_A&ROTARY_B)
		{
			ROTARY_Flag=1;
		}
		if(ROTARY_A!=ROTARY_B)
		{
			Turn_Right=ROTARY_A;
			Turn_Left=ROTARY_B;
		}
		if(ROTARY_Flag)
		{
			if((ROTARY_A==0)&&(ROTARY_B==0))
			{
				ROTARY_Flag=0;
				if(Set_Num_Flag)
				{
					
					if(Set_Num_Flag==3)
					{
						if(Turn_Left==0)
						{
							if(ROTARY_Read_Byte_ROTARY==0)
							{
								ROTARY_Read_Byte_ROTARY=5;
							}
							else 
							{
								ROTARY_Read_Byte_ROTARY--;
							}
						}
						if(Turn_Right==0)
						{
							if(ROTARY_Read_Byte_ROTARY>=5)
							{
								ROTARY_Read_Byte_ROTARY=0;
							}
							else 
							{
								ROTARY_Read_Byte_ROTARY++;
							}
						}
						Set_Num = ROTARY_Read_Byte_ROTARY*10000+(Set_Num%10000);
					}
					else if(Set_Num_Flag==4)
					{
						if(Turn_Left==0)
						{
							if(ROTARY_Read_Byte_ROTARY==0)
							{
								ROTARY_Read_Byte_ROTARY=9;
							}
							else 
							{
								ROTARY_Read_Byte_ROTARY--;
							}
						}
						if(Turn_Right==0)
						{
							if(ROTARY_Read_Byte_ROTARY>=9)
							{
								ROTARY_Read_Byte_ROTARY=0;
							}
							else 
							{
								ROTARY_Read_Byte_ROTARY++;
							}
						}
						Set_Num = ROTARY_Read_Byte_ROTARY*1000+(Set_Num/10000*10000)+(Set_Num%1000);
					}
					else if(Set_Num_Flag==5)
					{
						if(Turn_Left==0)
						{
							if(ROTARY_Read_Byte_ROTARY==0)
							{
								ROTARY_Read_Byte_ROTARY=9;
							}
							else 
							{
								ROTARY_Read_Byte_ROTARY--;
							}
						}
						if(Turn_Right==0)
						{
							if(ROTARY_Read_Byte_ROTARY>=9)
							{
								ROTARY_Read_Byte_ROTARY=0;
							}
							else 
							{
								ROTARY_Read_Byte_ROTARY++;
							}
						}
						Set_Num = ROTARY_Read_Byte_ROTARY*100+(Set_Num/1000*1000);
					}
				}
				else
				{
					if(Turn_Left==0)
					{
						if(ROTARY_Read_Byte_ROTARY==0)
						{
							ROTARY_Read_Byte_ROTARY=5;
						}
						else 
						{
							ROTARY_Read_Byte_ROTARY--;
						}
					}
					if(Turn_Right==0)
					{
						if(ROTARY_Read_Byte_ROTARY>=5)
						{
							ROTARY_Read_Byte_ROTARY=0;
						}
						else 
						{
							ROTARY_Read_Byte_ROTARY++;
						}
					}
				}
			}
		}
	}
}
void ROTARY_key_Scan_Drive()
{
	static xdata u8 Mode=0,Flag=0;
	static xdata u16 count1=0;
	static xdata u16 count2=0;
	switch(Mode)
	{
		case 0:
		{
			if(ROTARY_MUTE==0)
					Mode = 1;
		}
		break;
		case 1:
		{
			count1++;
			if(count1>50)
			{
				count1=0;
				if(ROTARY_MUTE)
					Mode = 0;
				else 
				{
//					ROTARY_Flag=1;
					Mode = 2;
				}
			}
		}
		break;
		case 2:
		{
			count1++;
			if(count1>5000)
			{
				count1=0;
				Mode = 4;
			}
			else
			{
				count2=count1;
				if(ROTARY_MUTE)
				{
					Mode=3;
					Flag++;
				}
			}
		}break;
		case 3:
		{
			count2++;
			if(count2>6000)
			{
				count2=0;
				Mode=4;
			}
			else
			{
				if((count2-count1)>500)
				{
					if(ROTARY_MUTE==0)
						Flag++;
				}
			}
		}break;
		case 4:
		{
			if(ROTARY_MUTE)
			{
				if(Flag>1)
				{
					Flag=0;
					Mode = 0;
//					ROTARY_Read_Byte_key=ROTARY_KEY_M;
				}
				else
				{
					Flag=0;
					Mode = 0;
					if(cursor_position==0)
					{
						if(Hall_Flag || Version==2)
						{
							Run_Flag=~Run_Flag;
							LED_W=1;
							if(Run_State || Run_OK)
							{
								Run_OK=0;
								Run_State=0;
								Run_Num=0;
							}
							if(Run_Flag)
							{
								LED_B=0;	//打开运行灯
							}
							else
							{
								LED_B=1;	//关闭运行灯
							}
						}
					}
					else
					{
						if(Run_Flag == 0) //不在运行状态才能设置
						{
							if(Set_Num_Flag)
							{
								ROTARY_Read_Byte_ROTARY = Set_Num_Flag;
								Set_Num_Flag=0;
							}
							else
							{
								switch(ROTARY_Read_Byte_ROTARY)
								{
									case 0:	Version++;Version %= 3;break;
									case 1:	Hall_Open=~Hall_Open;break;
									case 2:	Motor_Open=~Motor_Open;break;
									case 3:	Set_Num_Flag=ROTARY_Read_Byte_ROTARY;
											ROTARY_Read_Byte_ROTARY=Set_Num/10000;
											break;
									case 4:	Set_Num_Flag=ROTARY_Read_Byte_ROTARY;
											ROTARY_Read_Byte_ROTARY=Set_Num%10000/1000;
											break;		
									case 5:	Set_Num_Flag=ROTARY_Read_Byte_ROTARY;
											ROTARY_Read_Byte_ROTARY=Set_Num%1000/100;
											break;	
								}
							}
						}
					}
//					ROTARY_Read_Byte_key=ROTARY_KEY_S;
				}
			}				
			else 
			{
				Flag=0;
				Mode = 5;
				if(Run_Flag == 0) //不在运行状态才能设置
				{
					cursor_position = ~cursor_position;
					if(cursor_position)
					{
						ROTARY_Read_Byte_ROTARY=0;
					}
					else
					{
						ROTARY_Read_Byte_ROTARY=10;
						Set_Num_Flag=0;
					}
				}				
//				ROTARY_Read_Byte_key=ROTARY_KEY_L;
			}
//			ROTARY_Flag=0;
		}
		break;
		case 5:
		{
			if(ROTARY_MUTE)
				Mode = 0;
		}
		break;
	}
}