#include "all.h"

void Cylinder_Init()
{
	Cy_Side=Close;
	Cy_Front=Close;
	Cy_Rear=Close;
}
void Cylinder_Ser(u8 dat, u8 instruct)
{
//	if(dat)
//	{
		switch(dat)
		{
			case Side:	Cy_Side = instruct;break;
			case Front:	Cy_Front = instruct;break;
			case Rear:	Cy_Rear = instruct;break;
			case Cy_All:
					Cy_Side = instruct;
					Cy_Front = instruct;
					Cy_Rear = instruct;
					break;
		}
//		dat=0;
//	}
}
