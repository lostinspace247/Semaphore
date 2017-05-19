/* 
    Name:   queue.h
    Author: Dongyuan Zhan
    Date:   11/20/2010

Description:
    Functions used to implment a queue and its operations
*/

#include "thread_handler.h"

typedef struct element_type
{
    tcb                *data;
    struct element_type *next;
} E_type;

typedef struct queue_type
{
    E_type              *head;
    E_type              *tail;
    unsigned int        size;
} Q_type;

typedef struct sem_queue_element{
	tcb                      *data;
	struct sem_queue_element *next;
} sem_thread;

typedef struct sem_queue{
	sem_thread *head;
	sem_thread *tail;
	unsigned int blocked_queue_size;
}sem_queue;

void enqueue(tcb *data);

tcb *dequeue();

void blocked_enqueue(tcb *, sem_queue *);

tcb *blocked_dequeue(sem_queue *);

unsigned int getQsize();

unsigned int getBlocked_Qsize(sem_queue);
