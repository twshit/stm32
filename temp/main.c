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
int htoo;
int main(void)
{

		u16 dacval=0;
    HAL_Init();                    	//初始化HAL库
    Stm32_Clock_Init(RCC_PLL_MUL9); //设置时钟,72M
    delay_init(72);                 //初始化延时函数
    LED_Init();                     //初始化LED
	Dac1_Init();				//DAC初始化
    while (1)
    {
		switch (地址码)
		{
		case 01:
			
			LED_Init;
			switch (参数)
			{
			case 1:
				LED1=0;
				break;
			case 2:
				LED2=0;
				break;
			case 3:
				LED3=0;
				break;
			case 4:
				LED4=0;
				break;
			case 5:
				LED5=0;
				break;
			case 6:
				LED6=0;
				break;
			case 7:
				LED7=0;
				break;
			case 8:
				LED8=0;
				break;
			default:
				break;
			}
			break;
		case 02:
			int dac=htoo(参数)；
			HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);
			break;
		case 03:

			break;
		case 04:
			int adc=HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);
			temp=(float)adcx*(3.3/4096);
			printf("%f",adc);
			break;
		case 05:
			int adc=HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);
			temp=(float)adcx*(3.3/4096);
			printf("%f",adc);
			break;
		default:
			break;
		}

    }
}
int htoo(char a[])
{
	int len,t,sum=0;
	len=strlen(a);
	for(i=0;i<len;i++)
	{
		if(a[i]>='0'&&a[i]<='9'||a[i]>='a'&&a[i]<='f'||a[i]>='A'&&a[i]<='F')
		{
			if(a[i]>='0'&&a[i]<='9')
				t=a[i]-'0';
			else if(a[i]>='a'&&a[i]<='f')
				t=a[i]-'a'+10;//十六进制a转化为十进制是10,以此类推到f
			else
				t=a[i]-'A'+10;
			sum=sum*16+t;
		}
		
	}
	return sum;
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


