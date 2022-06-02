#include "led.h"

void LED_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��GPIOCʱ��

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	D3 = 1;

	// 485�շ�ģʽ RS485 RE PA11��0���� 1���ͣ�
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;		  // PA11�˿�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//����Դģ�⿪��SW��ƽ���� PA8 ��0С���� 1�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// GPIO_SetBits(GPIOA,GPIO_Pin_8);

	//ѡ�����IO����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7; // PA2(DATA0�ϵ�D1)PA3(DATA1����D2)PA6(DATA2�̵�D3)PA7(DATA3���̵�D4)�˿�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;								  //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // PC4(DATA4�Ƶ�D5)PC5(DATA5�ٵ�D6)�˿�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // PB0(DATA6���D7)PB1(DATA7�׵�D8)�˿�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
