#ifndef OLED_Drive
#define OLED_Drive

extern u8 xdata OLED_Modify_Allow;	

#define Data_HZ		 				0	//dat1==Data_HZ��˵���Ǻ���

//#define Reverse_Symbol_One		0	//ǰһ�����ַ���
//#define Reverse_Symbol_Two	 	1	//ǰһ�����ַ���
//#define Reverse_HZ		 		0	//���ַ���
//#define Display					2	//���֣����ֶ�����

extern void OLED_Init();
//extern void OLED_New_Show_Ser();						//ˢ��ͼ��
//extern void OLED_Write_Symbol(u8 PAGE, SEG16, dat1, dat2, Negation);//��ʾ�ַ�Negation:1����dat1,2����dat2,3ȫ������
//extern void OLED_Write_HZ(u8 PAGE, u8 SEG16, u8 dat1, u8 dat2, u8 Negation,bit Type);			//��ʾ����
//extern void OLED_XRAM_Delete();	//�������
//extern void OLED_Delete();		//���ͼ��
extern void OLED_New_Show_Ser(u8 PAGE,SEG16,dat1,dat2);

#endif