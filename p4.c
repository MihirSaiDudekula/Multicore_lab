#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 16
#define NUM_THREADS 4

int array[SIZE] = {38, 27, 43, 3, 9, 82, 10, 29, 42, 2, 1, 8, 5, 6, 7, 4};
int temp[SIZE];

typedef struct {
    int left;
    int right;
} thread_data;

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while (i <= mid)
        temp[k++] = array[i++];

    while (j <= right)
        temp[k++] = array[j++];

    for (i = left; i <= right; i++)
        array[i] = temp[i];
}

void merge_sort(int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(left, mid, right);
}

void* threaded_sort(void* arg) {
    thread_data* data = (thread_data*)arg;
    merge_sort(data->left, data->right);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data tdata[NUM_THREADS];

    int part = SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        tdata[i].left = i * part;
        tdata[i].right = (i == NUM_THREADS - 1) ? SIZE - 1 : (i + 1) * part - 1;
        pthread_create(&threads[i], NULL, threaded_sort, &tdata[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    for (int i = 1; i < NUM_THREADS; i++) {
        merge(0, i * part - 1, (i == NUM_THREADS - 1) ? SIZE - 1 : (i + 1) * part - 1);
    }

    printf("Sorted Array:\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}