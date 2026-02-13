#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFF_SIZE 10
#define NUM_ITEMS 50
typedef struct {
    int data[BUFF_SIZE];
    int head;
    int tail;
} circ_buf_t;

extern circ_buf_t   buffer;
extern sem_t        sem_empty;
extern sem_t        sem_full;
extern pthread_mutex_t buf_mutex;
extern int M, N;

void *consumidor(void *arg) {
    int id = *(int *)arg;
    free(arg);

    int quota = (NUM_ITEMS * M) / N;

    for (int i = 0; i < quota; ++i) {
        sem_wait(&sem_full);
        pthread_mutex_lock(&buf_mutex);

        int item = buffer.data[buffer.head];
        buffer.head = (buffer.head + 1) % BUFF_SIZE;
        printf("Consumidor %d consumiu: %d\n", id, item);

        pthread_mutex_unlock(&buf_mutex);
        sem_post(&sem_empty);

        usleep(150000);
    }
    return NULL;
}
