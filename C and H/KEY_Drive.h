#ifndef KEY_Drive
#define KEY_Drive

extern u8 xdata Read_Byte_key;
extern u8 xdata Key_Save;

#define KEY_NO  0
#define KEY_S   1
#define KEY_M   2
#define KEY_L   3
#define KEY_A   4

extern void KEY_Init();
extern void KEY_Scan_Ser();

#endif