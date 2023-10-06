#include "all.h"
u8  xdata RS485_Num=0;
u8  xdata Run_Flag=0;			//运行标志
u8  xdata Run_State=0;			//运行故障标志
u16 xdata Data_count=0;			//运行结束计数
u8  xdata Run_OK_200=0;			//运行200次完成标志
u16 xdata Mach_Count=0;			//电机驱动延时计数
u8  xdata Set_Num=Set_Num2;		//设置次数
u8  xdata Run_Num=0;			//运行记数
u8  xdata Version=3;			//版本（1= 一代锁，  2= 二代锁，  3=三代锁）
bit idata Hall_Open;			//是否检测霍尔电流（1=检测， 0=不检测）
bit idata Motor_Open;			//是否检测电机电流（1=检测， 0=不检测）
bit idata Hall_KEY;				//是否检测霍尔开关（1=检测， 0=不检测）
bit idata Limit_KEY;			//是否检测限位开关（1=检测， 0=不检测）
u8  xdata Run_Timer;		
u8  xdata Stop_Timer;
u16 xdata Stable_Motor_Current;
u8  xdata Motor_Current_Buf[Current_type];//0-79->电机电流(进)，80-159->电机电流(出)
u8  xdata Hall_Current_Buf[2];//0->霍尔电流(进)，1->霍尔电流(出)

