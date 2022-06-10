#include "ads1271.h"

void ADS1271_Init(void)
   {
	  GPIO_InitTypeDef GPIO_InitStruct;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);// GPIOC时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);// GPIOB时钟使能  		 
		
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;//PC8-ADS1271MODE引脚 PC9-ADS1271SYNC引脚 
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;  // PC8/9复用推挽输出 
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOC,&GPIO_InitStruct);   //初始化GPIOC   

    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;   //PB12-ADS1271 DRDY引脚
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; //PB12浮空输入
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStruct);   //初始化GPIOB 
	
	  GPIO_SetBits(GPIOC,GPIO_Pin_9);  // PC9上拉 配置 SYNC=1连续采集不断电
		//GPIO_ResetBits(GPIOC,GPIO_Pin_8);  //PC8浮空 配置 Mode=0 高分辨率模式
		 
   }
