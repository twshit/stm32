#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "delay.h"
#include "myiic.h"
#include "BH1750.h"
#include "rs485.h"
#include "adc.h"
#include "ads1271.h"
#include "dac.h"
#include "SPI.h"
//////////////////////////////////////////////////////////////////////////////////
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h" //ucos 使用
#endif
//////////////////////////////////////////////////////////////////////////////////
//
//串口1配置和初始化
//串口接收中断服务函数实现帧头校验和指令位数校验
//
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
  int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit(int x)
{
  x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
  while ((USART1->SR & 0X40) == 0)
    ; //循环发送,直到发送完毕
  USART1->DR = (u8)ch;
  return ch;
}
#endif

/*使用microLib的方法*/
/*
int fputc(int ch, FILE *f)
{
 USART_SendData(USART1, (uint8_t) ch);

 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

   return ch;
}
int GetKey (void)  {

   while (!(USART1->SR & USART_FLAG_RXNE));

   return ((int)(USART1->DR & 0x1FF));
}
*/

#if EN_USART1_RX //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误

u8 USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
u16 USART_RX_STA = 0;           //接收状态标记
u8 Res;
u8 ReceiveTick;
u8 ReceiveCount = 0;
u8 CMDReceivedFlag;
u8 ucProcessCommand485[6];

void uart_init(u32 bound)
{
  // GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //使能USART1，GPIOA时钟

  // USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);          //初始化GPIOA.9

  // USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            // PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化GPIOA.10

  // Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化VIC寄存器

  // USART 初始化设置

  USART_InitStructure.USART_BaudRate = bound;                                     //串口波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
  USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式

  USART_Init(USART1, &USART_InitStructure);      //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启串口接受中断
  USART_Cmd(USART1, ENABLE);                     //使能串口1
}

void USART1_IRQHandler(void) //串口1中断服务程序
{
#if SYSTEM_SUPPORT_OS //如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
  OSIntEnter();
#endif
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
  {
    Res = USART_ReceiveData(USART1); //读取接收到的数据
    USART_RX_BUF[ReceiveCount] = Res;

    if (USART_RX_BUF[0] == 0xAA)
    {
      ReceiveCount = ReceiveCount + 1;
      ReceiveTick = 0;
      sysTick = 0;
      TIM_Cmd(TIM3, ENABLE); //开始计时
    }

    else
    {
      ReceiveCount = 0;
      USART_ClearITPendingBit(USART1, USART_IT_RXNE); // Clear the Interrupt Flag
      return;
    }
    if ((ReceiveCount > 0) && (ReceiveCount < 6))
    {
      ReceiveTick = sysTick;
    }
    else if (ReceiveCount >= 6)
    {
      TIM_Cmd(TIM3, DISABLE); //停止计时
      sysTick = 0;
      ReceiveTick = 0;
      CMDReceivedFlag = 1;
      ReceiveCount = 0;
      ucProcessCommand485[0] = USART_RX_BUF[0];
      ucProcessCommand485[1] = USART_RX_BUF[1];
      ucProcessCommand485[2] = USART_RX_BUF[2];
      ucProcessCommand485[3] = USART_RX_BUF[3];
      ucProcessCommand485[4] = USART_RX_BUF[4];
      ucProcessCommand485[5] = USART_RX_BUF[5];
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE); // Clear the Interrupt Flag

#if SYSTEM_SUPPORT_OS //如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
    OSIntExit();
#endif
  }
#endif
}
