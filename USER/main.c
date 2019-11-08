#include "stdio.h"	
#include "sys.h"
#include "delay.h"
#include "stm32f4xx_conf.h"

//#include "usart.h"
#include "led.h"
#include "debug.h"

extern uint32_t SystemCoreClock;

int main(void)
{ 
    DEBUG_Init();
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	
  /**下面是通过直接操作库函数的方式实现IO控制**/
	while(1)
	{
        printf("SystemCoreClock = %d\n",SystemCoreClock);
	    LED_Open(LED0);
        LED_Close(LED1);
    	delay_ms(500);  		   //延时300ms
    	LED_Open(LED1);
        LED_Close(LED0);               //延时300ms
        delay_ms(500);
	}
}



 



