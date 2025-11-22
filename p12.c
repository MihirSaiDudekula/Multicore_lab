#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_TASKS 10
#define NUM_THREADS 4

int tasks[NUM_TASKS];

void* process_tasks(void* arg) {
    int thread_id = *(int*)arg;
    for (int i = thread_id; i < NUM_TASKS; i += NUM_THREADS) {
        printf("Thread %d processing task %d\n", thread_id, tasks[i]);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_TASKS; i++) {
        tasks[i] = i + 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, process_tasks, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}