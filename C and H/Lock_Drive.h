#ifndef Lock_Drive
#define Lock_Drive

#define Mach1_Left  Mach1_INA=1,Mach1_INB=0;	//���1��ת
#define Mach1_Right Mach1_INA=0,Mach1_INB=1;	//���1��ת
#define Mach1_Stop  Mach1_INA=1,Mach1_INB=1;	//���1ֹͣ

#define Dete_YES    		0
#define Dete_NO     		1

#define	Set_Num1			100
#define Set_Num2			200

#define Current_type		160

extern u8  xdata RS485_Num;
extern u8  xdata Run_Flag;			//���б�־
extern u8  xdata Run_State;			//����״̬
	//������ֵ����ĺ���
	//0x00 ->	�޹���
	//0x01 ->  ������״̬����⵽��������(Ӧ��û��)
	//0x02 ->  �������״̬��û�м�⵽��������(Ӧ����)
	//0x04 ->  ������״̬��30ms�ڻ�������û���ȶ���1-4ma
	//0x08 ->  �������״̬��30ms�ڻ�������û���ȶ���5-8ma
	//0x10 ->  �����������У������������Ԥ��ֵ
	//0x20 ->  ������ع����У������������Ԥ��ֵ
	//0x40 ->  �����������У�û�м�⵽��λ����(Ӧ����)
	//0x80 ->  ������ع����У���⵽��λ����(Ӧ��û��)
	
extern u16 xdata Data_count;		//���ݴ������
extern u8  xdata Run_OK_200;		//����200����ɱ�־
extern u8  xdata Run_Num;			//���м���
extern u8  xdata Set_Num;			//���ô���
extern u8  xdata Version;			//�汾��0= һ������  1= ��������  2=��������
extern bit idata Hall_Open;			//�Ƿ������������1=��⣬ 0=����⣩
extern bit idata Motor_Open;		//�Ƿ�����������1=��⣬ 0=����⣩
extern bit idata Hall_KEY;			//�Ƿ���������أ�1=��⣬ 0=����⣩
extern bit idata Limit_KEY;			//�Ƿ�����λ���أ�1=��⣬ 0=����⣩
//extern bit idata B_KEY;				//���������Ƿ�ֹͣ��1=ֹͣ�� 0=��ֹͣ��
extern u8  xdata Run_Timer;
extern u8  xdata Stop_Timer;
extern u16 xdata Stable_Motor_Current;
extern u8  xdata Motor_Current_Buf[Current_type];//0-79->�������(��)��80-159->�������(��)
extern u8  xdata Hall_Current_Buf[2];	//0->��������(��)��1->��������(��)

extern void System_Init();			//�豸��ʼ��
extern void Mach_Run_Scan();		//�������ɨ��

#endif