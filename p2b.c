#include <pthread.h>
#include <stdio.h>

void* print_message(void* thread_id) {
    int tid = *((int*)thread_id);
    printf("Hello from thread %d\n", tid);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5];

    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, print_message, &thread_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}