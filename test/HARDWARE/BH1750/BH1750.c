#include "BH1750.h"
#include "myiic.h"
#include "delay.h"

u8  BUF[2];


 /*********************************************************
ͨ��IIC��BH1750����ָ�� *�ѸĶ�*
*********************************************************/
void Single_Write_BH1750(u8 REG_Address) //REG_Address:Ҫ���͵�ָ��
{
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	while(IIC_Wait_Ack());
	IIC_Send_Byte(REG_Address);
	while(IIC_Wait_Ack());
	IIC_Stop();
}

/*********************************************************
��������BH1750�ڲ�����  *�ѸĶ�*
*********************************************************/
void Multiple_Read_BH1750()
{   
  IIC_Start();
  IIC_Send_Byte(SlaveAddress+1);
	while(IIC_Wait_Ack());
	BUF[0] = IIC_Read_Byte(1);
  BUF[1] = IIC_Read_Byte(0);
	IIC_Stop();
	delay_us(5);
}
 
/*********************************************************
�������ݲ��ϳ�ʵ�ʹ�ǿֵ  *�ѸĶ�*
*********************************************************/
void Get_Sunlight_Value()
{
	int dis_data=0;
	float temp;
	u8 i=0;
	Single_Write_BH1750(0x01);// power on  
	Single_Write_BH1750(0x10);// H- resolution mode
	delay_us(180);//��ʱ180ms
	Multiple_Read_BH1750();//�����������ݣ��洢��BUF��  
	for(i=0;i<3;i++)  
	//printf("0X%X ",BUF[i]);
	dis_data=BUF[0];
	dis_data=(dis_data<<8)+BUF[1];//�ϳ����� 
	temp=(float)dis_data/1.2;
	//printf("Sunlight=%0.2f lx\n",temp);
}

/*********************************************************
BH1750оƬ��ʼ��
*********************************************************/
void BH1750_Init(void)
{
  Single_Write_BH1750(0x01); //ͨ��
	Single_Write_BH1750(0x07); //����
	Single_Write_BH1750(0x42);
	Single_Write_BH1750(0x65); //����͸����Ϊ100%
	Single_Write_BH1750(0x10); //����Ϊ�߷ֱ���ģʽ��H-resolution Mode)
}
