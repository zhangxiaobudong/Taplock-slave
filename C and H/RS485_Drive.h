#ifndef RS485_Drive
#define RS485_Drive

extern u8  xdata RS485_Up_Num_Buffer[15];
extern u8  xdata RS485_Flag;
extern bit idata RS485_Busy;
extern bit idata Slave_NO_ONE;
extern u8  xdata Front_Device_Return;
extern u8  xdata Current_Device_Return;
extern u8  xdata Data_END_Flag;

#define RS485_RX			0		//读取数据
#define RS485_TX 			1		//发送数据

//#define Host_ID    			101		//主设备ID，设备跟此ID相同才检测按键，并代替其他设备跟主机通讯
//#define Slave_ID			101 	//设备ID，表示当前设备的ID号
//#define ALL_ID				000		//所有ID，表示接收的数据所有ID都需要

#define Cmd_RUN				1	
#define Cmd_STOP			2
#define Cmd_Version			3
//#define Cmd_Ask			4
#define Cmd_V_YES			5
#define Cmd_V_NO			6
#define Cmd_Data			7
#define Cmd_Data_End		8
#define Cmd_NO_ID			9

extern void RS485_Init();
extern void RS485_Data_Drive();//RS485数据处理
extern u8 EEPROM_Read_Device_ID();

#endif