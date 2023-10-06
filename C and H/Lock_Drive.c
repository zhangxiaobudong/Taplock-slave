#include "all.h"
u8  xdata RS485_Num=0;
u8  xdata Run_Flag=0;			//���б�־
u8  xdata Run_State=0;			//���й��ϱ�־
u16 xdata Data_count=0;			//���н�������
u8  xdata Run_OK_200=0;			//����200����ɱ�־
u16 xdata Mach_Count=0;			//���������ʱ����
u8  xdata Set_Num=Set_Num2;		//���ô���
u8  xdata Run_Num=0;			//���м���
u8  xdata Version=3;			//�汾��1= һ������  2= ��������  3=��������
bit idata Hall_Open;			//�Ƿ������������1=��⣬ 0=����⣩
bit idata Motor_Open;			//�Ƿ�����������1=��⣬ 0=����⣩
bit idata Hall_KEY;				//�Ƿ���������أ�1=��⣬ 0=����⣩
bit idata Limit_KEY;			//�Ƿ�����λ���أ�1=��⣬ 0=����⣩
u8  xdata Run_Timer;		
u8  xdata Stop_Timer;
u16 xdata Stable_Motor_Current;
u8  xdata Motor_Current_Buf[Current_type];//0-79->�������(��)��80-159->�������(��)
u8  xdata Hall_Current_Buf[2];//0->��������(��)��1->��������(��)

