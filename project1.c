#include <stdio.h>

#include "alarm_handler.h"
#include "thread_handler.h"
#include "Semaphore.h"

#define NUM_BEES 11
#define HC 30

/* a delay time used to adjust the frequency of printf messages */
#define MAX 100000

int portions = 0;
static sem_t *pot_full;
static sem_t *mutex;

void mythread(unsigned int tid)
{
    unsigned int i, j, n;
    
    n = (tid % 2 == 0)? 10: 15;
    for(i = 0; i < n; i++)
    {
        printf("This is message %d of thread #%d.\n", i, tid);
//        for(j = 0; j < (tid%3+1)*MAX; j++);
         for (j = 0; j < MAX; j++);
    }   
}

void BeesMakeHoney(unsigned int s_id,int i){
	printf("Pot amount now: %d. Bee: #%d added: %d out of 15 portions\n",portions, s_id, i);
}

void BearEatHoney(int i){
	printf("Bear: #%d ate the honey.\n",i);

}

void honeybee(unsigned int s_id){
	int k = 0;
	while(k < 15){
		mysem_down(mutex);
		portions++;
		BeesMakeHoney(s_id, k);
		k++;

		if(portions == HC){
			mysem_up(pot_full);
		} else {
			mysem_up(mutex);
		}

		int j;
		for(j = 0; j < MAX; j++);
	}
}

void bear(unsigned int s_id){
	int k = 0;
	while(k < 5){
		mysem_down(pot_full);
		portions = 0;
		k++;
		BearEatHoney(k);
		mysem_up(mutex);

		int j;
		for(j = 0; j < MAX; j++);
	}

	mysem_delete(mutex);
	mysem_delete(pot_full);
}
    
void os_primitive()
{
    unsigned int i;
    tcb *thread_pointer;
    
    mutex = mysem_create(1);
    pot_full = mysem_create(0);

    for(i = 0; i < NUM_BEES; i++){
    	if(i == 0){
        	thread_pointer = mythread_create(i, 4096, bear);
        	mythread_start(thread_pointer);
            mythread_join(thread_pointer);
    	} else {
        	thread_pointer = mythread_create(i, 4096, honeybee);
        	mythread_start(thread_pointer);
            mythread_join(thread_pointer);
    	}
    }

    if ( start_alarm_succeed() )
        printf ("Start the alarm successfully\n");
    else
        printf ("Unable to start the alarm\n");

    /* an endless while loop */
    while (1)
    {
        printf ("This is the OS primitive for my exciting CSE351 course projects!\n");
        
        /* delay printf for a while */
        for (i = 0; i < 10*MAX; i++);
    }

}

int main()
{
    os_primitive();
    return 0;
}
