#ifndef _SYS_QUEUE_H_
#define _SYS_QUEUE_H_

#include "uart.h"


typedef struct {
	uchar* pucData;
	int head; //��¼��ǰ���������ڵ��±�
	int tail; //��¼���һ����Ч���ֵ���һ������
			  //���������һ������û�еĻ�head=tail
    int size; //���д�С
    bool bDynamic;
} Queue;

enum
{
    EM_QUEUE_SUCCESS = 0,
    EM_QUEUE_ERROR,
    EM_QUEUE_PARAM,
    EM_QUEUE_EMPTY,
    EM_QUEUE_FULL,
    EM_QUEUE_OVERFLOW,
};

int   QUEUE_InitStatic(Queue* ptQueue,uchar* pucData,uint uiDataLen);
int   QUEUE_InitDynamic(Queue* ptQueue,uint uiDataLen);
int   QUEUE_Length(const Queue *ptQueue);
bool  QUEUE_IsEmpty(const Queue *ptQueue);
bool  QUEUE_IsFull(const Queue *ptQueue);
uchar QUEUE_Push(Queue *ptQueue, uchar val);
uchar QUEUE_Pop(Queue *ptQueue, uchar *pcVal);

#endif //_SYS_QUEUE_H_

