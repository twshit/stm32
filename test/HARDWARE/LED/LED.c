#include "led.h"

void LED_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能GPIOC时钟

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	D3 = 1;

	// 485收发模式 RS485 RE PA11（0接收 1发送）
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;		  // PA11端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//恒流源模拟开关SW电平配置 PA8 （0小电流 1大电流）
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// GPIO_SetBits(GPIOA,GPIO_Pin_8);

	//选灯相关IO配置
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7; // PA2(DATA0紫灯D1)PA3(DATA1蓝灯D2)PA6(DATA2绿灯D3)PA7(DATA3黄绿灯D4)端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;								  //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // PC4(DATA4黄灯D5)PC5(DATA5橘灯D6)端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // PB0(DATA6红灯D7)PB1(DATA7白灯D8)端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
