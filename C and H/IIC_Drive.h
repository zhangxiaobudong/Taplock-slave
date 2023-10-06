#ifndef IIC_Drive
#define IIC_Drive

extern void IIC_Init();
extern void IIC_Start();
extern void IIC_Stop();
extern void IIC_Write_Byte(u8 IIC_Byte);
//extern u8 IIC_Read_Byte();
extern u8 IIC_Read_ACK();
//extern void IIC_Write_ACK(bit ack);

#endif