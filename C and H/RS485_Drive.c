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
void RS485_TX_Drive()	//RS485���͵ײ㺯��
{
	static u8 xdata count=0,num=0;
//	if(RS485_Flag==1)
//	{
		RS485_ReadWrite=RS485_TX;
		count++;
		switch(count)
		{	//RS485�ӽ���״̬�л�������״̬����Ҫ�ӳ٣����ԴӼ���11��ʼ
			case 11:SBUF=0xB4;RS485_Flag=0; break;
			case 12:SBUF=0xD3;RS485_Flag=0; break;
			case 13:SBUF=EEPROM_Read_Byte_Drive(4,0);RS485_Flag=0; break;	//�ӻ����
			case 14:SBUF=EEPROM_Read_Byte_Drive(4,1);RS485_Flag=0; break;	//����ID
			case 15:SBUF=Key_Save;RS485_Flag=0;break;	//����ָ��
					 
			case 16:
//					if(Key_Save==Cmd_Data || Key_Save==Cmd_Data_End)	//���д���
//					{
						SBUF=Run_Num;
						RS485_Flag=0;
//					} 
					break;	
			case 17:
//					if(Key_Save==Cmd_Data)	//������
//					{
						SBUF=Run_State;
						RS485_Flag=0;
//					} 
					break;
			case 18:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//��������(��)
					{
						if(Hall_Open==Open)
							SBUF=Hall_Current_Buf[0];
						else if(Hall_Open==Close)
							SBUF=0;
						RS485_Flag=0;
					} 
					else
					{
						count=22;//ֱ����ת������0D  0A
					}
					break;
			case 19:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//��������(��)
					{
						if(Hall_Open==Open)
							SBUF=Hall_Current_Buf[1];
						else if(Hall_Open==Close)
							SBUF=0;
						RS485_Flag=0;
					} 
					break;
			case 20:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//������׼ֵ
					{
						SBUF=ADC_Reference;
						RS485_Flag=0;
					} 
					break;
			case 21:if(Key_Save==Cmd_Data && Run_Num==Set_Num2)	//��������
					{
						SBUF=Motor_Current_Buf[num];
						RS485_Flag=0;
						num++;
						if(num<Current_type)	
						{
							count=20;		//�Ȼ��ٽ���+1���ٴλص����ѭ������
						}
						else
						{
							num=0;	//���㣬��Ӱ����һ�����ݷ���
						}
					} 
					break;		
			case 22:SBUF=0x0D;RS485_Flag=0; break;	//�س�
			case 23:SBUF=0x0A;RS485_Flag=0; break;	//����

			case 24:count=0;RS485_Flag=0;RS485_ReadWrite=RS485_RX;break;
		}
//	}
}
void RS485_RX_Drive()	//RS485���յײ㺯��
{
	u8 i;
	
	send_cnt++;    //ֻҪ�����ݽ��գ�send_cntÿ�ζ��������ж�����
	if(send_cnt>200)   //��ʱһ��ʱ�䣬ȷ�ϻ�����û�м�����������
	{
		send_cnt=0;
		RS485_Busy=0;
		RxLen=0;
		for(i=0;i<7;i++)
		{
			//��������ͷ(�� D6  F7) H��β(0D  0A)
			if(RS485_Up_Num_Buffer[i]==0xD6 && RS485_Up_Num_Buffer[i+1]==0xF7 && RS485_Up_Num_Buffer[i+5]==0x0D && RS485_Up_Num_Buffer[i+6]==0x0A)
			{
				switch(RS485_Up_Num_Buffer[i+4])
				{
					case Cmd_RUN:break;		//��ʼ���гɹ�,N���ʼѯ���Ƿ����
					case Cmd_STOP:break;		//ֹͣ���гɹ�,ֹͣѯ��	
					case Cmd_Version:	
							{
								if(Run_Flag==0)	//ֹͣ״̬�����л��汾
								{
									Version %= 3;
									Version++;
									EEPROM_Wipe512_Drive(2);
									EEPROM_Write_Byte_Drive(2,0,Version);
									switch(Version)
									{
										case 1:	Run_Timer=30;				//30*10=300MS����ʱ��
												Stop_Timer=50;				//80*10=800MSֹͣʱ��
												Stable_Motor_Current=800;	//����ȶ�����
												Hall_Open=Open;			//�Ƿ�򿪻����������
												Motor_Open=Open;		//�Ƿ�򿪵���������
												Hall_KEY=Open;			//�Ƿ�򿪻������ؼ��
												break;
										case 2:	Run_Timer=80;				//80*10=800MS����ʱ��
												Stop_Timer=20;				//20*10=200MSֹͣʱ��
												Stable_Motor_Current=550;	//����ȶ�����
												Hall_Open=Open;			//�Ƿ�򿪻����������
												Motor_Open=Open;		//�Ƿ�򿪵���������
												Hall_KEY=Open;			//�Ƿ�򿪻������ؼ��
												break;
										case 3:	Run_Timer=80;				//80*10=800MS����
												Stop_Timer=20;				//20*10=200MSֹͣʱ��
												Stable_Motor_Current=800;	//����ȶ�����
												Hall_Open=Close;		//�Ƿ�򿪻����������
												Motor_Open=Open;		//�Ƿ�򿪵���������
												Hall_KEY=Open;			//�Ƿ�򿪻������ؼ��
												break;
									}
									if(Slave_NO_ONE)	//�豸1�Ż����淴��
									{
										RS485_Flag=1;			//Ӧ������
										Key_Save = Cmd_V_YES;	//�л��汾�ɹ�
									}
								}
								else			//����ֹͣ״̬���ϱ��л��汾ʧ��
								{
									if(Slave_NO_ONE)	//�豸1�Ż����淴��
									{
										RS485_Flag=1;			//Ӧ������
										Key_Save = Cmd_V_NO;	//�л��汾ʧ��
									}
								}
							}
							break;
					case Cmd_Data:
							RS485_Num++;
							if(RS485_Up_Num_Buffer[i+3]==EEPROM_Read_Byte_Drive(4,1))//���ص��ǵ�ǰ�豸���ݣ�ֹͣEND����
							{  
								if(RS485_Up_Num_Buffer[i+3]==10)	//��10�����ݴ������,���ͽ�������
								{
									Current_Device_Return=2;
								}
								else								//���ǵ�10�����ݣ��ȴ���������
								{
									Current_Device_Return=1;									
								}
							}
							else if(RS485_Up_Num_Buffer[i+3]+1==EEPROM_Read_Byte_Drive(4,1))//��һ�����������׼��������һ������
							{
								Front_Device_Return=1;	//�ȴ�������100�λ���200��										
							}
							break;
				}	
				break;	//����forѭ��
			}
				//��������ͷ(�� B4  D3) H��β(0D  0A)
			else if(RS485_Up_Num_Buffer[i]==0xB4 && RS485_Up_Num_Buffer[i+1]==0xD3 && RS485_Up_Num_Buffer[i+7]==0x0D && RS485_Up_Num_Buffer[i+8]==0x0A)
			{
				switch(RS485_Up_Num_Buffer[i+4])
				{
					case Cmd_RUN:Read_Byte_key=KEY_S;break;		//��ʼ���гɹ�,N���ʼѯ���Ƿ����									
					case Cmd_STOP:Read_Byte_key=KEY_M;break;	//ֹͣ���гɹ�,ֹͣѯ��									
//						case Cmd_V_YES:break;					//�л��汾�ɹ�
//						case Cmd_V_NO:break;					//�л��汾ʧ��									
//					case Cmd_Data:Data_count=Data_Clear;break;	//�����ӻ���������
//						case Cmd_NO_ID:break;					//�����ӻ�û�в�����
					case Cmd_Data_End:Data_END_Flag=1;break;//���յ������ϴ����ָ��
				}
				break;	//����forѭ��				
			}
		}
	}
}
void RS485_Data_Drive()//RS485���ݴ���
{
	if(RS485_Busy==1)  //˵��Ŀǰ�������ڽ������ݣ���Ҫ������������
	{
		RS485_RX_Drive();	//RS485���յײ㺯��		
	}
	else if(RS485_Flag==1)	//û�н������ݣ���ʱ׼����������ָ��	
	{
		RS485_TX_Drive();	//RS485���͵ײ㺯��
	}
}
