#ifndef RS485_Drive
#define RS485_Drive

extern u8  xdata RS485_Up_Num_Buffer[15];
extern u8  xdata RS485_Flag;
extern bit idata RS485_Busy;
extern bit idata Slave_NO_ONE;
extern u8  xdata Front_Device_Return;
extern u8  xdata Current_Device_Return;
extern u8  xdata Data_END_Flag;

#define RS485_RX			0		//��ȡ����
#define RS485_TX 			1		//��������

//#define Host_ID    			101		//���豸ID���豸����ID��ͬ�ż�ⰴ���������������豸������ͨѶ
//#define Slave_ID			101 	//�豸ID����ʾ��ǰ�豸��ID��
//#define ALL_ID				000		//����ID����ʾ���յ���������ID����Ҫ

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
extern void RS485_Data_Drive();//RS485���ݴ���
extern u8 EEPROM_Read_Device_ID();

#endif