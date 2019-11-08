#include "sys_queue.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
int QUEUE_InitStatic(Queue* ptQueue,uchar* pucData,uint uiDataLen)
{
    if(!ptQueue || !pucData)
    {
        return EM_QUEUE_PARAM;
    }
    ptQueue->pucData = pucData;
    ptQueue->size = uiDataLen;
    ptQueue->head = 0;
    ptQueue->tail = 0;
    ptQueue->bDynamic = FALSE;
    return EM_QUEUE_SUCCESS;
}

int QUEUE_InitDynamic(Queue* ptQueue,uint uiDataLen)
{
    if(!ptQueue)
    {
        return EM_QUEUE_PARAM;
    }
    ptQueue->pucData = (uchar*)malloc(uiDataLen);
    ptQueue->size = uiDataLen;
    ptQueue->head = 0;
    ptQueue->tail = 0;
    ptQueue->bDynamic = TRUE;
    return EM_QUEUE_SUCCESS;
}

int QUEUE_UnInit(Queue* ptQueue)
{
    if(!ptQueue)
    {
        return EM_QUEUE_PARAM;
    }
    if(ptQueue->bDynamic)
    {
        free(ptQueue->pucData);
        ptQueue->pucData = NULL;
    }
    memset(ptQueue,0x00,sizeof(Queue));
    return EM_QUEUE_SUCCESS;
}

//计算数字个数
int QUEUE_Length(const Queue *ptQueue)
{
    if(!ptQueue)
    {
        return EM_QUEUE_PARAM;
    }
    if(ptQueue->tail >= ptQueue->head)
    {
        return ptQueue->tail - ptQueue->head;
    }
    else
    {
        return ptQueue->size - ptQueue->head + ptQueue->tail;
    }
}

//判断队列是否为空
bool QUEUE_IsEmpty(const Queue *ptQueue) 
{
    if(!ptQueue)
    {
        return FALSE;
    }
    if(ptQueue->tail == ptQueue->head)
    	return TRUE;
    else
        return FALSE;
}

//判断队列是否满的
bool QUEUE_IsFull(const Queue *ptQueue) 
{
    if(!ptQueue)
    {
        return FALSE;
    }
    if(QUEUE_Length(ptQueue) >= ptQueue->size - 1)
        return TRUE;
    else
        return FALSE;
}

//向队列里加入数字
uchar QUEUE_Push(Queue *ptQueue, uchar val) 
{
    if(!ptQueue)
    {
        return EM_QUEUE_PARAM;
    }
	if (QUEUE_IsFull(ptQueue)) 
    {
		return EM_QUEUE_FULL;
	}
    ptQueue->pucData[ptQueue->tail] = val;
	ptQueue->tail = (ptQueue->tail+1)%ptQueue->size;
	return EM_QUEUE_SUCCESS;
}

//从队列里获得数字的（会把数字从队列里删除）
uchar QUEUE_Pop(Queue *ptQueue, uchar *pcVal) 
{
    if(!ptQueue)
    {
        return EM_QUEUE_PARAM;
    }
	if (QUEUE_IsEmpty(ptQueue)) 
    {
		return EM_QUEUE_EMPTY;
	}
    *pcVal = ptQueue->pucData[ptQueue->head];
    ptQueue->head++;
    return EM_QUEUE_SUCCESS;
}

