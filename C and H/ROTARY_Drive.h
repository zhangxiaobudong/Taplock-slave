#ifndef ROTARY_Drive
#define ROTARY_Drive

#define ROTARY_KEY_NO 0
#define ROTARY_KEY_S 1
#define ROTARY_KEY_M 2
#define ROTARY_KEY_L 3

//#define ROTARY_NO    0
//#define ROTARY_Left  1
//#define ROTARY_Right 2

sbit ROTARY_MUTE=P3^2;
sbit ROTARY_A=P3^4;
sbit ROTARY_B=P3^3;

extern u8  xdata ROTARY_Read_Byte_key;
extern u16 xdata ROTARY_Read_Byte_ROTARY;
//extern bit idata ROTARY_Flag;
extern u8  xdata Set_Num_Flag;
extern bit idata cursor_position;

extern void ROTARY_Init();
extern void ROTARY_key_Scan_Drive();
extern void ROTARY_ROTARY_Scan_Drive();

#endif