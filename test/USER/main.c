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
 ���ڷ���ָ��ʵ�ֹ��ܣ�

 01 �� ѡ��
 02 �� ����LED��������
 03 �� ���ú���Դ������λ
 04 �� ��ѯ��������ֵ
 05 �� ��ѯ��������ֵ
 06 �� ��ѯʱ����Ӧ����
 07 �� ��ѯ���ն�����

************************************************/

u16 i;
u16 DACtemp;	// DA�����ѹ����	��д��DHR��
u16 receive[3]; // SPI���յ��������ֽ�Ƭ��AD�������
u32 ADC;		//Ƭ��AD�ɼ����ݣ�SPI�����ֽں�Ϊһ��������
float vol;		//���������ѹ
u16 TEMP_R;		//����������ֵ
u16 R0;
u8 R[2]; //����������ֵ�ߵͰ�λ

int main(void)
{
	delay_init();									//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);								//���ڳ�ʼ��Ϊ115200
	LED_Init();										//��ʼ����LED���ӵ�Ӳ���ӿڼ�IO��
	IIC_Init();										// IIC��ʼ��
	Adc_Init();
	ADS1271_Init();
	Dac1_Init();
	SPI2_Init();
	TIM3_Int_Init(9, 7199); //ÿ1ms����һ�ζ�ʱ��3�жϣ�systick+1��
	TIM2_Int_Init(9, 71);	//ÿ0.1ms����һ�ζ�ʱ��2�ж� Ƭ��AD�����ź�
	RS485_TX_EN = 0;		//Ĭ��Ϊ����ģʽ
	while (1)
	{
		//��������λ��С����λʱ���ȴ�50ms��δ���յ���һλ���������¿�ʼ����
		if ((ReceiveCount > 0) && (ReceiveCount < 6))
		{
			if ((sysTick - ReceiveTick) > 10) //�������50msδ���ܵ���һ�ֽ�����
			{
				TIM_Cmd(TIM3, DISABLE); //ֹͣ��ʱ
				for (i = 0; i < 6; i++)
					USART_RX_BUF[i] = 0;
				ReceiveCount = 0;
				CMDReceivedFlag = 0;
				sysTick = 0;
				ReceiveTick = 0;
			}
		}
		if (CMDReceivedFlag == 1) //����ɹ����յ�6�ֽڵ�ָ��
		{
			USART_RX_STA = 0;
			if (ucProcessCommand485[5] == 0x0D) /*�ж�֡β*/
			{
				switch (ucProcessCommand485[2]) /*�ж�������*/
				{
				case 0x01: // ѡ��ָ��  01-07ѡ�� 00���
				{

					switch (ucProcessCommand485[3])
					{
					case 0x00: // ��ȫ��
					{
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x01: // D1�ϵ���
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_2);
						GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x02: // D2������
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x03: // D3�̵���
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_6);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x04: // D4���̵���
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_7);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x05: // D5�Ƶ���
					{
						GPIO_SetBits(GPIOC, GPIO_Pin_4);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x06: // D6�ٵ���
					{
						GPIO_SetBits(GPIOC, GPIO_Pin_5);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
						break;
					}
					case 0x07: // D7�����
					{
						GPIO_SetBits(GPIOB, GPIO_Pin_0);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_1);
						break;
					}
					case 0x08: // D8�׵���
					{
						GPIO_SetBits(GPIOB, GPIO_Pin_1);
						GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
						GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);
						break;
					}
					}
					RS485_TX_EN = 1; // 485����Ϊ����
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
						; //�ȴ����ͽ���
					break;
				}
				case 0x02: // ����LED��������
				{
					DACtemp = (ucProcessCommand485[3] << 8) + ucProcessCommand485[4];
					DAC_SetChannel1Data(DAC_Align_12b_R, DACtemp);
					RS485_TX_EN = 1; // 485����Ϊ����
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
						; //�ȴ����ͽ���
					break;
				}
				case 0x03: //  ���ú���Դ������λ 00�� FF��
				{
					switch (ucProcessCommand485[3]) /*�жϵ�λ*/
					{
					case 0x00: // �͵���  I=0.5*10^(-6)
					{
						GPIO_ResetBits(GPIOA, GPIO_Pin_8);
						break;
					}
					case 0xFF: // �ߵ��� I=2.5*10^(-4)
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_8);
						break;
					}
					}
					RS485_TX_EN = 1; // 485����Ϊ����
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
						; //�ȴ����ͽ���
					break;
				}
				case 0x04: //  ��ѯ��������ֵ
				{
					GPIO_ResetBits(GPIOA, GPIO_Pin_8); //����Դ������С������λ
					while (!DRDY)
						;
					while (DRDY)
						;
					receive[0] = SPI2_ReadWriteByte(0x00);
					receive[1] = SPI2_ReadWriteByte(0x00);
					receive[2] = SPI2_ReadWriteByte(0x00);
					ADC = (receive[0] << 16) + (receive[1] << 8) + receive[2]; //ͨ����λ�����յ�������8λ���ݺϲ�Ϊһ��24λ����
					vol = (float)ADC * (2.5 / 8388606);						   //����õ���ѹֵ
					TEMP_R = vol * I2;										   //����������谵������ֵ����λ10����
					R0 = TEMP_R & 0xFF00;									   //ȡ��ֵ�߰�λ
					R[0] = R0 >> 8;
					R[1] = TEMP_R & 0xFF; //ȡ��ֵ�Ͱ�λ
					RS485_TX_EN = 1;	  // 485����Ϊ����
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
					USART_SendData(USART1, R[0]); //�򴮿�1���͹���������ֵ���ݣ��߰�λ��
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, R[1]); //�򴮿�1���͹���������ֵ���ݣ��Ͱ�λ��
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //�ȴ����ͽ���
					break;
				}
				case 0x05: //  ��ѯ��������ֵ
				{
					GPIO_SetBits(GPIOA, GPIO_Pin_8); //����Դ�����ڴ������λ
					while (!DRDY)
						;
					while (DRDY)
						;
					receive[0] = SPI2_ReadWriteByte(0x00);
					receive[1] = SPI2_ReadWriteByte(0x00);
					receive[2] = SPI2_ReadWriteByte(0x00);
					ADC = (receive[0] << 16) + (receive[1] << 8) + receive[2]; //ͨ����λ�����յ�������8λ���ݺϲ�Ϊһ��24λ����
					vol = (float)ADC * (2.5 / 8388607);						   //����õ���ѹֵ
					TEMP_R = vol * I1;										   //�������������������ֵ����λ10����
					R0 = TEMP_R & 0xFF00;									   //ȡ��ֵ�߰�λ
					R[0] = R0 >> 8;
					R[1] = TEMP_R & 0xFF; //ȡ��ֵ�Ͱ�λ
					RS485_TX_EN = 1;	  // 485����Ϊ����
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
					USART_SendData(USART1, R[0]); //�򴮿�1���͹���������ֵ���ݣ��߰�λ��
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, R[1]); //�򴮿�1���͹���������ֵ���ݣ��Ͱ�λ��
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //�ȴ����ͽ���
					break;
				}
				case 0x06: //  ��ѯʱ����Ӧ����
				{
					GPIO_SetBits(GPIOA, GPIO_Pin_8);
					//����֡ͷ��FAFA
					RS485_TX_EN = 1; // 485����Ϊ����
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFA);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFA);
					//�ı���������ܵ����ն�
					DAC_SetChannel1Data(DAC_Align_12b_R, 0x0000); //���
					delay_ms(100);
					DAC_SetChannel1Data(DAC_Align_12b_R, 0x05FF); //���ó�ʼ���ն�
					TIM_Cmd(TIM2, ENABLE);						  //��ʱ��2�жϣ�ÿ0.1ms����һ�� ��ȡ1000����ֵ���ݣ�ÿ�����ݸߵ���λ ��2000λ��
					GetSend_R();								  //ʱ����Ӧ���ݲ�������
					//����֡β��FBFB
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFB);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0xFB);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						; //�ȴ����ͽ���

					break;
				}

				case 0x07: //  ��ѯ���ն�����
				{
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //�رմ��ڽ����ж�
					Single_Write_BH1750(0x01);						// power on
					Single_Write_BH1750(0x07);						//����
					Single_Write_BH1750(0x65);						//����͸����Ϊ100%
					Single_Write_BH1750(0x42);
					Single_Write_BH1750(0x20); // ����H-resolution mode����ģʽ
					delay_ms(220);			   //��ʱ220ms
					Multiple_Read_BH1750();	   //�����������ݣ��洢��BUF��

					RS485_TX_EN = 1; // 485����Ϊ����
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
					USART_SendData(USART1, BUF[0]); //�򴮿�1���͹��ն����ݣ��߰�λ��
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, BUF[1]); //�򴮿�1���͹��ն����ݣ��Ͱ�λ��
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
						;
					USART_SendData(USART1, 0x0D);
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						;										   //�ȴ����ͽ���
					USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�������ڽ����ж�
					break;
				}

				case 0x08: //  �������Բ���
				{
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //�رմ��ڽ����ж�
					GPIO_SetBits(GPIOA, GPIO_Pin_8);
					RS485_TX_EN = 1; // 485����Ϊ����
					for (i = 0; i < 1000; i++)
					{
						//�ı�LED��������
						DACtemp = i;
						DAC_SetChannel1Data(DAC_Align_12b_R, DACtemp);
						delay_ms(5); //��ʱ5ms
						//���ն����ݲ���
						Single_Write_BH1750(0x01); // power on
						Single_Write_BH1750(0x07); //����
						Single_Write_BH1750(0x65); //����͸����Ϊ100%
						Single_Write_BH1750(0x42);
						Single_Write_BH1750(0x20); //����H-resolution mode����ģʽ
						delay_ms(220);			   //��ʱ220ms
						Multiple_Read_BH1750();	   //�����������ݣ��洢��BUF��

						//���ն����ݴ���
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, BUF[0]); //�򴮿�1���͹��ն����ݣ��߰�λ��
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, BUF[1]); //�򴮿�1���͹��ն����ݣ��Ͱ�λ��
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, 0xFA);
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
							;
						USART_SendData(USART1, 0xAF);
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
							; //�ȴ����ͽ���
						// RS485_TX_EN = 0;//485����Ϊ����

						//��ֵ���ݲ���

						while (!DRDY)
							;
						while (DRDY)
							;
						receive[0] = SPI2_ReadWriteByte(0x00);
						receive[1] = SPI2_ReadWriteByte(0x00);
						receive[2] = SPI2_ReadWriteByte(0x00);
						ADC = (receive[0] << 16) + (receive[1] << 8) + receive[2]; //ͨ����λ�����յ�������8λ���ݺϲ�Ϊһ��24λ����
						vol = (float)ADC * (2.5 / 8388607);						   //����õ���ѹֵ
						TEMP_R = vol * I1;										   //�������������������ֵ����λ10����
						R0 = TEMP_R & 0xFF00;									   //ȡ��ֵ�߰�λ
						R[0] = R0 >> 8;
						R[1] = TEMP_R & 0xFF; //ȡ��ֵ�Ͱ�λ

						//��ֵ���ݴ���
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, R[0]); //�򴮿�1���͹���������ֵ���ݣ��߰�λ��
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, R[1]); //�򴮿�1���͹���������ֵ���ݣ��Ͱ�λ��
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
							;
						USART_SendData(USART1, 0xA5);
						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
							;
						USART_SendData(USART1, 0x5A);
					}
					while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
						;			 //�ȴ����ͽ���
					RS485_TX_EN = 0; // 485����Ϊ����
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
