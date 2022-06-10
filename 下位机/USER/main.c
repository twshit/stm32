#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "myiic.h"
#include "BH1750.h"
#include "rs485.h"
#include "adc.h"
#include "ads1271.h"
#include "dac.h"
#include "SPI.h"
#include "timer.h"

/************************************************
 串口发送指令实现功能：

 01 √ 选灯
 02 √ 设置LED工作电流
 03 √ 设置恒流源电流档位
 04 √ 查询暗电阻阻值
 05 √ 查询亮电阻阻值
 06 √ 查询时间响应数据
 07 √ 查询光照度数据

************************************************/

u16 i;
u16 DACtemp;	// DA输出电压数据	（写入DHR）
u16 receive[3]; // SPI接收到的三个字节片外AD采样结果
u32 ADC;		//片外AD采集数据（SPI三个字节合为一个大数）
float vol;		//光敏电阻电压
u16 TEMP_R;		//光敏电阻阻值
u16 R0;
u8 R[2]; //光敏电阻阻值高低八位

int main(void)
{
	delay_init();									//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);								//串口初始化为115200
	LED_Init();										//初始化与LED连接的硬件接口及IO口
	IIC_Init();										// IIC初始化
	Adc_Init();
	ADS1271_Init();
	Dac1_Init();
	SPI2_Init();
	TIM3_Int_Init(9, 7199); //每1ms产生一次定时器3中断（systick+1）
	TIM2_Int_Init(9, 71);	//每0.1ms产生一次定时器2中断 片内AD测量信号
	RS485_TX_EN = 0;		//默认为接收模式
	while (1)
	{
		//接收数据位数小于六位时，等待50ms仍未接收到下一位数据则重新开始接受
		if ((ReceiveCount > 0) && (ReceiveCount < 6))
		{
			if ((sysTick - ReceiveTick) > 10) //如果超过50ms未接受到下一字节数据
			{
				TIM_Cmd(TIM3, DISABLE); //停止计时
				for (i = 0; i < 6; i++)
					USART_RX_BUF[i] = 0;
				ReceiveCount = 0;
				CMDReceivedFlag = 0;
				sysTick = 0;
				ReceiveTick = 0;
			}
		}
		if (CMDReceivedFlag == 1) //如果成功接收到6字节的指令
		{
			USART_RX_STA = 0;
			if (ucProcessCommand485[5] == 0x0D) /*判断帧尾*/
			{
				switch (ucProcessCommand485[2]) /*判断命令码*/
				{
				case 0x01: // 选灯指令  01-07选灯 00灭灯
				{

					switch (ucProcessCommand485[3])
					{
					case 0x00: // 灯全灭
					{
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x01: // D1紫灯亮
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_2);
						GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x02: // D2蓝灯亮
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x03: // D3绿灯亮
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_6);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x04: // D4黄绿灯亮
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_7);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x05: // D5黄灯亮
					{
						GPIO_SetBits(GPIOC, GPIO_Pin_4);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x06: // D6橘灯亮
					{
						GPIO_SetBits(GPIOC, GPIO_Pin_5);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x07: // D7红灯亮
					{
						GPIO_SetBits(GPIOB, GPIO_Pin_0);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_1);
						break;
					}
					case 0x08: // D8白灯亮
					{
						GPIO_SetBits(GPIOB, GPIO_Pin_1);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);
						break;
					}
					}
					RS485_TX_EN = 1; // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xAA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x00);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x00);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //等待发送结束
					break;
				}
				case 0x02: // 设置LED工作电流
				{
					DACtemp = (ucProcessCommand485[3] << 8) + ucProcessCommand485[4];
					DAC_SetChannel1Data(DAC_Align_12b_R, DACtemp);
					RS485_TX_EN = 1; // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xAA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x02);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, USART_RX_BUF[3]);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, USART_RX_BUF[4]);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //等待发送结束
					break;
				}
				case 0x03: //  设置恒流源电流档位 00低 FF高
				{
					switch (ucProcessCommand485[3]) /*判断档位*/
					{
					case 0x00: // 低电流  I=0.5*10^(-6)
					{
						GPIO_ResetBits(GPIOA, GPIO_Pin_8);
						break;
					}
					case 0xFF: // 高电流 I=2.5*10^(-4)
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_8);
						break;
					}
					}
					RS485_TX_EN = 1; // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xAA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x03);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x00);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x00);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //等待发送结束
					break;
				}
				case 0x04: //  查询暗电阻阻值
				{
					GPIO_ResetBits(GPIOA, GPIO_Pin_8); //恒流源工作在小电流档位
					while (!DRDY)
						;
					while (DRDY)
						;
					receive[0] = SPI2_ReadWriteByte(0x00);
					receive[1] = SPI2_ReadWriteByte(0x00);
					receive[2] = SPI2_ReadWriteByte(0x00);
					ADC = (receive[0] << 16) + (receive[1] << 8) + receive[2]; //通过移位将接收到的三个8位数据合并为一个24位的数
					vol = (float)ADC * (2.5 / 8388606);						   //计算得到电压值
					TEMP_R = vol * I2;										   //计算光敏电阻暗电阻阻值（单位10Ω）
					R0 = TEMP_R & 0xFF00;									   //取阻值高八位
					R[0] = R0 >> 8;
					R[1] = TEMP_R & 0xFF; //取阻值低八位
					RS485_TX_EN = 1;	  // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xAA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x04);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, R[0]); //向串口1发送光敏电阻阻值数据（高八位）
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, R[1]); //向串口1发送光敏电阻阻值数据（低八位）
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //等待发送结束
					break;
				}
				case 0x05: //  查询亮电阻阻值
				{
					GPIO_SetBits(GPIOA, GPIO_Pin_8); //恒流源工作在大电流档位
					while (!DRDY)
						;
					while (DRDY)
						;
					receive[0] = SPI2_ReadWriteByte(0x00);
					receive[1] = SPI2_ReadWriteByte(0x00);
					receive[2] = SPI2_ReadWriteByte(0x00);
					ADC = (receive[0] << 16) + (receive[1] << 8) + receive[2]; //通过移位将接收到的三个8位数据合并为一个24位的数
					vol = (float)ADC * (2.5 / 8388607);						   //计算得到电压值
					TEMP_R = vol * I1;										   //计算光敏电阻亮电阻阻值（单位10Ω）
					R0 = TEMP_R & 0xFF00;									   //取阻值高八位
					R[0] = R0 >> 8;
					R[1] = TEMP_R & 0xFF; //取阻值低八位
					RS485_TX_EN = 1;	  // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xAA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x05);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, R[0]); //向串口1发送光敏电阻阻值数据（高八位）
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, R[1]); //向串口1发送光敏电阻阻值数据（低八位）
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //等待发送结束
					break;
				}
				case 0x06: //  查询时间响应数据
				{
					GPIO_SetBits(GPIOA, GPIO_Pin_8);
					//发送帧头：FAFA
					RS485_TX_EN = 1; // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFA);
					//改变光敏电阻受到光照度
					DAC_SetChannel1Data(DAC_Align_12b_R, 0x0000); //灭灯
					delay_ms(100);
					DAC_SetChannel1Data(DAC_Align_12b_R, 0x05FF); //设置初始光照度
					TIM_Cmd(TIM2, ENABLE);						  //定时器2中断：每0.1ms测量一次 获取1000个阻值数据（每个数据高低两位 共2000位）
					GetSend_R();								  //时间响应数据测量传输
					//发送帧尾：FBFB
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFB);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFB);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //等待发送结束

					break;
				}

				case 0x07: //  查询光照度数据
				{
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //关闭串口接受中断
					Single_Write_BH1750(0x01);						// power on
					Single_Write_BH1750(0x07);						//重置
					Single_Write_BH1750(0x65);						//设置透光率为100%
					Single_Write_BH1750(0x42);
					Single_Write_BH1750(0x20); // 单次H-resolution mode测量模式
					delay_ms(220);			   //延时220ms
					Multiple_Read_BH1750();	   //连续读出数据，存储在BUF中

					RS485_TX_EN = 1; // 485设置为发送
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xAA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x01);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x07);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, BUF[0]); //向串口1发送光照度数据（高八位）
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, BUF[1]); //向串口1发送光照度数据（低八位）
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						;										   //等待发送结束
					USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启串口接受中断
					break;
				}

				case 0x08: //  光照特性测量
				{
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //关闭串口接受中断
					GPIO_SetBits(GPIOA, GPIO_Pin_8);
					RS485_TX_EN = 1; // 485设置为发送
					for (i = 0; i < 1000; i++)
					{
						//改变LED工作电流
						DACtemp = i;
						DAC_SetChannel1Data(DAC_Align_12b_R, DACtemp);
						delay_ms(5); //延时5ms
						//光照度数据测量
						Single_Write_BH1750(0x01); // power on
						Single_Write_BH1750(0x07); //重置
						Single_Write_BH1750(0x65); //设置透光率为100%
						Single_Write_BH1750(0x42);
						Single_Write_BH1750(0x20); //单次H-resolution mode测量模式
						delay_ms(220);			   //延时220ms
						Multiple_Read_BH1750();	   //连续读出数据，存储在BUF中

						//光照度数据传输
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, BUF[0]); //向串口1发送光照度数据（高八位）
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, BUF[1]); //向串口1发送光照度数据（低八位）
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, 0xFA);
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
							;
						USART_SendData(USART1, 0xAF);
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
							; //等待发送结束
						// RS485_TX_EN = 0;//485设置为接收

						//阻值数据测量

						while (!DRDY)
							;
						while (DRDY)
							;
						receive[0] = SPI2_ReadWriteByte(0x00);
						receive[1] = SPI2_ReadWriteByte(0x00);
						receive[2] = SPI2_ReadWriteByte(0x00);
						ADC = (receive[0] << 16) + (receive[1] << 8) + receive[2]; //通过移位将接收到的三个8位数据合并为一个24位的数
						vol = (float)ADC * (2.5 / 8388607);						   //计算得到电压值
						TEMP_R = vol * I1;										   //计算光敏电阻亮电阻阻值（单位10Ω）
						R0 = TEMP_R & 0xFF00;									   //取阻值高八位
						R[0] = R0 >> 8;
						R[1] = TEMP_R & 0xFF; //取阻值低八位

						//阻值数据传输
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, R[0]); //向串口1发送光敏电阻阻值数据（高八位）
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, R[1]); //向串口1发送光敏电阻阻值数据（低八位）
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, 0xA5);
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
							;
						USART_SendData(USART1, 0x5A);
					}
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						;			 //等待发送结束
					RS485_TX_EN = 0; // 485设置为接收
				}
				}

				ucProcessCommand485[0] = 0;
				ucProcessCommand485[1] = 0;
				ucProcessCommand485[2] = 0;
				ucProcessCommand485[3] = 0;
				ucProcessCommand485[4] = 0;
				ucProcessCommand485[5] = 0;
				RS485_TX_EN = 0;
				CMDReceivedFlag = 0;
				D3 = !D3;
			}
		}
	}
}
