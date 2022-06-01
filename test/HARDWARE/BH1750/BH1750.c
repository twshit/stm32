#include "BH1750.h"
#include "myiic.h"
#include "delay.h"

u8  BUF[2];


 /*********************************************************
通过IIC向BH1750发送指令 *已改动*
*********************************************************/
void Single_Write_BH1750(u8 REG_Address) //REG_Address:要发送的指令
{
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	while(IIC_Wait_Ack());
	IIC_Send_Byte(REG_Address);
	while(IIC_Wait_Ack());
	IIC_Stop();
}

/*********************************************************
连续读出BH1750内部数据  *已改动*
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
读出数据并合成实际光强值  *已改动*
*********************************************************/
void Get_Sunlight_Value()
{
	int dis_data=0;
	float temp;
	u8 i=0;
	Single_Write_BH1750(0x01);// power on  
	Single_Write_BH1750(0x10);// H- resolution mode
	delay_us(180);//延时180ms
	Multiple_Read_BH1750();//连续读出数据，存储在BUF中  
	for(i=0;i<3;i++)  
	//printf("0X%X ",BUF[i]);
	dis_data=BUF[0];
	dis_data=(dis_data<<8)+BUF[1];//合成数据 
	temp=(float)dis_data/1.2;
	//printf("Sunlight=%0.2f lx\n",temp);
}

/*********************************************************
BH1750芯片初始化
*********************************************************/
void BH1750_Init(void)
{
  Single_Write_BH1750(0x01); //通电
	Single_Write_BH1750(0x07); //重置
	Single_Write_BH1750(0x42);
	Single_Write_BH1750(0x65); //设置透光率为100%
	Single_Write_BH1750(0x10); //设置为高分辨率模式（H-resolution Mode)
}
