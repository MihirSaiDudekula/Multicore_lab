#include <stdio.h>
#include <omp.h>

void blur() {
    printf("Blurring the image...\n");
}

void sharpen() {
    printf("Sharpening the image...\n");
}

void contrast() {
    printf("Adjusting contrast...\n");
}

void resize_image() {
    printf("Resizing the image...\n");
}

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            blur();

            #pragma omp task
            sharpen();

            #pragma omp task
            contrast();

            #pragma omp task
            resize_image();
        }
    }

    return 0;
}