/* This program implements a bounded-buffer using producer and consumer processes. Two semaphores are used 
 * for this problem, empty and full, which count the number of empty and full slots in the buffer. A mutex 
 * lock is also used to allow multiple processes to share the same resource, but not simultaneously. 
 * The buffer will consist of an array of buffer_items. Each buffer can hold no more than five processes. 
 * The producer threads will alternate between sleeping for a random period of time and inserting a random 
 * integer into the buffer. The consumer threads will sleep for a random period of time, and upon awakening, 
 * they will attempt to remove an item from the buffer. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0
typedef int buffer_item; // Buffer item
#define BUFFER_SIZE 5

buffer_item START_NUMBER;

int sleepTime;
int insert_item(buffer_item item);

int remove_item(buffer_item *item);

buffer_item buffer[BUFFER_SIZE]; // Buffer used for processes

pthread_mutex_t mutex;
pthread_t tid;
pthread_cond_t condp, condc;
sem_t empty;
sem_t full;

int i = 0; // Count
int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
	/* Implementation of the insert_item() function */
	if (i < BUFFER_SIZE)
	{
		buffer[i] = item; // Insert item into buffer
		i++; // Increment the number of items in buffer
		return 0;
	}
	else
		return -1;
}

int remove_item(buffer_item *item)
{
	/* Implementation of the remove_item function */
	if (i > 0)
	{
		*item = buffer[(i - 1)]; // Remove item from buffer
		i--; // Decrement the number of items in buffer
		return 0;
	}
	else
		return 1;
}

int main(int argc, char *argv[])
{
	/* 1. Get command line arguments argv[1],argv[2],argv[3],argv[4] */
	/* 2. Initialize buffer */
	/* 3. Create producer thread(s) */
	/* 4. Create consumer thread(s) */
	/* 5. Sleep */
	/* 6. Exit */
	
	int sleepTime, producerThreads, consumerThreads;

	int i, j;
	if (argc != 5) // Program must take five arguments
	{
		fprintf(stderr, "Usage: <sleep time> <producer threads> <consumer threads> <start number>\n");
		return -1;
	}
	
	sleepTime = atoi(argv[1]); // Sleep time
	producerThreads = atoi(argv[2]); // The number of producer threads
	consumerThreads = atoi(argv[3]); // The number of consumer threads
	START_NUMBER = atoi(argv[4]); // Process number to start with

	/* Initialize the synchronization tools */
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);

	/* Create the producer and consumer threads */
	for (i = 0; i < producerThreads; i++)
	{
		pthread_create(&tid, NULL, producer, (int) START_NUMBER);
	}

	for (i = 0; i < consumerThreads; i++)
	{
		pthread_create(&tid, NULL, consumer, (int) START_NUMBER);
	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	
	pthread_mutex_destroy(&mutex);
	return 0;
}

void *producer(void *param)
{
	/* Implementation of the producer thread */
	buffer_item item;
	while (TRUE)
	{
		item = (signed int) START_NUMBER++;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		if (insert_item(item))
			printf("Report error condition\n");
		else
			printf("Producer %u produced %d \n", (unsigned int) pthread_self(), item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		break;
	}
	pthread_exit(0);
}

void *consumer(void *param)
{
	/* Implementation of the consumer thread */
	buffer_item item;

	while (TRUE)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		if (remove_item(&item))
			printf("Report error condition\n");
		else
			printf("Consumer %u consumed %d \n", (unsigned int) pthread_self(), item);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		break;
	}
	pthread_exit(0);
}
