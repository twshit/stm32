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
int htoo;
int main(void)
{

		u16 dacval=0;
    HAL_Init();                    	//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9); //����ʱ��,72M
    delay_init(72);                 //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED
	Dac1_Init();				//DAC��ʼ��
    while (1)
    {
		switch (��ַ��)
		{
		case 01:
			
			LED_Init;
			switch (����)
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
			int dac=htoo(����)��
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
				t=a[i]-'a'+10;//ʮ������aת��Ϊʮ������10,�Դ����Ƶ�f
			else
				t=a[i]-'A'+10;
			sum=sum*16+t;
		}
		
	}
	return sum;
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


