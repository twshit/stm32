#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
/************************************************
 ALIENTEK NANO��STM32F103������ʵ��1
 ������ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 �������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

/*������������ʹ��HAL�⺯��ʵ�ֿ���IO�����*/

int main(void)
{

    HAL_Init();                    	//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9); //����ʱ��,72M
    delay_init(72);                 //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED

    while (1)
    {

//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); //LED0��
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); //LED1��
//        delay_ms(500);                                  //��ʱ500ms
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); //LED0��
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); //LED1��
//        delay_ms(500);                                   //��ʱ500ms
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//			delay_ms(500);                                   //��ʱ500ms
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//LED7 ��ɫ����
//			delay_ms(500);                                   //��ʱ500ms
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);//LED6 ��ɫ����
//			delay_ms(500); 
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);//LED6 ��ɫ����
//			delay_ms(500); 
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 ��ɫ����

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

