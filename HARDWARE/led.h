#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 	

#if 0
//LED�˿ڶ���
#define LED0 PAout(6)	// D2
#define LED1 PAout(7)	// D3	 
#endif

typedef enum _LED
{
    LED0,
    LED1,
    LED_MAX,
}LED;

void LED_Init(void);//��ʼ��	
void LED_Open(LED led);
void LED_Close(LED led);
#endif
