#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
//#include "dac.h"
/************************************************
 ALIENTEK NANO板STM32F103开发板实验1
 跑马灯实验-HAL库版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司
 作者：正点原子 @ALIENTEK
************************************************/

/*下面主函数是使用HAL库函数实现控制IO口输出*/

int main(void)
{

		u16 dacval=0;
    HAL_Init();                    	//初始化HAL库
    Stm32_Clock_Init(RCC_PLL_MUL9); //设置时钟,72M
    delay_init(72);                 //初始化延时函数
    LED_Init();                     //初始化LED
//		Dac1_Init();				//DAC初始化
    while (1)
    {
//					dacval++;
//					HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);//LED1 紫色灯亮
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);//LED1 紫色灯灭			
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);//LED2 蓝色灯亮
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);//LED2 蓝色灯灭
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);//LED3 绿色灯亮
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);//LED3 绿色灯灭
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);//LED4 黄绿色灯亮
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);//LED4 黄绿色灯灭
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);//LED5 黄色灯亮
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);//LED5 黄色灯灭
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);//LED6 橘色灯亮
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);//LED6 橘色灯灭
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//LED7 红色灯亮
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//LED7 红色灯灭
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);//LED8 白色灯亮
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);//LED8 白色灯灭
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);//led0亮
    }
}


/*下面主函数使用位带操作实现：*/

/*
int main(void)
{
    HAL_Init();                    	 	//初始化HAL库
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               			//初始化延时函数
	LED_Init();							//初始化LED

	while(1)
	{
         LED0=0;			     	//LED0亮
	     LED1=1;				 	//LED1灭
		 delay_ms(500);
		 LED0=1;					//LED0灭
		 LED1=0;					//LED1亮
		 delay_ms(500);
	 }
}
*/


/*
下面主函数使用直接操作结存器方式实现
*/

/*
int main(void)
{
    HAL_Init();                    	 	//初始化HAL库
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	LED_Init();							//初始化LED

	while(1)
	{
	  GPIOC->BSRR=GPIO_PIN_0<<16; 	//LED0亮
	  GPIOC->BSRR=GPIO_PIN_1;     	//LED1灭
	  delay_ms(500);
	  GPIOC->BSRR=GPIO_PIN_0;     	//LED0灭
	  GPIOC->BSRR=GPIO_PIN_1<<16; 	//LED1亮
	  delay_ms(500);
	 }
}
*/

/*
下面主函数使用HAL库函数方式实现流水灯
*/

/*
int main(void)
{
    u8 LED=0x00;
	u8 i=0;

    HAL_Init();                    	//初始化HAL库
    Stm32_Clock_Init(RCC_PLL_MUL9); //设置时钟,72M
    delay_init(72);                 //初始化延时函数
    LED_Init();                     //初始化LED
	while(1)
	{

        for(i=0;i<8;i++)
		{
			LED++;
			HAL_GPIO_WritePin(GPIOC,LED,GPIO_PIN_RESET);
			delay_ms(200);
			LED<<=1;//LED依次点亮
		}
		LED++;
		HAL_GPIO_WritePin(GPIOC,LED,GPIO_PIN_RESET);
		delay_ms(200);
		LED=0xff;//LED全灭
		HAL_GPIO_WritePin(GPIOC,LED,GPIO_PIN_SET);
		delay_ms(200);


	}
}
*/


