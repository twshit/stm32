#include "timer.h"
#include "usart.h"
#include "led.h"
#include "adc.h"
#include "delay.h"
#include "sys.h"
#include "rs485.h"
///////////////////////////////////////////////////////////////////////////////// 
//��ʱ��3����жϣ�ϵͳ��������sysTick��+1
//��ʱ��4����жϣ�����ʱ����Ӧ������ֵ����
/////////////////////////////////////////////////////////////////////////////////	   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M 
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3

u8 sysTick=0;
	u16 a=0;
  u8 TIM2ITflag=0;
void TIM3_Int_Init(u16 arr,u16 psc)//��ʱ��3��ʼ��
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	//TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
}

void TIM2_Int_Init(u16 arr,u16 psc) //��ʱ��2��ʼ��
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM2��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		sysTick++;
		}
}

//��ʱ��2�жϷ������


void TIM2_IRQHandler(void)   //TIM2�ж� ÿ0.1ms��TIM2ITflag��1
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIM2�����жϱ�־
			TIM2ITflag =1; //��ʾ��ʱ0.1ms
			//a=a+1;
		}
}

	
//ʱ����Ӧ���ݲ����������
void GetSend_R(void)
{
	u16 i;
	u16 TEMP_R[1000]; //����������ֵ

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5 );	//ADC1ͨ��0,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	
	for(i=0;i<1000;i++)	//��ȡ1000����ֵ����
	{
		while(TIM2ITflag == 0); //�ȴ�ÿ 0.1ms TIM2�����жϷ���	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
		TEMP_R[i] = (float)ADC_GetConversionValue(ADC1)*(3.3/4096)*I1;  //��ȡƬ��AD�������
		TIM2ITflag =0;
	}
	TIM_Cmd(TIM2, DISABLE);
	
	RS485_TX_EN = 1;//485����Ϊ����
	for(i=0;i<1000;i++)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1,TEMP_R[i]>>8 );//�򴮿�1���͹���������ֵ���ݸ߰�λ
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1,TEMP_R[i]);//�򴮿�1���͹���������ֵ���ݵͰ�λ
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
				//�����ֵ����
				for(i=0;i<1000;i++)
				{
					TEMP_R[i]=0;
				}							
}
