#ifndef OLED_Drive
#define OLED_Drive

extern u8 xdata OLED_Modify_Allow;	

#define Data_HZ		 				0	//dat1==Data_HZ，说明是汉字

//#define Reverse_Symbol_One		0	//前一个数字反显
//#define Reverse_Symbol_Two	 	1	//前一个数字反显
//#define Reverse_HZ		 		0	//汉字反显
//#define Display					2	//汉字，数字都正显

extern void OLED_Init();
//extern void OLED_New_Show_Ser();						//刷新图像
//extern void OLED_Write_Symbol(u8 PAGE, SEG16, dat1, dat2, Negation);//显示字符Negation:1反显dat1,2反显dat2,3全部反显
//extern void OLED_Write_HZ(u8 PAGE, u8 SEG16, u8 dat1, u8 dat2, u8 Negation,bit Type);			//显示汉字
//extern void OLED_XRAM_Delete();	//清除缓存
//extern void OLED_Delete();		//清除图像
extern void OLED_New_Show_Ser(u8 PAGE,SEG16,dat1,dat2);

#endif