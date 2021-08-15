#include <stdio.h>

void swap(int* a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_down(int *arr, int n, int i) {
    int l = i*2+1;
    int r = i*2+2;

    int tmp = i;

    if(l < n && arr[l] < arr[i]) {
        tmp = l;
    }

    if(r < n && arr[r] < arr[tmp]) {
        tmp = r;
    }

    if(tmp != i) {
        swap(&arr[tmp], &arr[i]);
        heap_down(arr, n, tmp);
    }
}

void heap_up(int* arr, int n, int i) {
    int parent = (i-1)/2;
    if(i > 0 && arr[i] > arr[parent]) {
        swap(&arr[i], &arr[parent]);
        heap_up(arr, n, (i-2)/2);
    }
}

int main() {
    int arr[10] = {1, 5, 7, 4, 2, 3, 1, 9, 5, 2};
    
    int n = sizeof(arr)/sizeof(int);

    for(int i = 0; i < 10; i++) {
        heap_down(arr, 10, i);
    }

    for(int i = 0; i < 10; i++) {
        printf("%d\n", arr[0]);
        swap(&arr[0], &arr[n-i-1]);
        heap_down(arr, n-i-1, 0);
    }

    return 0;
}
