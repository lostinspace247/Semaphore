#include <stdio.h>
#include "queue.h"

static Q_type queue = {NULL, NULL, 0};

void enqueue(tcb *data)
{
    E_type  *elem;
    
    if ((elem = (E_type *)malloc(sizeof(E_type))) == NULL)
    {
        printf("Unable to allocate space!\n");
        exit(1);
    }
    elem->data = (tcb *)data;
    elem->next = NULL;
    
    if (queue.head == NULL)
        queue.head = elem;
    else
        queue.tail->next = elem;
    queue.tail = elem;

    queue.size++;
}

tcb *dequeue()
{
    E_type  *elem;
    tcb    *data = NULL;
    
    if (queue.size != 0)
    {
        elem = queue.head;
        if (queue.size == 1)
            queue.tail = NULL;
        queue.head = queue.head->next;
        
        queue.size--;
        data = elem->data;
        free(elem);
    }
        
    return data;
}

void blocked_enqueue(tcb *data, sem_queue *blocked_queue)
{
    sem_thread  *elem;

    if ((elem = (sem_thread *)malloc(sizeof(sem_thread))) == NULL)
    {
        printf("Unable to allocate space!\n");
        exit(1);
    }
    elem->data = (tcb *)data;
    elem->next = NULL;

    if (blocked_queue->head == NULL)
        blocked_queue->head = elem;
    else
        blocked_queue->tail->next = elem;
    blocked_queue->tail = elem;

    blocked_queue->blocked_queue_size++;
}

tcb *blocked_dequeue(sem_queue *blocked_queue)
{
    sem_thread  *elem;
    tcb    *data = NULL;

    if (blocked_queue->blocked_queue_size != 0)
    {
        elem = blocked_queue->head;
        if (blocked_queue->blocked_queue_size == 1)
            blocked_queue->tail = NULL;
        blocked_queue->head = blocked_queue->head->next;

        blocked_queue->blocked_queue_size--;
        data = elem->data;
        free(elem);
    }

    return data;
}

unsigned int getQsize()
{
    return queue.size;
}

unsigned int getBlocked_Qsize(sem_queue blocked_queue)
{
    return blocked_queue.blocked_queue_size;
}
