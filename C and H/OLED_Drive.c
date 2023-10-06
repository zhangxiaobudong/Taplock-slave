#include "all.h"

u8 xdata OLED_Write_Buffer[2][16];
u8 xdata OLED_Modify_Allow=0;

void OLED_Write_Reg(u8 Command)
{
	IIC_Start();			//��ʼ�ź�
	IIC_Write_Byte(0x78);   //�ӻ���ַ
	IIC_Read_ACK();			//�ӻ�Ӧ��
	IIC_Write_Byte(0x00);	//��һ��ָ��д����
	IIC_Read_ACK();			//�ӻ�Ӧ��
	IIC_Write_Byte(Command);//����
	IIC_Read_ACK();			//�ӻ�Ӧ��
	IIC_Stop();				//ֹͣ�ź�
}
//void OLED_Symbol_Ser(u8 dat1,dat2, show)   //��ʾ2���ַ�
void OLED_Symbol_Ser(u8 dat1,dat2)   //��ʾ2���ַ�
{
	u8 i, Value1, Value2;
	Value1=dat1-' ';			//���ַ�=0x20
	Value2=dat2-' ';			//���ַ�=0x20
	for(i=0; i<8; i++)
	{
//		if(show==0)
//			OLED_Write_Buffer[0][i]=~F8X16[Value1*16+i];
//		else
			OLED_Write_Buffer[0][i]=F8X16[Value1*16+i];
	}
	for(i=0; i<8; i++)
	{
//		if(show==1)
//			OLED_Write_Buffer[0][i+8]=~F8X16[Value2*16+i];
//		else
			OLED_Write_Buffer[0][i+8]=F8X16[Value2*16+i];
	}
	for(i=0; i<8; i++)
	{
//		if(show==0)
//			OLED_Write_Buffer[1][i]=~F8X16[Value1*16+8+i];
//		else
			OLED_Write_Buffer[1][i]=F8X16[Value1*16+8+i];
	}
	for(i=0; i<8; i++)
	{
//		if(show==1)
//			OLED_Write_Buffer[1][i+8]=~F8X16[Value2*16+8+i];
//		else
			OLED_Write_Buffer[1][i+8]=F8X16[Value2*16+8+i];
	}
}
//void OLED_HZ_Ser(u8 dat, show)   //��ʾ1������
void OLED_HZ_Ser(u8 dat)   //��ʾ1������
{
	u8 i;
	for(i=0; i<16; i++)
	{
//		if(show==0)
//			OLED_Write_Buffer[0][i]=~Hzk[dat][i];
//		else
			OLED_Write_Buffer[0][i]=Hzk[dat][i];
	}
	for(i=0; i<16; i++)
	{
//		if(show==0)
//			OLED_Write_Buffer[1][i]=~Hzk[dat+1][i];
//		else
			OLED_Write_Buffer[1][i]=Hzk[dat+1][i];
		
	}
}
void OLED_Write_Data(u8 PAGE, u8 SEG16)
{
	u8 i;
	OLED_Write_Reg(0xb0+PAGE);	//ѡ��ҳ
	OLED_Write_Reg(0x10+SEG16);	//ѡ��Ԫ
	IIC_Start();			//��ʼ�ź�
	IIC_Write_Byte(0x78);   //�ӻ���ַ
	IIC_Read_ACK();			//�ӻ�Ӧ��
	IIC_Write_Byte(0x40);	//��һ��ָ��д����
	IIC_Read_ACK();			//�ӻ�Ӧ��
	for(i=0; i<16; i++)
	{
		IIC_Write_Byte(OLED_Write_Buffer[0][i]);//����
		IIC_Read_ACK();		//�ӻ�Ӧ��
	}
	IIC_Stop();				//ֹͣ�ź�
	
	OLED_Write_Reg(0xb0+PAGE+1);	//ѡ��ҳ
	OLED_Write_Reg(0x10+SEG16);	//ѡ��Ԫ
	IIC_Start();			//��ʼ�ź�
	IIC_Write_Byte(0x78);   //�ӻ���ַ
	IIC_Read_ACK();			//�ӻ�Ӧ��
	IIC_Write_Byte(0x40);	//��һ��ָ��д����
	IIC_Read_ACK();			//�ӻ�Ӧ��
	for(i=0; i<16; i++)                            
	{
		IIC_Write_Byte(OLED_Write_Buffer[1][i]);//����
		IIC_Read_ACK();		//�ӻ�Ӧ��
	}
	IIC_Stop();				//ֹͣ�ź�
}
//void OLED_New_Show_Ser(u8 PAGE,SEG16,dat1,dat2,show)
void OLED_New_Show_Ser(u8 PAGE,SEG16,dat1,dat2)
{
	if(dat1==Data_HZ)	//����һ����������
	{
//		OLED_HZ_Ser(dat2,show);	
		OLED_HZ_Ser(dat2);	
	}
	else				//����2���ַ�����
	{
//		OLED_Symbol_Ser(dat1, dat2, show); 
		OLED_Symbol_Ser(dat1, dat2); 
	}
	OLED_Write_Data(PAGE, SEG16);
}
void OLED_Delete()
{
	u8 i, j, k;
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			OLED_Write_Reg(0xb0+i);	//ѡ��ҳ
			OLED_Write_Reg(0x10+j);	//ѡ��Ԫ
			IIC_Start();			//��ʼ�ź�
			IIC_Write_Byte(0x78);   //�ӻ���ַ
			IIC_Read_ACK();			//�ӻ�Ӧ��
			IIC_Write_Byte(0x40);	//��һ��ָ��д����
			IIC_Read_ACK();			//�ӻ�Ӧ��
			for(k=0; k<16; k++)
			{
				IIC_Write_Byte(0);	//����
				IIC_Read_ACK();		//�ӻ�Ӧ��
			}
			IIC_Stop();				//ֹͣ�ź�
		}
	}
}
void Delay200ms()		//@30.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void OLED_Init()
{	
	OLED_RES=0;
	Delay200ms();
	OLED_RES=1;
	
	OLED_Write_Reg(0x00);
	
	OLED_Write_Reg(0x01);
	
	OLED_Write_Reg(0x81);	//���öԱȶ�
	OLED_Write_Reg(0xff);	//�Աȶ�ֵ
	
	OLED_Write_Reg(0xa4);	//��ʾͼ��
	
	OLED_Write_Reg(0xa6);	
	
	OLED_Write_Reg(0xaf);
	
	OLED_Write_Reg(0x40);
	
	OLED_Write_Reg(0xa1);
	
	OLED_Write_Reg(0xc8);
	
	OLED_Write_Reg(0xda);
	OLED_Write_Reg(0x12);
	
	OLED_Write_Reg(0xa8);
	OLED_Write_Reg(0x3f);
	
	OLED_Write_Reg(0xd3);
	OLED_Write_Reg(0x00);
	
	OLED_Write_Reg(0xd5);
	OLED_Write_Reg(0x00);
	
	OLED_Write_Reg(0xd9);
	OLED_Write_Reg(0x22);
	
	OLED_Write_Reg(0xdb);
	OLED_Write_Reg(0x20);
	
	OLED_Write_Reg(0x8d);
	OLED_Write_Reg(0x14);
	
	OLED_Write_Reg(0x20);	//Ѱַģʽ
	OLED_Write_Reg(0x02);	//ҳѰַģʽ
	
	OLED_Delete();		
	
	//�豸
	OLED_New_Show_Ser(0,0,Data_HZ,0);
	OLED_New_Show_Ser(0,1,Data_HZ,2);
	//����
	OLED_New_Show_Ser(2,0,Data_HZ,16);
	OLED_New_Show_Ser(2,1,Data_HZ,18);
//	//����FYAMS22G7A   (XXXX)
//	OLED_New_Show_Ser(4,0,0x3F,0x59);
//	OLED_New_Show_Ser(4,1,0x3A,0x4D);
//	OLED_New_Show_Ser(4,2,0x53,0x32);
//	OLED_New_Show_Ser(4,3,0x32,0x47);
//	OLED_New_Show_Ser(4,4,0x37,0x3A);
	//0x  (00)    �ϸ�/�������ϸ�
	OLED_New_Show_Ser(6,0,0x30,0x78);
	
	OLED_New_Show_Ser(6,6,Data_HZ,28);
	OLED_New_Show_Ser(6,7,Data_HZ,30);
}
