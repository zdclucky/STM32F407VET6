#include "uart.h"
#include "sys_queue.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef struct
{
    EUART eUartId;
    USART_TypeDef* pUSARTx;
    Queue queue;
    uchar* pucRecvBuf;
    bool bOpen;
}UartObject;

static UartObject gstUartObjs[UART_MAX] = {0};


static uint16_t UART_I_GetWordLength(EWordLength WordLength)
{
    switch(WordLength)
    {
    case WORD_LENGTH_8b:
        return USART_WordLength_8b;
    case WORD_LENGTH_9b:
        return USART_WordLength_9b;
    default:
        return USART_WordLength_8b;
    }
}

static uint16_t UART_I_GetStopBits(EStopBits StopBits)
{
    switch(StopBits)
    {
    case STOP_BITS_1:
        return USART_StopBits_1;
    case STOP_BITS_0_5:
        return USART_StopBits_0_5;
    case STOP_BITS_2:
        return USART_StopBits_2;
    case STOP_BITS_1_5:
        return USART_StopBits_1_5;
    default:
        return USART_StopBits_1;
    }
}

static uint16_t UART_I_GetParity(EParity Parity)
{
    switch(Parity)
    {
    case PARITY_NO:
        return USART_Parity_No;
    case PARITY_EVEN:
        return USART_Parity_Even;
    case PARITY_ODD:
        return USART_Parity_Odd;
    default:
        return USART_Parity_No;
    }
}

static uint16_t UART_I_GetFlowControl(EFlowControl FlowControl)
{
    switch(FlowControl)
    {
    case FLOW_CONTROL_NONE:
        return USART_HardwareFlowControl_None;
    case FLOW_CONTROL_RTS:
        return USART_HardwareFlowControl_RTS;
    case FLOW_CONTROL_CTS:
        return USART_HardwareFlowControl_CTS;
    case FLOW_CONTROL_RTS_CTS:
        return USART_HardwareFlowControl_RTS_CTS;
    default:
        return USART_HardwareFlowControl_None;
    }
}

int UART_Open(EUART eUartId,uint uiBaudRate,EWordLength eWordLength, EStopBits eStopBits,EParity eParity,EFlowControl eFlowControl,uint uiSize)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    uint8_t ui8IRQChannel;
    if(gstUartObjs[eUartId].bOpen)
    {
        return EM_UART_OPENED;
    }
    memset(&gstUartObjs[eUartId],0x00,sizeof(UartObject));
    if(uiSize)
    {
        gstUartObjs[eUartId].pucRecvBuf = (uchar*)malloc(uiSize);
    }
    QUEUE_InitStatic(&gstUartObjs[eUartId].queue,gstUartObjs[eUartId].pucRecvBuf,uiSize);
    //IO初始化
	switch(eUartId)
	{
    case  UART_1:
        //时钟使能
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
	    //串口1对应引脚复用映射
    	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
    	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
    	//USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10
    	gstUartObjs[eUartId].pUSARTx = USART1;
        ui8IRQChannel = USART1_IRQn;
        break;
    case  UART_2:
        //时钟使能
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOD时钟
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART1时钟
	    //串口1对应引脚复用映射
    	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOD5复用为USART2
    	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOD6复用为USART2
    	//USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOD5与GPIOD6
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PD5,PD6
        gstUartObjs[eUartId].pUSARTx = USART2;
        ui8IRQChannel = USART2_IRQn;
        break;
    case  UART_3:
        //时钟使能
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOD时钟
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART1时钟
	    //串口1对应引脚复用映射
    	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART2); //GPIOD5复用为USART2
    	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART2); //GPIOD6复用为USART2
    	//USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOD5与GPIOD6
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PD5,PD6
        gstUartObjs[eUartId].pUSARTx = USART3;
        ui8IRQChannel = USART3_IRQn;
        break;
	}
    
    //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = uiBaudRate;//波特率设置
	USART_InitStructure.USART_WordLength = UART_I_GetWordLength(eWordLength);//字长为8位数据格式
	USART_InitStructure.USART_StopBits = UART_I_GetStopBits(eStopBits);//一个停止位
	USART_InitStructure.USART_Parity = UART_I_GetParity(eParity);//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = UART_I_GetFlowControl(eFlowControl);//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(gstUartObjs[eUartId].pUSARTx, &USART_InitStructure); //初始化串口

    USART_Cmd(gstUartObjs[eUartId].pUSARTx, ENABLE);  //使能串口
    USART_ClearFlag(gstUartObjs[eUartId].pUSARTx, USART_FLAG_TC);

    USART_ITConfig(gstUartObjs[eUartId].pUSARTx, USART_IT_RXNE, ENABLE);//开启相关中断
	//Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = ui8IRQChannel;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	return EM_UART_SUCCESS;
}

int UART_Close(EUART eUartId)
{
    return EM_UART_SUCCESS;
}

int UART_Write(EUART eUartId,uchar* pucSendBuf,uint uiSendLen,uint uiTimeout)
{
    uint i = 0;
    uint uiRet = EM_SUCCESS;
    for(i = 0;i < uiSendLen;i++)
    {
        USART_SendData(gstUartObjs[eUartId].pUSARTx,pucSendBuf[i]);
        while(USART_GetFlagStatus(gstUartObjs[eUartId].pUSARTx,USART_FLAG_TC)!=SET);//等待发送结束
        uiRet++;
        //超时判断
    }
    return uiRet;
}

int UART_Read(EUART eUartId,uchar* pucRecvBuf,uint uiRecvLen,uint uiTimeout)
{
    UartObject* pObj = &gstUartObjs[eUartId];
    uint uiLen = 0;
    uint i = 0;
    if(QUEUE_Length(&pObj->queue) >= uiRecvLen)
        uiLen = uiRecvLen;
    else
        uiLen = QUEUE_Length(&pObj->queue);
    for(i = 0;i < uiLen;i++)
    {
        QUEUE_Pop(&pObj->queue,&pucRecvBuf[i]);
    }
    return uiLen;
}

void USART_IRQHandler(void) 
{
    EUART eUartId = UART_1;
    uchar ucVal;
    if(NVIC_GetActive(USART1_IRQn))
    {
        eUartId = UART_1;
    }
    else if(NVIC_GetActive(USART2_IRQn))
    {
        eUartId = UART_2;
    }
    else if(NVIC_GetActive(USART3_IRQn))
    {
        eUartId = UART_3;
    }
    else
    {
        return;
    }
    if(USART_GetITStatus(gstUartObjs[eUartId].pUSARTx, USART_IT_RXNE) == RESET)
    {
        return;
    }
    USART_ITConfig(gstUartObjs[eUartId].pUSARTx, USART_IT_RXNE, DISABLE);
    while(USART_GetFlagStatus(gstUartObjs[eUartId].pUSARTx, USART_FLAG_RXNE) != RESET)
    {
        ucVal = USART_ReceiveData(gstUartObjs[eUartId].pUSARTx);
        if(EM_UART_SUCCESS != QUEUE_Push(&gstUartObjs[eUartId].queue,ucVal))
        {
            break;
        }
    }
}


