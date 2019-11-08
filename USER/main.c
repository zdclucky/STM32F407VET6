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
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	
  /**������ͨ��ֱ�Ӳ����⺯���ķ�ʽʵ��IO����**/
	while(1)
	{
        printf("SystemCoreClock = %d\n",SystemCoreClock);
	    LED_Open(LED0);
        LED_Close(LED1);
    	delay_ms(500);  		   //��ʱ300ms
    	LED_Open(LED1);
        LED_Close(LED0);               //��ʱ300ms
        delay_ms(500);
	}
}



 