void Timer0_Routine() interrupt 1 using 1
{
	Mach_Count++;
}
void System_Init()		//��ʱ5MS/30MHZ
{	
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
//	TL0 = 0x58;			//���ö�ʱ��ֵ		//10ms
//	TH0 = 0x9E;			//���ö�ʱ��ֵ
	
	TL0 = 0x2C;			//���ö�ʱ��ֵ		//5ms
	TH0 = 0xCF;			//���ö�ʱ��ֵ
	TR0 = 1;			//��ʱ��0��ʼ��ʱ
	ET0 = 1;
	EA = 1;
	
	LED_W=LED_Close;
	Mach1_Stop;
	Hall=1;
	Limit=1;
	
	Version = EEPROM_Read_Byte_Drive(2,0);
	switch(Version)
	{
		case 1:	Run_Timer=30;				//30*10=300MS����ʱ��
				Stop_Timer=50;				//80*10=800MSֹͣʱ��
				Stable_Motor_Current=800;	//����ȶ�����
				Hall_Open=Open;				//�Ƿ�򿪻����������
				Motor_Open=Open;			//�Ƿ�򿪵���������
				Hall_KEY=Open;				//�Ƿ�򿪻������ؼ��
				break;
		case 2:	Run_Timer=80;				//80*10=800MS����ʱ��
				Stop_Timer=20;				//20*10=200MSֹͣʱ��
				Stable_Motor_Current=550;	//����ȶ�����
				Hall_Open=Open;				//�Ƿ�򿪻����������
				Motor_Open=Open;			//�Ƿ�򿪵���������
				Hall_KEY=Open;				//�Ƿ�򿪻������ؼ��
				break;
		case 3:	Run_Timer=80;				//80*10=800MS����
				Stop_Timer=20;				//20*10=200MSֹͣʱ��
				Stable_Motor_Current=800;	//����ȶ�����
				Hall_Open=Close;			//�Ƿ�򿪻����������
				Motor_Open=Open;			//�Ƿ�򿪵���������
				Hall_KEY=Open;				//�Ƿ�򿪻������ؼ��
				break;
	}
}
u8 Motor_Current_Detection(u8 Fault_Code)	//����������  Fault_Code==������
{
	u8 value=0;
	static u8  xdata count=0;
	if(Motor_Open)
	{	
		Motor_Current_Calculate();	//����������
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
u8 Hall_Current_Detection(u8 Dete, u8 Fault_Code, u8 Fault_Code1,u8 Fault_Code2)	//�����������
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
			Hall_Current_Calculate();	//�����������
			if(Dete==Dete_YES)
			{
//				if((Hall_Current>7) || (Hall_Current<3) )	//��������4-7MA,���������������������
				if((Hall_Current>8) || (Hall_Current<5) )	//��������5-8MA,���������������������
				{
					value |= Fault_Code1;
				}
			}	
			else if(Dete==Dete_NO)
			{
//				if((Hall_Current>3) || (Hall_Current<1) )	//��������1-3MA,���������������������
				if((Hall_Current>4) || (Hall_Current<1) )	//��������1-4MA,���������������������
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
		case 1:	//��ʼʱ���׶���
			{	
				switch(Mode)									
				{									
					case 0:	
						Cylinder_Ser(Rear,Open);	//�򿪹̶�����
						if(Mach_Count>=Stop_Timer*2)	
						{
							Mode=1;					//����״̬1
							Count_Save=0;
							Mach_Count=0;			//������������´μ���	
						}					
						break;
					case 1:	
						Mach1_Left;//�������
						if(Count_Save != Mach_Count)	//ÿ��10MS���һ��
						{
							Count_Save = Mach_Count;
							Motor_Current_Calculate();		//��׽�������ֵ
							Motor_Current_Buf[Count_Save]=ADC_Read_Byte;								
						}
						if(Mach_Count>=Run_Timer*2)						
						{
							Mode=2;			//����״̬2
							Count_Save=0;
							Mach_Count=0;	//������������´μ���
						}
						break;
					case 2: 
						Mach1_Stop;				//���ͣת											
						if(Mach_Count>=Stop_Timer*2)			//���ͣת
						{		
							Mode=3;							//����״̬3		
							Count_Save=0;
							Mach_Count=0;					//������������´μ���
						}	
						break;
					case 3:	
						Cylinder_Ser(Front,Close);	//�ر���λ����
						Cylinder_Ser(Side,Close);	//�ر��г�����
						if(Mach_Count>=Stop_Timer*2)	
						{
							Mode=0;					//����״̬0
							Mach_Count=0;			//������������´μ���
							Count_Save=0;
							Run_Flag=4;				//���еڶ��׶�
						}					
						break;
					}					
			}
			break;
		case 2:	//100�ν������׶���
			{
				switch(Mode)								
				{	
					case 0://�ȴ������豸��Ӧ
						if(Mach_Count>=Run_Timer*2)	
						{
							Mode=1;			//����״̬1
							Mach_Count=0;	//������������´μ���
						}
						break;
					case 1:			
						Cylinder_Ser(Side,Open);	//���г�����
						if(Mach_Count>=Run_Timer*2)	
						{
							Mode=2;			//����״̬2
							Mach_Count=0;	//������������´μ���
						}
						break;
					case 2:	
						Cylinder_Ser(Front,Open);	//����λ����
						Cylinder_Ser(Rear,Open);	//�򿪹̶�����
						if(Mach_Count>=Run_Timer*2)	
						{
							Mode=0;			//����״̬0
							Mach_Count=0;	//������������´μ���
							Run_Flag=4;					//���еڶ��׶�
						}
						break;
				}					
			}
			break;
		case 3:	//200�ν������׶���
			{	
				if(One_Flag==0)	//����ֹͣ��һ�����������Mode
				{
					One_Flag=1;
					Mode=0;
				}
				else
				{
					switch(Mode)								
					{	
						case 0://�ȴ������豸��Ӧ
							if(Mach_Count>=Run_Timer*2)	
							{
								Mode=1;			//����״̬1
								Mach_Count=0;	//������������´μ���
								Count_Save=0;
							}
							break;
						case 1:	
							Cylinder_Ser(Front,Close);	//�ر�Ӳ��λ����
							Cylinder_Ser(Rear,Close);	//�رչ̶�����
							Mach1_Left;					//�������
							if(Mach_Count>=Run_Timer*2)	//�������
							{
								Mode=2;					//����״̬1
								Mach_Count=0;			//������������´μ���						
							}					
							break;
						case 2:		
							Mach1_Stop;						//���ͣת	
							if(Mach_Count>=Stop_Timer*2)		//���ͣת
							{		
								Mode=3;						//����״̬2
								Mach_Count=0;				//������������´μ���
							}
							break;
						case 3:	
							Cylinder_Ser(Side,Close);	//�ر��г�����
							if(Mach_Count>=Stop_Timer*2)	
							{
								Mode=4;			//����״̬3
								Mach_Count=0;	//������������´μ���
							}
							break;
						case 4:	
							Mach1_Right;
							if(Mach_Count>=Run_Timer*2)	//������
							{
								Mode=5;			//����״̬4
								Mach_Count=0;	//������������´μ���
							}
							break;
						case 5: 
							Mach1_Stop;				//���ͣת											
							if(Mach_Count>=Stop_Timer*2)			//���ͣת
							{		
								Mode=0;							//����״̬0				
								Mach_Count=0;					//������������´μ���								
								Run_Flag=0;
								One_Flag=0;
								if(Run_Num>=Set_Num2)
									Run_OK_200=1;					//������ɱ�־								
							}	
							break;			
						}		
					}
			}
			break;
		case 4:	//ѭ������
			{	
				switch(Mode)								
				{			
					case 0:	
						Mach1_Right;						//������
						if(Count_Save != Mach_Count)	//ÿ��10MS���һ��
						{
							Count_Save = Mach_Count;
							Run_State |= Motor_Current_Detection(0x10);//����������
						}						
						if(Mach_Count>=Run_Timer*2)	//�������
						{
							Mode=1;					//����״̬1
							Count_Save=0;
							Mach_Count=0;			//������������´μ���							
						}					
						break;
					case 1:		
						Mach1_Stop;						//���ͣת	
						if(Count_Save != Mach_Count)	//ÿ��10MS���һ��
						{
							Count_Save = Mach_Count;
							Run_State |= Hall_Current_Detection(Dete_NO, 0x01, 0x04, 0x40);//�����������
//							Run_State |= Hall_Current_Detection(Dete_NO, 0x01, 0x04, 0x00);//�����������							
							if(Run_Num==0)
							{
								Hall_Current_Buf[0]=Hall_Current;
							}
						}	
						
						if(Mach_Count>=Stop_Timer*2)			//���ͣת
						{		
							Mode=2;							//����״̬2
							Count_Save=0;
							Mach_Count=0;					//������������´μ���
						}
						break;
					case 2:	
						Mach1_Left;//�������	
						if(Count_Save != Mach_Count)	//ÿ��10MS���һ��
						{
							Count_Save = Mach_Count;
							Run_State |= Motor_Current_Detection(0x20);//����������
						}
						if(Mach_Count>=Run_Timer*2)						
						{
							Mode=3;			//����״̬3
							Count_Save=0;
							Mach_Count=0;	//������������´μ���
						}
						break;
					case 3: 
						Mach1_Stop;				//���ͣת											
						if(Count_Save != Mach_Count)	//ÿ��10MS���һ��
						{
							Count_Save = Mach_Count;
							Run_State |= Hall_Current_Detection(Dete_YES, 0x02, 0x08,0x80);//�����������
//							Run_State |= Hall_Current_Detection(Dete_YES, 0x02, 0x08,0x00);//�����������
							if(Run_Num==0)
							{
								Hall_Current_Buf[1]=Hall_Current;
							}
						}	

						if(Mach_Count>=Stop_Timer*2)			//���ͣת
						{		
							Mode=4;							//����״̬4		
							Count_Save=0;
							Mach_Count=0;					//������������´μ���
						}	
						break;		
					case 4:
						Run_Num++;						//���д���+1
						if(Run_Num==Set_Num1 || Run_Num>=Set_Num2)	
						{
							Mode=5;							//����״̬5
							RS485_Num=0;
						}
						else
							Mode=0;							//����״̬0
						break;
					case 5:	
						if(Data_END_Flag)	//���յ���������
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
						else if(Slave_NO_ONE || Front_Device_Return==1)	//�豸1�Ż���һ������,���ߺ����豸����ȴ�״̬
						{
							Mach_Count=0;
							Mode=6;	
							Front_Device_Return=0;
							if((Version!=3 && Run_State==0x7E) || (Version==3 && Run_State==0x72))		//û�в������ᱨ����0x7E
							{
								RS485_Flag=1;				//Ӧ������
								Key_Save = Cmd_NO_ID;		//����û����ָ��
							}
							else						//�в���ͷ��
							{
								RS485_Flag=1;				//Ӧ������
								Key_Save = Cmd_Data;		//��������ָ��
							}	
//							if(Hall==0)			//��ʱ����������״̬������Hall==0��ʾ�в���ͷ��
//							{
//								RS485_Flag=1;				//Ӧ������
//								Key_Save = Cmd_Data;		//��������ָ��
//							}
//							else				//û�в���ͷ��
//							{
//								RS485_Flag=1;				//Ӧ������
//								Key_Save = Cmd_NO_ID;		//����û����ָ��
//							}							
						}
						break;
					case 6:
						if(Current_Device_Return==1)	//��ǰ�豸�ѷ���,�ȴ���������
						{
							if(Data_END_Flag)		//���յ���������
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
						else if(Mach_Count>=800 || Current_Device_Return==2)	//2���δ���أ����ͽ�������
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
//							if(Slave_NO_ONE)	//�豸1�Ż����淴��
//							{
								RS485_Flag=1;				//Ӧ������
								Key_Save = Cmd_Data_End;	//�������ָ��
//							}
						}	
						break;							
				}					
			}
			break;
	}
}
