#ifndef EEPROM
#define EEPROM

extern void EEPROM_Wipe512_Drive(u8 ADDRH);//���ĳ������ 
extern u8 EEPROM_Read_Byte_Drive(u8 ADDRH,u8 ADDRL);//��ĳ����������
extern void EEPROM_Write_Byte_Drive(u8 ADDRH,u8 ADDRL,u8 Byte);//��ĳ������д����
//extern u16 EEPROM_Read_Byte(u8 ADDRH);	//��0������������2���ֽ�
//extern void EEPROM_Write_Byte(u8 ADDRH,u16 Byte);//��0����д2�ֽ�����
//extern void EEPROM_Init();//����ȫд0
	
#endif