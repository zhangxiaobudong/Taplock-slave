#include "all.h"

void OLED_Allot()
{	
	static u8 xdata OLED_Count=0;
	OLED_Count++;
	switch(OLED_Count)
	{		
		case 2:OLED_New_Show_Ser(0,2,0x54,EEPROM_Read_Byte_Drive(4,0)-7);break;
		case 4:OLED_New_Show_Ser(0,3,EEPROM_Read_Byte_Drive(4,1)/10+'0',EEPROM_Read_Byte_Drive(4,1)%10+'0');break;
		case 6:if(Run_OK_200)
					OLED_New_Show_Ser(0, 5, Data_HZ,12);
				else if(Run_Flag)
					OLED_New_Show_Ser(0, 5, Data_HZ,4);
				else if(!Run_Flag)
					OLED_New_Show_Ser(0, 5, Data_HZ,8);
				break;
		case 8:if(Run_OK_200)
					OLED_New_Show_Ser(0, 6, Data_HZ,14);
				else if(Run_Flag)
					OLED_New_Show_Ser(0, 6, Data_HZ,6);
				else if(!Run_Flag)
					OLED_New_Show_Ser(0, 6, Data_HZ,10);
				break;
		case 10:if(Version==1)	//一代锁显示①    二代锁显示②  三代锁显示③    
					OLED_New_Show_Ser(0, 7, Data_HZ,20);
				else if(Version==2)
					OLED_New_Show_Ser(0, 7, Data_HZ,22);
				else if(Version==3)
					OLED_New_Show_Ser(0, 7, Data_HZ,24);
				break;	
				
		case 12:OLED_New_Show_Ser(2,2,0x54,Run_Num/100+'0');break;
		case 14:OLED_New_Show_Ser(2,3,Run_Num%100/10+'0',Run_Num%10+'0');break;								
		
		case 18:OLED_New_Show_Ser(4,0,Hall_Current/10+'0',Hall_Current%10+'0');break;	
		case 20:if(Hall)
					OLED_New_Show_Ser(4,2,0x20,0x47);	//Y
				else
					OLED_New_Show_Ser(4,2,0x20,0x52);	//N
				break;
		case 22:if(Limit)
					OLED_New_Show_Ser(4,4,0x20,0x47);	//Y
				else
					OLED_New_Show_Ser(4,4,0x20,0x52);	//N
				break;
//		case 24:if(Hall_Current>=1 && Hall_Current<9)	
//				{
//					OLED_New_Show_Ser(4, 6, Data_HZ,32);//有插入设备 √    
//				}
//				else									
//				{
//					OLED_New_Show_Ser(4, 6, Data_HZ,34);//没有插入设备 ×   
//				}									
//				break;	
		case 24:OLED_New_Show_Ser(4,7,RS485_Num+'0', 0x20);break;
				
		case 26:OLED_New_Show_Ser(6,1,Run_State/16+'0',Run_State%16+'0');break;	
		case 28:
				if(Run_State)
					OLED_New_Show_Ser(6,5,Data_HZ,26);	
				else
					OLED_New_Show_Ser(6,5,0x20,0x20);
				break;		
		case 30:OLED_Count=0;break;
		
		//测试用
//		case 20:OLED_New_Show_Ser(4,0,RS485_Up_Num_Buffer[0]/16+'0',RS485_Up_Num_Buffer[0]%16+'0');break;
//		case 22:OLED_New_Show_Ser(4,1,0x20,RS485_Up_Num_Buffer[1]/16+'0');break;
//		case 24:OLED_New_Show_Ser(4,2,RS485_Up_Num_Buffer[1]%16+'0',0x20);break;
//		case 26:OLED_New_Show_Ser(4,3,RS485_Up_Num_Buffer[2]/16+'0',RS485_Up_Num_Buffer[2]%16+'0');break;
//		case 28:OLED_New_Show_Ser(4,4,0x20,RS485_Up_Num_Buffer[3]/16+'0');break;
//		case 30:OLED_New_Show_Ser(4,5,RS485_Up_Num_Buffer[3]%16+'0',0x20);break;
//		case 32:OLED_New_Show_Ser(4,6,RS485_Up_Num_Buffer[4]/16+'0',RS485_Up_Num_Buffer[4]%16+'0');break;
//		
//		case 34:OLED_New_Show_Ser(6,0,RS485_Up_Num_Buffer[5]/16+'0',RS485_Up_Num_Buffer[5]%16+'0');break;
//		case 36:OLED_New_Show_Ser(6,1,0x20,RS485_Up_Num_Buffer[6]/16+'0');break;
//		case 38:OLED_New_Show_Ser(6,2,RS485_Up_Num_Buffer[6]%16+'0',0x20);break;
		
//		case 40:OLED_New_Show_Ser(6,3,RS485_Num/16+'0',RS485_Num%16+'0');break;
//		case 42:OLED_New_Show_Ser(6,4,0x20,bbb/16+'0');break;
//		case 44:OLED_New_Show_Ser(6,5,bbb%16+'0',0x20);break;
//		case 46:OLED_New_Show_Ser(6,6,ccc/16+'0',ccc%16+'0');break;
//		case 47:OLED_New_Show_Ser(6,7,0x20,RS485_OK_Flag+'0');break;

//		case 30:OLED_New_Show_Ser(4,0,ADC_Reference/1000+'0',ADC_Reference%1000/100+'0');break;
//		case 32:OLED_New_Show_Ser(4,1,ADC_Reference%100/10+'0',ADC_Reference%10+'0');break;
//		case 48:OLED_Count=0;break;
	}	
}
void KEY_Allot()
{	
	if(Slave_NO_ONE)	//主设备才能检测按键
	{
		KEY_Scan_Ser();
	}
	if(Read_Byte_key==KEY_S)	//短按，运行/停止
	{			
		Run_Flag=1;
		Run_OK_200=0;			
		LED_W=LED_Close;	//关灯
		Run_Num=0;
		Run_State=0; 
		Limit_KEY=Open;
	}
	else if(Read_Byte_key==KEY_M)	//短按，运行/停止
	{
		Run_Flag=3;
		Mach1_Stop;
	}
	Read_Byte_key=KEY_NO;
}
void ADC_Allot()
{
	static u16 xdata count=0;
	count++;
	if(count==1500)
	{
		if(Run_Flag==0)
		{
			if(ADC_Reference==0)
			{
				Motor_Current_Calculate();	//捕获电机电流
				ADC_Reference=ADC_Read_Byte;
			}
			else
			{
				Hall_Current_Calculate();	//捕获霍尔电流
			}
		}		
	}
	if(count>=1700)
	{
		count=0;
	}
}
void main()
{
	P1M1=0;P1M0=0;
	P3M1=0;P3M0=0xE2;	//P3.1/P3.5/P3.6/P3.7推挽输出
	P5M1=0;P5M0=0;
	RS485_Init();
	ADC_Init();
	IIC_Init();
	OLED_Init();
	System_Init();
	KEY_Init();	
	Cylinder_Init();

	EEPROM_Wipe512_Drive(4);
	EEPROM_Write_Byte_Drive(4,0,'D');
	EEPROM_Write_Byte_Drive(4,1,1);
	
	while(1)
	{
		RS485_Data_Drive();	//RS485数据处理
		OLED_Allot();		//OLED屏幕显示
		Mach_Run_Scan();	//电机运行扫描	
		KEY_Allot();
		ADC_Allot();
		LED_Ser();
	}
}