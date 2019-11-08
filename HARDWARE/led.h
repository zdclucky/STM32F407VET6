#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 	

#if 0
//LED端口定义
#define LED0 PAout(6)	// D2
#define LED1 PAout(7)	// D3	 
#endif

typedef enum _LED
{
    LED0,
    LED1,
    LED_MAX,
}LED;

void LED_Init(void);//初始化	
void LED_Open(LED led);
void LED_Close(LED led);
#endif
