#include "timer.h"
#include "usart.h"
#include "led.h"
#include "adc.h"
#include "delay.h"
#include "sys.h"
#include "rs485.h"
///////////////////////////////////////////////////////////////////////////////// 
//定时器3溢出中断：系统计数器（sysTick）+1
//定时器4溢出中断：控制时间响应特性阻值测量
/////////////////////////////////////////////////////////////////////////////////	   	 

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M 
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3

u8 sysTick=0;
	u16 a=0;
  u8 TIM2ITflag=0;
void TIM3_Int_Init(u16 arr,u16 psc)//定时器3初始化
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	//TIM_Cmd(TIM3, ENABLE);  //使能TIMx
}

void TIM2_Int_Init(u16 arr,u16 psc) //定时器2初始化
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM2, ENABLE);  //使能TIMx
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
		sysTick++;
		}
}

//定时器2中断服务程序


void TIM2_IRQHandler(void)   //TIM2中断 每0.1ms将TIM2ITflag置1
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIM2更新中断标志
			TIM2ITflag =1; //表示计时0.1ms
			//a=a+1;
		}
}

	
//时间响应数据测量传输程序
void GetSend_R(void)
{
	u16 i;
	u16 TEMP_R[1000]; //光敏电阻阻值

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5 );	//ADC1通道0,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	
	for(i=0;i<1000;i++)	//获取1000个阻值数据
	{
		while(TIM2ITflag == 0); //等待每 0.1ms TIM2更新中断发生	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
		TEMP_R[i] = (float)ADC_GetConversionValue(ADC1)*(3.3/4096)*I1;  //获取片内AD采样结果
		TIM2ITflag =0;
	}
	TIM_Cmd(TIM2, DISABLE);
	
	RS485_TX_EN = 1;//485设置为发送
	for(i=0;i<1000;i++)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1,TEMP_R[i]>>8 );//向串口1发送光敏电阻阻值数据高八位
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1,TEMP_R[i]);//向串口1发送光敏电阻阻值数据低八位
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
				//清空阻值缓存
				for(i=0;i<1000;i++)
				{
					TEMP_R[i]=0;
				}							
}
