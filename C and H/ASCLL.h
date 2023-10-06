#ifndef ASCII 	//如果其他文件已经做了这个记号，那么不执行#define.
#define ASCII 	//如果其他文件没有这个标记，那么就需要新做一个记号（唯一的）。
				//并且编译#define到#endif之间的代码。
					
extern u8 code  F8X16[];	//8*16 大字符	
extern u8 code  Hzk[][16];

#endif