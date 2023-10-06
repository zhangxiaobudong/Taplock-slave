#ifndef EEPROM
#define EEPROM

extern void EEPROM_Wipe512_Drive(u8 ADDRH);//清空某个扇区 
extern u8 EEPROM_Read_Byte_Drive(u8 ADDRH,u8 ADDRL);//读某个扇区数据
extern void EEPROM_Write_Byte_Drive(u8 ADDRH,u8 ADDRL,u8 Byte);//往某个扇区写数据
//extern u16 EEPROM_Read_Byte(u8 ADDRH);	//读0扇区数据连续2个字节
//extern void EEPROM_Write_Byte(u8 ADDRH,u16 Byte);//往0扇区写2字节数据
//extern void EEPROM_Init();//扇区全写0
	
#endif