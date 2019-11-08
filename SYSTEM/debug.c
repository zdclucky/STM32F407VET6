#include "debug.h"
#include "uart.h"

#define UART_DEBUG (UART_3)
#define USART_DEBUG USART3


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

_ttywrch(int ch)
{
    ch = ch;
}


//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART_DEBUG->SR&0X40)==0);//循环发送,直到发送完毕   
	USART_DEBUG->DR =  ch;      
	return ch;
}
#endif

void DEBUG_Init(void)
{
    UART_Open(UART_DEBUG,115200,WORD_LENGTH_8b,STOP_BITS_1,PARITY_NO,FLOW_CONTROL_NONE,0);
}



