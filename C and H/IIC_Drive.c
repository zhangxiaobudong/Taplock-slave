#include "all.h"

void IIC_Init()
{
	IIC_SDA=1;
	IIC_SCL=1;
}
void IIC_delay()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}
void IIC_Start()
{
	IIC_SCL=1;
	IIC_SDA=1;
	IIC_delay();
	IIC_SDA=0;
	IIC_SCL=0;
	IIC_delay();
}
void IIC_Stop()
{
	IIC_SDA=0;
	IIC_SCL=1;
	IIC_delay();
	IIC_SDA=1;
	IIC_delay();
}
void IIC_Write_Byte(u8 IIC_Byte)
{
	u8 idata i;
	IIC_SCL=0;
	IIC_SDA=1;
	for(i=0; i<8; i++)
	{
		IIC_SDA=(bit)(IIC_Byte&0x80);
		IIC_Byte<<=1;
		IIC_SCL=1;
		IIC_delay();
		IIC_SCL=0;
		IIC_delay();
	}
	IIC_SDA=1;
}
//u8 IIC_Read_Byte()
//{
//	u8 idata i, Value;
//	IIC_SCL=0;
//	IIC_SDA=1;
//	for(i=0; i<8; i++)
//	{
//		Value<<=1;
//		Value|=IIC_SDA;
//		IIC_SCL=1;
//		IIC_delay();
//		IIC_SCL=0;
//		IIC_delay();
//	}
//	return Value;
//}
u8 IIC_Read_ACK()
{
	u8 idata i, ack=1;
	IIC_SCL=1;
	IIC_delay();
	while((ack)&&(i<5))
	{
		i++;
		ack=IIC_SDA;
	}
	IIC_SCL=0;
	return ack;
}
//void IIC_Write_ACK(bit ack)
//{
//	IIC_SDA=ack;
//	IIC_SCL=1;
//	IIC_delay();
//	IIC_SCL=0;
//	IIC_SDA=1;
//	IIC_delay();
//}