void Timer0_Routine() interrupt 1 using 1
{
	Mach_Count++;
}
void System_Init()		//定时5MS/30MHZ
{	
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
//	TL0 = 0x58;			//设置定时初值		//10ms
//	TH0 = 0x9E;			//设置定时初值
	
	TL0 = 0x2C;			//设置定时初值		//5ms
	TH0 = 0xCF;			//设置定时初值
	TR0 = 1;			//定时器0开始计时
	ET0 = 1;
	EA = 1;
	
	LED_W=LED_Close;
	Mach1_Stop;
	Hall=1;
	Limit=1;
	
	Version = EEPROM_Read_Byte_Drive(2,0);
	switch(Version)
	{
		case 1:	Run_Timer=30;				//30*10=300MS运行时间
				Stop_Timer=50;				//80*10=800MS停止时间
				Stable_Motor_Current=800;	//电机稳定电流
				Hall_Open=Open;				//是否打开霍尔电流检测
				Motor_Open=Open;			//是否打开电机电流检测
				Hall_KEY=Open;				//是否打开霍尔开关检测
				break;
		case 2:	Run_Timer=80;				//80*10=800MS运行时间
				Stop_Timer=20;				//20*10=200MS停止时间
				Stable_Motor_Current=550;	//电机稳定电流
				Hall_Open=Open;				//是否打开霍尔电流检测
				Motor_Open=Open;			//是否打开电机电流检测
				Hall_KEY=Open;				//是否打开霍尔开关检测
				break;
		case 3:	Run_Timer=80;				//80*10=800MS运行
				Stop_Timer=20;				//20*10=200MS停止时间
				Stable_Motor_Current=800;	//电机稳定电流
				Hall_Open=Close;			//是否打开霍尔电流检测
				Motor_Open=Open;			//是否打开电机电流检测
				Hall_KEY=Open;				//是否打开霍尔开关检测
				break;
	}
}
u8 Motor_Current_Detection(u8 Fault_Code)	//电机电流检测  Fault_Code==故障码
{
	u8 value=0;
	static u8  xdata count=0;
	if(Motor_Open)
	{	
		Motor_Current_Calculate();	//捕获电机电流
		if(Motor_Current>Stable_Motor_Current)
		{
			count++;
			if(count>=9)
			{
				value=Fault_Code;
				return value;
			}
		}
		else
		{
			count=0;
		}					
	}
	if(Mach_Count>=Run_Timer)
	{
		count=0;
	}
	return value;
}
u8 Hall_Current_Detection(u8 Dete, u8 Fault_Code, u8 Fault_Code1,u8 Fault_Code2)	//霍尔电流检测
{
	u8 value=0;
	if(Mach_Count > 6)
	{
		if(Hall_KEY) 
		{		
			if(Hall != Dete) 
			{
				value |= Fault_Code;
			}
		}
		if(Limit_KEY) 
		{		
			if(Limit == Dete) 
			{
				value |= Fault_Code2;
			}
		}
		if(Hall_Open)
		{
			Hall_Current_Calculate();	//捕获霍尔电流
			if(Dete==Dete_YES)
			{
//				if((Hall_Current>7) || (Hall_Current<3) )	//霍尔电流4-7MA,如果不符合则电流计数清除
				if((Hall_Current>8) || (Hall_Current<5) )	//霍尔电流5-8MA,如果不符合则电流计数清除
				{
					value |= Fault_Code1;
				}
			}	
			else if(Dete==Dete_NO)
			{
//				if((Hall_Current>3) || (Hall_Current<1) )	//霍尔电流1-3MA,如果不符合则电流计数清除
				if((Hall_Current>4) || (Hall_Current<1) )	//霍尔电流1-4MA,如果不符合则电流计数清除
				{
					value |= Fault_Code1;
				}
			}
		}
	}
	return value;
}
void Mach_Run_Scan()
{
	static u8 xdata Mode=0,Count_Save=0;
	static bit idata One_Flag=0;
	
	switch(Run_Flag)
	{
		case 0:Mode=0;Mach_Count=0;Count_Save=0;break;
		case 1:	//开始时气缸动作
			{	
				switch(Mode)									
				{									
					case 0:	
						Cylinder_Ser(Rear,Open);	//打开固定气缸
						if(Mach_Count>=Stop_Timer*2)	
						{
							Mode=1;					//进入状态1
							Count_Save=0;
							Mach_Count=0;			//清除计数方便下次计数	
						}					
						break;
					case 1:	
						Mach1_Left;//电机缩回
						if(Count_Save != Mach_Count)	//每隔10MS检测一次
						{
							Count_Save = Mach_Count;
							Motor_Current_Calculate();		//捕捉电机电流值
							Motor_Current_Buf[Count_Save]=ADC_Read_Byte;								
						}
						if(Mach_Count>=Run_Timer*2)						
						{
							Mode=2;			//进入状态2
							Count_Save=0;
							Mach_Count=0;	//清除计数方便下次计数
						}
						break;
					case 2: 
						Mach1_Stop;				//电机停转											
						if(Mach_Count>=Stop_Timer*2)			//电机停转
						{		
							Mode=3;							//进入状态3		
							Count_Save=0;
							Mach_Count=0;					//清除计数方便下次计数
						}	
						break;
					case 3:	
						Cylinder_Ser(Front,Close);	//关闭限位气缸
						Cylinder_Ser(Side,Close);	//关闭行程气缸
						if(Mach_Count>=Stop_Timer*2)	
						{
							Mode=0;					//进入状态0
							Mach_Count=0;			//清除计数方便下次计数
							Count_Save=0;
							Run_Flag=4;				//运行第二阶段
						}					
						break;
					}					
			}
			break;
		case 2:	//100次结束气缸动作
			{
				switch(Mode)								
				{	
					case 0://等待其他设备反应
						if(Mach_Count>=Run_Timer*2)	
						{
							Mode=1;			//进入状态1
							Mach_Count=0;	//清除计数方便下次计数
						}
						break;
					case 1:			
						Cylinder_Ser(Side,Open);	//打开行程气缸
						if(Mach_Count>=Run_Timer*2)	
						{
							Mode=2;			//进入状态2
							Mach_Count=0;	//清除计数方便下次计数
						}
						break;
					case 2:	
						Cylinder_Ser(Front,Open);	//打开限位气缸
						Cylinder_Ser(Rear,Open);	//打开固定气缸
						if(Mach_Count>=Run_Timer*2)	
						{
							Mode=0;			//进入状态0
							Mach_Count=0;	//清除计数方便下次计数
							Run_Flag=4;					//运行第二阶段
						}
						break;
				}					
			}
			break;
		case 3:	//200次结束气缸动作
			{	
				if(One_Flag==0)	//按键停止第一次需进入清理Mode
				{
					One_Flag=1;
					Mode=0;
				}
				else
				{
					switch(Mode)								
					{	
						case 0://等待其他设备反应
							if(Mach_Count>=Run_Timer*2)	
							{
								Mode=1;			//进入状态1
								Mach_Count=0;	//清除计数方便下次计数
								Count_Save=0;
							}
							break;
						case 1:	
							Cylinder_Ser(Front,Close);	//关闭硬限位气缸
							Cylinder_Ser(Rear,Close);	//关闭固定气缸
							Mach1_Left;					//电机缩回
							if(Mach_Count>=Run_Timer*2)	//电机缩回
							{
								Mode=2;					//进入状态1
								Mach_Count=0;			//清除计数方便下次计数						
							}					
							break;
						case 2:		
							Mach1_Stop;						//电机停转	
							if(Mach_Count>=Stop_Timer*2)		//电机停转
							{		
								Mode=3;						//进入状态2
								Mach_Count=0;				//清除计数方便下次计数
							}
							break;
						case 3:	
							Cylinder_Ser(Side,Close);	//关闭行程气缸
							if(Mach_Count>=Stop_Timer*2)	
							{
								Mode=4;			//进入状态3
								Mach_Count=0;	//清除计数方便下次计数
							}
							break;
						case 4:	
							Mach1_Right;
							if(Mach_Count>=Run_Timer*2)	//电机伸出
							{
								Mode=5;			//进入状态4
								Mach_Count=0;	//清除计数方便下次计数
							}
							break;
						case 5: 
							Mach1_Stop;				//电机停转											
							if(Mach_Count>=Stop_Timer*2)			//电机停转
							{		
								Mode=0;							//进入状态0				
								Mach_Count=0;					//清除计数方便下次计数								
								Run_Flag=0;
								One_Flag=0;
								if(Run_Num>=Set_Num2)
									Run_OK_200=1;					//运行完成标志								
							}	
							break;			
						}		
					}
			}
			break;
		case 4:	//循环运行
			{	
				switch(Mode)								
				{			
					case 0:	
						Mach1_Right;						//电机伸出
						if(Count_Save != Mach_Count)	//每隔10MS检测一次
						{
							Count_Save = Mach_Count;
							Run_State |= Motor_Current_Detection(0x10);//电机电流检测
						}						
						if(Mach_Count>=Run_Timer*2)	//电机缩回
						{
							Mode=1;					//进入状态1
							Count_Save=0;
							Mach_Count=0;			//清除计数方便下次计数							
						}					
						break;
					case 1:		
						Mach1_Stop;						//电机停转	
						if(Count_Save != Mach_Count)	//每隔10MS检测一次
						{
							Count_Save = Mach_Count;
							Run_State |= Hall_Current_Detection(Dete_NO, 0x01, 0x04, 0x40);//霍尔电流检测
//							Run_State |= Hall_Current_Detection(Dete_NO, 0x01, 0x04, 0x00);//霍尔电流检测							
							if(Run_Num==0)
							{
								Hall_Current_Buf[0]=Hall_Current;
							}
						}	
						
						if(Mach_Count>=Stop_Timer*2)			//电机停转
						{		
							Mode=2;							//进入状态2
							Count_Save=0;
							Mach_Count=0;					//清除计数方便下次计数
						}
						break;
					case 2:	
						Mach1_Left;//电机缩回	
						if(Count_Save != Mach_Count)	//每隔10MS检测一次
						{
							Count_Save = Mach_Count;
							Run_State |= Motor_Current_Detection(0x20);//电机电流检测
						}
						if(Mach_Count>=Run_Timer*2)						
						{
							Mode=3;			//进入状态3
							Count_Save=0;
							Mach_Count=0;	//清除计数方便下次计数
						}
						break;
					case 3: 
						Mach1_Stop;				//电机停转											
						if(Count_Save != Mach_Count)	//每隔10MS检测一次
						{
							Count_Save = Mach_Count;
							Run_State |= Hall_Current_Detection(Dete_YES, 0x02, 0x08,0x80);//霍尔电流检测
//							Run_State |= Hall_Current_Detection(Dete_YES, 0x02, 0x08,0x00);//霍尔电流检测
							if(Run_Num==0)
							{
								Hall_Current_Buf[1]=Hall_Current;
							}
						}	

						if(Mach_Count>=Stop_Timer*2)			//电机停转
						{		
							Mode=4;							//进入状态4		
							Count_Save=0;
							Mach_Count=0;					//清除计数方便下次计数
						}	
						break;		
					case 4:
						Run_Num++;						//运行次数+1
						if(Run_Num==Set_Num1 || Run_Num>=Set_Num2)	
						{
							Mode=5;							//进入状态5
							RS485_Num=0;
						}
						else
							Mode=0;							//进入状态0
						break;
					case 5:	
						if(Data_END_Flag)	//接收到结束命令
						{
							Front_Device_Return=0;
							Mode=0;
							Mach_Count=0;
							if(Run_Num==Set_Num1)
							{
								Run_Flag=2;	
								Limit_KEY=Close;
							}
							else if(Run_Num==Set_Num2)
							{
								Run_Flag=3;								
							}
						}
						else if(Slave_NO_ONE || Front_Device_Return==1)	//设备1号机第一个传输,或者后续设备进入等待状态
						{
							Mach_Count=0;
							Mode=6;	
							Front_Device_Return=0;
							if((Version!=3 && Run_State==0x7E) || (Version==3 && Run_State==0x72))		//没有插入锁会报故障0x7E
							{
								RS485_Flag=1;				//应答主机
								Key_Save = Cmd_NO_ID;		//发送没有锁指令
							}
							else						//有插龙头锁
							{
								RS485_Flag=1;				//应答主机
								Key_Save = Cmd_Data;		//传输数据指令
							}	
//							if(Hall==0)			//此时锁舌在缩回状态，所以Hall==0表示有插龙头锁
//							{
//								RS485_Flag=1;				//应答主机
//								Key_Save = Cmd_Data;		//传输数据指令
//							}
//							else				//没有插龙头锁
//							{
//								RS485_Flag=1;				//应答主机
//								Key_Save = Cmd_NO_ID;		//发送没有锁指令
//							}							
						}
						break;
					case 6:
						if(Current_Device_Return==1)	//当前设备已返回,等待结束命令
						{
							if(Data_END_Flag)		//接收到结束命令
							{
								Current_Device_Return=0;
								Data_END_Flag=0;
								Mode=0;
								Mach_Count=0;
								if(Run_Num==Set_Num1)
								{
									Run_Flag=2;
									Limit_KEY=Close;
								}
								else if(Run_Num==Set_Num2)
								{
									Run_Flag=3;								
								}
							}
						}
						else if(Mach_Count>=800 || Current_Device_Return==2)	//2秒后未返回，则发送结束命令
						{
							Current_Device_Return=0;
							Mode=0;
							Mach_Count=0;
							if(Run_Num==Set_Num1)
							{
								Run_Flag=2;	
								Limit_KEY=Close;
							}
							else if(Run_Num==Set_Num2)
							{
								Run_Flag=3;								
							}
//							if(Slave_NO_ONE)	//设备1号机代替反馈
//							{
								RS485_Flag=1;				//应答主机
								Key_Save = Cmd_Data_End;	//传输结束指令
//							}
						}	
						break;							
				}					
			}
			break;
	}
}
