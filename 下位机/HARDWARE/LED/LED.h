#ifndef _LED_H
#define _LED_H
#include "sys.h"

#define D3 PCout(15)   	//D3 LED�˿ڶ���
#define I1 400;					//sw=1 ������ĵ�������ʮ(��������ʱѡ�ã���λ10����) 
#define	I2 200000;			//sw=0 С�����ĵ�������ʮ(�ⰵ����ʱѡ�ã���λ10����) 

void LED_Init(void);  //LED��ʼ��
 
#endif
