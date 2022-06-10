#ifndef BH1750_H
#define BH1750_H
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define	 SlaveAddress   0xB8  //BH1750µØÖ·
extern u8  BUF[2];

//º¯ÊýÉùÃ÷
void Single_Write_BH1750(u8 REG_Address);
void Multiple_Read_BH1750(void);
void Get_Sunlight_Value(void);
void BH1750_Init(void);
#endif
