#include "all.h"
//****************************************8*16的点阵************************************
u8 code  F8X16[]=	  
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//  0
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15	
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 26
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 27
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 28
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 29
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 30
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 31
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
	
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 32
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 33
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 34
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 35
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 36
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 37
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 38
	
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94
};
u8 code  Hzk[][16]=
{
 /*设(0) 备(1) 运(2) 行(3) 停(4) 止(5) 完(6) 成(7) 计(8) 数(9) 
	①(10) ②(11) ③(12)  不(13)  合(14)  格(15)  √(16) ×(17)  ④(18)*/

{0x40,0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x9E,0xA0,0x20,0x20,0x00},
{0x00,0x00,0x00,0x3F,0x90,0x88,0x40,0x43,0x2C,0x10,0x28,0x46,0x41,0x80,0x80,0x00},/*"设",0*/
/* (16 X 16 , 宋体 )*/

{0x80,0x90,0x90,0x48,0x4C,0x57,0x24,0x24,0x24,0x54,0x4C,0x44,0x80,0x80,0x80,0x00},
{0x00,0x00,0x00,0xFF,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,0x00},/*"备",1*/
/* (16 X 16 , 宋体 )*/

{0x40,0x40,0x42,0xCC,0x00,0x20,0x22,0x22,0xA2,0x62,0x22,0x22,0x22,0x20,0x00,0x00},
{0x00,0x40,0x20,0x1F,0x20,0x44,0x4E,0x45,0x44,0x44,0x44,0x45,0x46,0x4C,0x40,0x00},/*"运",2*/
/* (16 X 16 , 宋体 )*/

{0x00,0x10,0x88,0xC4,0x33,0x00,0x40,0x42,0x42,0x42,0xC2,0x42,0x42,0x42,0x40,0x00},
{0x02,0x01,0x00,0xFF,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00},/*"行",3*/
/* (16 X 16 , 宋体 )*/

{0x80,0x60,0xF8,0x07,0x00,0x04,0x74,0x54,0x55,0x56,0x54,0x54,0x74,0x04,0x00,0x00},
{0x00,0x00,0xFF,0x00,0x03,0x01,0x05,0x45,0x85,0x7D,0x05,0x05,0x05,0x01,0x03,0x00},/*"停",4*/
/* (16 X 16 , 宋体 )*/

{0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00},
{0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00},/*"止",5*/
/* (16 X 16 , 宋体 )*/

{0x10,0x0C,0x04,0x24,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x24,0x04,0x14,0x0C,0x00},
{0x00,0x81,0x81,0x41,0x31,0x0F,0x01,0x01,0x01,0x7F,0x81,0x81,0x81,0xF1,0x00,0x00},/*"完",6*/
/* (16 X 16 , 宋体 )*/

{0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0xFF,0x08,0x09,0x0A,0xC8,0x08,0x00},
{0x80,0x60,0x1F,0x00,0x10,0x20,0x1F,0x80,0x40,0x21,0x16,0x18,0x26,0x41,0xF8,0x00},/*"成",7*/
/* (16 X 16 , 宋体 )*/

{0x40,0x40,0x42,0xCC,0x00,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0x40,0x00},
{0x00,0x00,0x00,0x7F,0x20,0x10,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00},/*"计",8*/
/* (16 X 16 , 宋体 )*/

{0x90,0x52,0x34,0x10,0xFF,0x10,0x34,0x52,0x80,0x70,0x8F,0x08,0x08,0xF8,0x08,0x00},
{0x82,0x9A,0x56,0x63,0x22,0x52,0x8E,0x00,0x80,0x40,0x33,0x0C,0x33,0x40,0x80,0x00},/*"数",9*/
/* (16 X 16 , 宋体 )*/

{0xE0,0x18,0x04,0x02,0x02,0x21,0x11,0xF9,0x01,0x01,0x02,0x02,0x04,0x18,0xE0,0x00},
{0x03,0x0C,0x10,0x20,0x20,0x40,0x40,0x4F,0x40,0x40,0x20,0x20,0x10,0x0C,0x03,0x00},/*"①",10*/
/* (16 X 16 , 宋体 )*/

{0xE0,0x18,0x04,0x02,0x02,0x11,0x09,0x09,0x89,0x71,0x02,0x02,0x04,0x18,0xE0,0x00},
{0x03,0x0C,0x10,0x20,0x20,0x4C,0x4A,0x49,0x48,0x48,0x20,0x20,0x10,0x0C,0x03,0x00},/*"②",11*/
/* (16 X 16 , 宋体 )*/

{0xE0,0x18,0x04,0x02,0x02,0x09,0x89,0xC9,0x29,0x19,0x02,0x02,0x04,0x18,0xE0,0x00},
{0x03,0x0C,0x10,0x20,0x20,0x44,0x48,0x48,0x49,0x46,0x20,0x20,0x10,0x0C,0x03,0x00},/*"③",12*/
/* (16 X 16 , 宋体 )*/

{0x00,0x02,0x02,0x02,0x02,0x82,0x42,0xF2,0x0E,0x42,0x82,0x02,0x02,0x02,0x00,0x00},
{0x10,0x08,0x04,0x02,0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0x02,0x0C,0x00,0x00},/*"不",13*/
/* (16 X 16 , 宋体 )*/

{0x40,0x40,0x20,0x20,0x50,0x48,0x44,0x43,0x44,0x48,0x50,0x20,0x20,0x40,0x40,0x00},
{0x00,0x00,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x00,0x00,0x00},/*"合",14*/
/* (16 X 16 , 宋体 )*/

{0x10,0x10,0xD0,0xFF,0x90,0x20,0x10,0x18,0xA7,0x44,0xA4,0x14,0x0C,0x00,0x00,0x00},
{0x04,0x03,0x00,0xFF,0x00,0x05,0x02,0xFD,0x44,0x44,0x44,0x45,0xFD,0x02,0x02,0x00},/*"格",15*/
/* (16 X 16 , 宋体 )*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,0x0C,0x03,0x00},
{0x00,0x00,0x00,0x10,0x08,0x04,0x18,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x00,0x00},/*"√",16*/
/* (16 X 16 , 宋体 )*/

{0x00,0x00,0x00,0x08,0x10,0x20,0x40,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x08,0x04,0x02,0x01,0x00,0x01,0x02,0x04,0x08,0x00,0x00,0x00,0x00},/*"×",17*/
/* (16 X 16 , 宋体 )*/

//{0xE0,0x18,0x04,0x02,0x02,0xC1,0x31,0x09,0xC1,0x01,0x02,0x02,0x04,0x18,0xE0,0x00},
//{0x03,0x0C,0x10,0x20,0x23,0x42,0x42,0x42,0x4F,0x42,0x22,0x20,0x10,0x0C,0x03,0x00},/*"④",18*/
///* (16 X 16 , 宋体 )*/

////{0x00,0x00,0x00,0x00,0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,0x00},
////{0x00,0x00,0x00,0x00,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,0x00,0x00,0x00,0x00},/*"H",0*/
////{0xE0,0x10,0x08,0x04,0x0A,0xF9,0x09,0x01,0x01,0x09,0xF9,0x0A,0x04,0x08,0x10,0xE0},
////{0x0F,0x10,0x20,0x40,0xA0,0xBF,0xA1,0x81,0x81,0xA1,0xBF,0xA0,0x40,0x20,0x10,0x0F},/*"带圈H",0*/
////{0x00,0x00,0x00,0x08,0xF8,0x08,0xF8,0x00,0xF8,0x08,0xF8,0x08,0x00,0x00,0x00,0x00},
////{0x00,0x00,0x00,0x20,0x3F,0x00,0x03,0x3C,0x03,0x00,0x3F,0x20,0x00,0x00,0x00,0x00},/*"M",0*/
////{0xF0,0x08,0x04,0x0A,0xF9,0x09,0xF9,0x01,0xF9,0x09,0xF9,0x09,0x02,0x04,0x08,0xF0},
////{0x0F,0x10,0x20,0x60,0xBF,0x80,0x83,0xBC,0x83,0x80,0xBF,0xA0,0x40,0x20,0x10,0x0F},/*"带圈M",0*/
////{0x00,0x00,0x00,0x00,0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x00,0x00,0x00},
////{0x00,0x00,0x00,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,0x00,0x00,0x00,0x00},/*"S",0*/
////{0xE0,0x10,0x08,0x04,0x02,0x31,0x49,0x89,0x89,0x09,0x19,0x03,0x04,0x08,0x10,0xE0},
////{0x07,0x08,0x10,0x20,0x40,0x98,0x90,0x90,0x90,0x91,0x8E,0x40,0x20,0x10,0x08,0x07},/*"带圈S",0*/

};