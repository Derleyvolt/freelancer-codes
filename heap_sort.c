#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void swap(int* A, int* B) {
    int aux = *A;
    *A = *B;
    *B = aux;
}

void heap_down(int arr[], int n, int i) {
    int l = i*2+1;
    int r = i*2+2;

    int temp = i;  

    if(r < n && arr[temp] < arr[r])
        temp = r;
    if(l < n && arr[temp] < arr[l])
        temp = l;

    if(temp != i) {
        swap(&arr[temp], &arr[i]);
        heap_down(arr, n, temp);
    }
}

void heap_sort(int arr[], int n) {
    for(int i = n/2; i >= 0; i--)
        heap_down(arr, n, i);

    for(int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heap_down(arr, i, 0);
    }
}

int main() {
    srand(time(NULL));

    int arr[50];

    for(int i = 0; i < 50; i++) {
        arr[i] = rand() % 10000;
    }

    heap_sort(arr, 50);

    for(int i = 0; i < 50; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
