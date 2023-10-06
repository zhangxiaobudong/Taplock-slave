#include "all.h"

u8  xdata RS485_Up_Num_Buffer[15]=0;
u8  xdata RS485_Flag=0;
bit idata RS485_Busy=0;
u8  xdata RxLen=0;
u16 xdata send_cnt=0;
bit idata Slave_NO_ONE=1;
u8  xdata Front_Device_Return=0;
u8  xdata Current_Device_Return=0;
u8  xdata Data_END_Flag=0;

void RS485_Init()
{
	SCON=0x50;
	AUXR|=0x05;	
	T2H=0xFC;
	T2L=0xF3;
	AUXR|=0x10;	
	
	ES=1;
	EA=1;
	
	RS485_ReadWrite=RS485_RX;
	if(EEPROM_Read_Byte_Drive(4,1) == 1)
	{
		Slave_NO_ONE=1;
	}
	else
	{
		Slave_NO_ONE=0;
	}
}

void RS485_Rountine() interrupt 4
{
	if(RI)
	{
		RI=0;
		RS485_Busy=1;
		RS485_Up_Num_Buffer[RxLen]=SBUF;
		RxLen++;
		send_cnt=0;
	}
	else  if(TI)
	{
		TI=0;
		RS485_Flag=1;
	}			
}
void RS485_TX_Drive()	//RS485发送底层函数
{
	static u8 xdata count=0,num=0;
//	if(RS485_Flag==1)
//	{
		RS485_ReadWrite=RS485_TX;
		count++;
		switch(count)
		{	//RS485从接收状态切换到发送状态，需要延迟，所以从计数11开始
			case 11:SBUF=0xB4;RS485_Flag=0; break;
			case 12:SBUF=0xD3;RS485_Flag=0; break;
			case 13:SBUF=EEPROM_Read_Byte_Drive(4,0);RS485_Flag=0; break;	//从机组别
			case 14:SBUF=EEPROM_Read_Byte_Drive(4,1);RS485_Flag=0; break;	//主机ID
			case 15:SBUF=Key_Save;RS485_Flag=0;break;	//按键指令
					 
			case 16:
//					if(Key_Save==Cmd_Data || Key_Save==Cmd_Data_End)	//运行次数
//					{
						SBUF=Run_Num;
						RS485_Flag=0;
//					} 
					break;	
			case 17:
//					if(Key_Save==Cmd_Data)	//故障码
//					{
						SBUF=Run_State;
						RS485_Flag=0;
//					} 
					break;
			case 18:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//霍尔电流(出)
					{
						if(Hall_Open==Open)
							SBUF=Hall_Current_Buf[0];
						else if(Hall_Open==Close)
							SBUF=0;
						RS485_Flag=0;
					} 
					else
					{
						count=22;//直接跳转到发送0D  0A
					}
					break;
			case 19:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//霍尔电流(进)
					{
						if(Hall_Open==Open)
							SBUF=Hall_Current_Buf[1];
						else if(Hall_Open==Close)
							SBUF=0;
						RS485_Flag=0;
					} 
					break;
			case 20:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//电流基准值
					{
						SBUF=ADC_Reference;
						RS485_Flag=0;
					} 
					break;
			case 21:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//霍尔电流
					{
						SBUF=Motor_Current_Buf[num];
						RS485_Flag=0;
						num++;
						if(num<Current_type)	
						{
							count=20;		//等会再进来+1后再次回到这里，循环发送
						}
						else
						{
							num=0;	//清零，不影响下一轮数据发送
						}
					} 
					break;		
			case 22:SBUF=0x0D;RS485_Flag=0; break;	//回车
			case 23:SBUF=0x0A;RS485_Flag=0; break;	//换行

			case 24:count=0;RS485_Flag=0;RS485_ReadWrite=RS485_RX;break;
		}
//	}
}
void RS485_RX_Drive()	//RS485接收底层函数
{
	u8 i;
	
	send_cnt++;    //只要有数据接收，send_cnt每次都被串口中断清零
	if(send_cnt>200)   //延时一段时间，确认缓冲区没有继续接受数据
	{
		send_cnt=0;
		RS485_Busy=0;
		RxLen=0;
		for(i=0;i<7;i++)
		{
			//检验数据头(主 D6  F7) H和尾(0D  0A)
			if(RS485_Up_Num_Buffer[i]==0xD6 && RS485_Up_Num_Buffer[i+1]==0xF7 && RS485_Up_Num_Buffer[i+5]==0x0D && RS485_Up_Num_Buffer[i+6]==0x0A)
			{
				switch(RS485_Up_Num_Buffer[i+4])
				{
					case Cmd_RUN:break;		//开始运行成功,N秒后开始询问是否完成
					case Cmd_STOP:break;		//停止运行成功,停止询问	
					case Cmd_Version:	
							{
								if(Run_Flag==0)	//停止状态才能切换版本
								{
									Version %= 3;
									Version++;
									EEPROM_Wipe512_Drive(2);
									EEPROM_Write_Byte_Drive(2,0,Version);
									switch(Version)
									{
										case 1:	Run_Timer=30;				//30*10=300MS运行时间
												Stop_Timer=50;				//80*10=800MS停止时间
												Stable_Motor_Current=800;	//电机稳定电流
												Hall_Open=Open;			//是否打开霍尔电流检测
												Motor_Open=Open;		//是否打开电机电流检测
												Hall_KEY=Open;			//是否打开霍尔开关检测
												break;
										case 2:	Run_Timer=80;				//80*10=800MS运行时间
												Stop_Timer=20;				//20*10=200MS停止时间
												Stable_Motor_Current=550;	//电机稳定电流
												Hall_Open=Open;			//是否打开霍尔电流检测
												Motor_Open=Open;		//是否打开电机电流检测
												Hall_KEY=Open;			//是否打开霍尔开关检测
												break;
										case 3:	Run_Timer=80;				//80*10=800MS运行
												Stop_Timer=20;				//20*10=200MS停止时间
												Stable_Motor_Current=800;	//电机稳定电流
												Hall_Open=Close;		//是否打开霍尔电流检测
												Motor_Open=Open;		//是否打开电机电流检测
												Hall_KEY=Open;			//是否打开霍尔开关检测
												break;
									}
									if(Slave_NO_ONE)	//设备1号机代替反馈
									{
										RS485_Flag=1;			//应答主机
										Key_Save = Cmd_V_YES;	//切换版本成功
									}
								}
								else			//不是停止状态，上报切换版本失败
								{
									if(Slave_NO_ONE)	//设备1号机代替反馈
									{
										RS485_Flag=1;			//应答主机
										Key_Save = Cmd_V_NO;	//切换版本失败
									}
								}
							}
							break;
					case Cmd_Data:
							RS485_Num++;
							if(RS485_Up_Num_Buffer[i+3]==EEPROM_Read_Byte_Drive(4,1))//返回的是当前设备数据，停止END计数
							{  
								if(RS485_Up_Num_Buffer[i+3]==10)	//第10个数据传输完毕,发送结束命令
								{
									Current_Device_Return=2;
								}
								else								//不是第10个数据，等待结束命令
								{
									Current_Device_Return=1;									
								}
							}
							else if(RS485_Up_Num_Buffer[i+3]+1==EEPROM_Read_Byte_Drive(4,1))//上一个传输结束，准备传输下一个数据
							{
								Front_Device_Return=1;	//等待锁跑完100次或者200次										
							}
							break;
				}	
				break;	//跳出for循环
			}
				//检验数据头(从 B4  D3) H和尾(0D  0A)
			else if(RS485_Up_Num_Buffer[i]==0xB4 && RS485_Up_Num_Buffer[i+1]==0xD3 && RS485_Up_Num_Buffer[i+7]==0x0D && RS485_Up_Num_Buffer[i+8]==0x0A)
			{
				switch(RS485_Up_Num_Buffer[i+4])
				{
					case Cmd_RUN:Read_Byte_key=KEY_S;break;		//开始运行成功,N秒后开始询问是否完成									
					case Cmd_STOP:Read_Byte_key=KEY_M;break;	//停止运行成功,停止询问									
//						case Cmd_V_YES:break;					//切换版本成功
//						case Cmd_V_NO:break;					//切换版本失败									
//					case Cmd_Data:Data_count=Data_Clear;break;	//其他从机传输数据
//						case Cmd_NO_ID:break;					//其他从机没有插入锁
					case Cmd_Data_End:Data_END_Flag=1;break;//接收到数据上传完毕指令
				}
				break;	//跳出for循环				
			}
		}
	}
}
void RS485_Data_Drive()//RS485数据处理
{
	if(RS485_Busy==1)  //说明目前串口正在接收数据，不要读缓冲区数据
	{
		RS485_RX_Drive();	//RS485接收底层函数		
	}
	else if(RS485_Flag==1)	//没有接收数据，随时准备发送数据指令	
	{
		RS485_TX_Drive();	//RS485发送底层函数
	}
}
