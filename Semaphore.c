/*
 * Semaphore.c
 *
 *  Created on: Dec 4, 2016
 *      Author: dnelson
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sys/alt_alarm.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "Semaphore.h"

//static alt_u32 s_id;

sem_t *mysem_create(int id){
	sem_t *temp_sem;

	temp_sem = (sem_t *)malloc(sizeof(sem_t));
	temp_sem -> sem_count = id;
	temp_sem -> threads_wait = 0;
	initilize_queue(temp_sem);

	return temp_sem;
}

void mysem_up(sem_t *temp){

	DISABLE_INTERRUPTS();
	if(mysem_waitCount(temp) > 0){
		tcb *thread = blocked_dequeue(temp->blocked_queue);
		mythread_start(thread);
	} else {
		temp->sem_count++;
	}
	ENABLE_INTERRUPTS();
}

void mysem_down(sem_t *temp){

	DISABLE_INTERRUPTS();
	if(mysem_value(temp) > 0){
		temp->sem_count--;
		ENABLE_INTERRUPTS();
	} else {
		tcb *thread = get_current_running_thread();
		mythread_block(thread);
		blocked_enqueue(thread, temp->blocked_queue);
		temp->threads_wait = temp->blocked_queue->blocked_queue_size;
		ENABLE_INTERRUPTS();
		while(thread->state == BLOCKED);
	}

}

void mysem_delete(sem_t *temp){
	DISABLE_INTERRUPTS();
	free(temp->blocked_queue);
	free(temp);
	ENABLE_INTERRUPTS();

}

int mysem_waitCount(sem_t *temp){
	return temp->threads_wait;
}

int mysem_value(sem_t *temp){
	return temp->sem_count;
}

void initilize_queue(sem_t *temp_sem){
	temp_sem -> blocked_queue = (sem_queue *)malloc(sizeof(sem_queue));

	temp_sem -> blocked_queue -> head = NULL;
	temp_sem -> blocked_queue -> tail = NULL;
	temp_sem -> blocked_queue -> blocked_queue_size = 0;
}
