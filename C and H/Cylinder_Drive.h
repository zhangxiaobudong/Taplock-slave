#ifndef Cylinder_Drive
#define Cylinder_Drive

#define	Side 		1
#define	Front 		2
#define	Rear 		3
#define	Cy_All 		4

extern void Cylinder_Init();
extern void Cylinder_Ser(u8 dat, u8 instruct);//Side,Front,Rear,Cy_All---Open,Close

#endif