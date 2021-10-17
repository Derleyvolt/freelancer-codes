#include <stdio.h>

void insertion_sort(int arr[], int n) {
    int aux, i;
    for (int j = 1; j < n; j++) {
        aux = arr[j];
        i = j-1;
        while ((i >= 0) && (arr[i] > aux)) {
            arr[i+1] = arr[i];
            i = i - 1;
        }
        arr[i+1] = aux;
    }
}