#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_TASKS 10

int buffer[BUFFER_SIZE];
int count = 0, in = 0, out = 0;

pthread_mutex_t lock;
pthread_cond_t not_full, not_empty;

void* producer(void* arg) {
    for (int i = 1; i <= NUM_TASKS; i++) {
        pthread_mutex_lock(&lock);

        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &lock);

        buffer[in] = i;
        printf("Produced Task: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= NUM_TASKS; i++) {
        pthread_mutex_lock(&lock);

        while (count == 0)
            pthread_cond_wait(&not_empty, &lock);

        int task = buffer[out];
        printf("Consumed Task: %d\n", task);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}