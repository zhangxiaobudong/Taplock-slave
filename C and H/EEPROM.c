#include "all.h"

void EEPROM_Wipe512_Drive(u8 ADDRH)	//���ĳ������ 
{
	IAP_ADDRH=ADDRH;
	IAP_CONTR|=0X82;
	IAP_CMD=0X03;
	IAP_TRIG=0X5A;
	IAP_TRIG=0XA5;
}
u8 EEPROM_Read_Byte_Drive(u8 ADDRH,u8 ADDRL)	//��ĳ����������
{
	u8 idata DATA;
	IAP_ADDRH=ADDRH;
	IAP_ADDRL=ADDRL;
	IAP_CONTR|=0X82;
	IAP_CMD=0X01;
	IAP_TRIG=0X5A;
	IAP_TRIG=0XA5;
	DATA=IAP_DATA;
	return  DATA;
}
void EEPROM_Write_Byte_Drive(u8 ADDRH,u8 ADDRL,u8 Byte)//��ĳ������д����
{ 
	IAP_ADDRH=ADDRH;
	IAP_ADDRL=ADDRL;
	IAP_DATA=Byte;
	IAP_CONTR|=0X82;
	IAP_CMD=0X02;
	IAP_TRIG=0X5A;
	IAP_TRIG=0XA5;
}
//u16 EEPROM_Read_Byte(u8 ADDRH)	//��ADDRH������������2���ֽ�
//{
//	u16 xdata DATA;
//	DATA=(EEPROM_Read_Byte_Drive(ADDRH,0)*256)+
//		 EEPROM_Read_Byte_Drive(ADDRH,1);
//	return  DATA;
//}
//void EEPROM_Write_Byte(u8 ADDRH,u16 Byte)//��ADDRH����д2�ֽ�����
//{
//	EEPROM_Wipe512_Drive(ADDRH);
//	EEPROM_Write_Byte_Drive(ADDRH,0,((Byte>>8)&0xff));
//	EEPROM_Write_Byte_Drive(ADDRH,1,(Byte&0xff));
//}
//void EEPROM_Init()//����ȫд0
//{
//	u8 i,j;
//	for(i=0;i<4;i++)
//	{
//		EEPROM_Wipe512_Drive(i*2);
//		for(j=0;j<4;j++)
//		{
//			EEPROM_Write_Byte_Drive(i*2,j,0);//��ĳ������д����
//		}
//	}
//}