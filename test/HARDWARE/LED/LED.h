#ifndef _LED_H
#define _LED_H
#include "sys.h"

#define D3 PCout(15)   	//D3 LED端口定义
#define I1 400;					//sw=1 大电流的倒数除以十(测亮电阻时选用（单位10Ω）) 
#define	I2 200000;			//sw=0 小电流的倒数除以十(测暗电阻时选用（单位10Ω）) 

void LED_Init(void);  //LED初始化
 
#endif
