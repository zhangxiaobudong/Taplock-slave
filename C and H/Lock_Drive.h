#ifndef Lock_Drive
#define Lock_Drive

#define Mach1_Left  Mach1_INA=1,Mach1_INB=0;	//电机1正转
#define Mach1_Right Mach1_INA=0,Mach1_INB=1;	//电机1反转
#define Mach1_Stop  Mach1_INA=1,Mach1_INB=1;	//电机1停止

#define Dete_YES    		0
#define Dete_NO     		1

#define	Set_Num1			100
#define Set_Num2			200

#define Current_type		160

extern u8  xdata RS485_Num;
extern u8  xdata Run_Flag;			//运行标志
extern u8  xdata Run_State;			//运行状态
	//故障数值代表的含义
	//0x00 ->	无故障
	//0x01 ->  电机伸出状态，检测到霍尔开关(应该没有)
	//0x02 ->  电机缩回状态，没有检测到霍尔开关(应该有)
	//0x04 ->  电机伸出状态，30ms内霍尔电流没有稳定到1-4ma
	//0x08 ->  电机缩回状态，30ms内霍尔电流没有稳定到5-8ma
	//0x10 ->  电机伸出过程中，电机电流超过预设值
	//0x20 ->  电机缩回过程中，电机电流超过预设值
	//0x40 ->  电机伸出过程中，没有检测到限位开关(应该有)
	//0x80 ->  电机缩回过程中，检测到限位开关(应该没有)
	
extern u16 xdata Data_count;		//数据传输计数
extern u8  xdata Run_OK_200;		//运行200次完成标志
extern u8  xdata Run_Num;			//运行记数
extern u8  xdata Set_Num;			//设置次数
extern u8  xdata Version;			//版本（0= 一代锁，  1= 二代锁，  2=三代锁）
extern bit idata Hall_Open;			//是否检测霍尔电流（1=检测， 0=不检测）
extern bit idata Motor_Open;		//是否检测电机电流（1=检测， 0=不检测）
extern bit idata Hall_KEY;			//是否检测霍尔开关（1=检测， 0=不检测）
extern bit idata Limit_KEY;			//是否检测限位开关（1=检测， 0=不检测）
//extern bit idata B_KEY;				//遇到故障是否停止（1=停止， 0=不停止）
extern u8  xdata Run_Timer;
extern u8  xdata Stop_Timer;
extern u16 xdata Stable_Motor_Current;
extern u8  xdata Motor_Current_Buf[Current_type];//0-79->电机电流(进)，80-159->电机电流(出)
extern u8  xdata Hall_Current_Buf[2];	//0->霍尔电流(进)，1->霍尔电流(出)

extern void System_Init();			//设备初始化
extern void Mach_Run_Scan();		//电机运行扫描

#endif