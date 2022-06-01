#include "ads1271.h"

void ADS1271_Init(void)
   {
	  GPIO_InitTypeDef GPIO_InitStruct;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);// GPIOCʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);// GPIOBʱ��ʹ��  		 
		
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;//PC8-ADS1271MODE���� PC9-ADS1271SYNC���� 
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;  // PC8/9����������� 
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOC,&GPIO_InitStruct);   //��ʼ��GPIOC   

    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;   //PB12-ADS1271 DRDY����
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; //PB12��������
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStruct);   //��ʼ��GPIOB 
	
	  GPIO_SetBits(GPIOC,GPIO_Pin_9);  // PC9���� ���� SYNC=1�����ɼ����ϵ�
		//GPIO_ResetBits(GPIOC,GPIO_Pin_8);  //PC8���� ���� Mode=0 �߷ֱ���ģʽ
		 
   }
