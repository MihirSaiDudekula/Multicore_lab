#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 3

int A[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int B[SIZE][SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int C[SIZE][SIZE];

typedef struct {
    int row;
} thread_data;

void* add_matrices(void* arg) {
    thread_data* data = (thread_data*)arg;
    int i = data->row;

    printf("Thread %lu is processing row %d\n", (unsigned long)pthread_self(), i);

    for (int j = 0; j < SIZE; j++) {
        C[i][j] = A[i][j] + B[i][j];
    }

    free(data);
    return NULL;
}

int main() {
    pthread_t threads[SIZE];

    for (int i = 0; i < SIZE; i++) {
        thread_data* data = malloc(sizeof(thread_data));
        data->row = i;
        pthread_create(&threads[i], NULL, add_matrices, data);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nResultant Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}