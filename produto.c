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
extern int M;

static int next_value(int id, int iter) {
    return id * NUM_ITEMS + iter;
}

void *produtor(void *arg) {
    int id = *(int *)arg;
    free(arg);

    for (int i = 0; i < NUM_ITEMS; ++i) {
        int item = next_value(id, i);

        sem_wait(&sem_empty);
        pthread_mutex_lock(&buf_mutex);

        buffer.data[buffer.tail] = item;
        buffer.tail = (buffer.tail + 1) % BUFF_SIZE;
        printf("Produtor %d produziu: %d\n", id, item);

        pthread_mutex_unlock(&buf_mutex);
        sem_post(&sem_full);

        usleep(100000);
    }
    return NULL;
}
