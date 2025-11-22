#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define SIZE 1000000

int array[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
    }

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }

    printf("Total Sum: %d\n", sum);

    return 0;
}