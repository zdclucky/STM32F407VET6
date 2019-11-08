#include "debug.h"
#include "uart.h"

#define UART_DEBUG (UART_3)
#define USART_DEBUG USART3


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 

_ttywrch(int ch)
{
    ch = ch;
}


//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART_DEBUG->SR&0X40)==0);//ѭ������,ֱ���������   
	USART_DEBUG->DR =  ch;      
	return ch;
}
#endif

void DEBUG_Init(void)
{
    UART_Open(UART_DEBUG,115200,WORD_LENGTH_8b,STOP_BITS_1,PARITY_NO,FLOW_CONTROL_NONE,0);
}



