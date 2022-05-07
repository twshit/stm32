#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
//#include "dac.h"
/************************************************
 ALIENTEK NANO��STM32F103������ʵ��1
 �����ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

/*������������ʹ��HAL�⺯��ʵ�ֿ���IO�����*/

int main(void)
{

		u16 dacval=0;
    HAL_Init();                    	//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9); //����ʱ��,72M
    delay_init(72);                 //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED
//		Dac1_Init();				//DAC��ʼ��
    while (1)
    {
//					dacval++;
//					HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);//LED1 ��ɫ����
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);//LED1 ��ɫ����			
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);//LED2 ��ɫ����
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);//LED2 ��ɫ����
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);//LED3 ��ɫ����
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);//LED3 ��ɫ����
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);//LED4 ����ɫ����
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);//LED4 ����ɫ����
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);//LED5 ��ɫ����
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);//LED5 ��ɫ����
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);//LED6 ��ɫ����
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);//LED6 ��ɫ����
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//LED7 ��ɫ����
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);//LED8 ��ɫ����
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);//LED8 ��ɫ����
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);//led0��
    }
}


/*����������ʹ��λ������ʵ�֣�*/

/*
int main(void)
{
    HAL_Init();                    	 	//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               			//��ʼ����ʱ����
	LED_Init();							//��ʼ��LED

	while(1)
	{
         LED0=0;			     	//LED0��
	     LED1=1;				 	//LED1��
		 delay_ms(500);
		 LED0=1;					//LED0��
		 LED1=0;					//LED1��
		 delay_ms(500);
	 }
}
*/


/*
����������ʹ��ֱ�Ӳ����������ʽʵ��
*/

/*
int main(void)
{
    HAL_Init();                    	 	//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	LED_Init();							//��ʼ��LED

	while(1)
	{
	  GPIOC->BSRR=GPIO_PIN_0<<16; 	//LED0��
	  GPIOC->BSRR=GPIO_PIN_1;     	//LED1��
	  delay_ms(500);
	  GPIOC->BSRR=GPIO_PIN_0;     	//LED0��
	  GPIOC->BSRR=GPIO_PIN_1<<16; 	//LED1��
	  delay_ms(500);
	 }
}
*/

/*
����������ʹ��HAL�⺯����ʽʵ����ˮ��
*/

/*
int main(void)
{
    u8 LED=0x00;
	u8 i=0;

    HAL_Init();                    	//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9); //����ʱ��,72M
    delay_init(72);                 //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED
	while(1)
	{

        for(i=0;i<8;i++)
		{
			LED++;
			HAL_GPIO_WritePin(GPIOC,LED,GPIO_PIN_RESET);
			delay_ms(200);
			LED<<=1;//LED���ε���
		}
		LED++;
		HAL_GPIO_WritePin(GPIOC,LED,GPIO_PIN_RESET);
		delay_ms(200);
		LED=0xff;//LEDȫ��
		HAL_GPIO_WritePin(GPIOC,LED,GPIO_PIN_SET);
		delay_ms(200);


	}
}
*/


