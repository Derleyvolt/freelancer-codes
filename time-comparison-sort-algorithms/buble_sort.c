#include <stdio.h>

void trocar_buble(int* a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(int* arr, int tam) {
    int n = tam;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                trocar_buble(&arr[j], &arr[j+1]);
        }
    }
} 