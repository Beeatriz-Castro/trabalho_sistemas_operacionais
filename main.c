#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFF_SIZE 10
#define NUM_ITEMS 50
typedef struct {
    int data[BUFF_SIZE];
    int head;
    int tail;
} circ_buf_t;

circ_buf_t      buffer = { .head = 0, .tail = 0 };
sem_t           sem_empty;
sem_t           sem_full;
pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
int             M = 2, N = 2;

void *produtor(void *);
void *consumidor(void *);

static void parse_args(int argc, char *argv[]) {
    if (argc >= 2) M = atoi(argv[1]);
    if (argc >= 3) N = atoi(argv[2]);
    if (M <= 0 || N <= 0) {
        fprintf(stderr, "Uso: %s [produtores] [consumidores]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);

    sem_init(&sem_empty, 0, BUFF_SIZE);
    sem_init(&sem_full,  0, 0);

    pthread_t prod_th[M], cons_th[N];

    for (int i = 0; i < M; ++i) {
        int *id = malloc(sizeof *id);
        *id = i + 1;
        pthread_create(&prod_th[i], NULL, produtor, id);
    }
    for (int j = 0; j < N; ++j) {
        int *id = malloc(sizeof *id);
        *id = j + 1;
        pthread_create(&cons_th[j], NULL, consumidor, id);
    }

    for (int i = 0; i < M; ++i) pthread_join(prod_th[i], NULL);
    for (int j = 0; j < N; ++j) pthread_join(cons_th[j], NULL);

    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    pthread_mutex_destroy(&buf_mutex);

    puts("Processamento completo.");
    return 0;
}
