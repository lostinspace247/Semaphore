/*
 * Semaphore.h
 *
 *  Created on: Dec 4, 2016
 *      Author: dnelson
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "sys/alt_alarm.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "queue.h"
#include "thread_handler.h"

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

typedef struct s_t{
	unsigned int sem_count;
	unsigned int threads_wait;
	sem_queue *blocked_queue;
}sem_t;

sem_t *mysem_create(int);
void mysem_up(sem_t *);
void mysem_down(sem_t *);
void mysem_delete(sem_t *);
int mysem_waitCount(sem_t *);
int mysem_value(sem_t *);
void initilize_queue(sem_t *);

//sem_t pot_full; //full = 0
//sem_t pot_empty; //empty = H
//sem_t mutex; //mutex = 1

#endif /* SEMAPHORE_H_ */
