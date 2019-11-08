#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
//#include "sys.h" 

#ifndef uint
typedef unsigned int uint;
typedef unsigned char uchar;
typedef enum {FALSE = 0,TRUE,}bool;
enum
{
    EM_SUCCESS = 0,
    EM_ERROR,
    EM_ERR_PARAMS,
};

#endif

enum
{
    EM_UART_SUCCESS = 0,
    EM_UAER_ERROR,
    EM_UART_PARAM,
    EM_UART_OPENED,
    EM_UART_CLOSE,
};

typedef enum
{
    UART_1 = 0,
    UART_2,
    UART_3,
    UART_MAX,
}EUART;

typedef enum
{
    WORD_LENGTH_8b = 0,
    WORD_LENGTH_9b,
    WORD_LENGTH_MAX,
}EWordLength;


typedef enum
{
    STOP_BITS_1 = 0,
    STOP_BITS_0_5,
    STOP_BITS_2,
    STOP_BITS_1_5,
    STOP_BITS_MAX,
}EStopBits;

typedef enum
{
    PARITY_NO = 0,
    PARITY_EVEN,
    PARITY_ODD,
    PARITY_MAX,
}EParity;

typedef enum
{
    FLOW_CONTROL_NONE = 0,
    FLOW_CONTROL_RTS,
    FLOW_CONTROL_CTS,
    FLOW_CONTROL_RTS_CTS,
    FLOW_CONTROL_MAX,
}EFlowControl;

int UART_Open(EUART eUartId,uint uiBaudRate,EWordLength eWordLength, EStopBits eStopBits,EParity eParity,EFlowControl eFlowControl,uint uiSize);
int UART_Close(EUART eUartId);
int UART_Write(EUART eUartId,uchar* pucSendBuf,uint uiSendLen,uint uiTimeout);
int UART_Read(EUART eUartId,uchar* pucRecvBuf,uint uiRecvLen,uint uiTimeout);
void USART_IRQHandler(void);
#endif


