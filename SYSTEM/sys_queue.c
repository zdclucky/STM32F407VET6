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

//�������ָ���
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

//�ж϶����Ƿ�Ϊ��
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

//�ж϶����Ƿ�����
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

//��������������
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

//�Ӷ����������ֵģ�������ִӶ�����ɾ����
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

