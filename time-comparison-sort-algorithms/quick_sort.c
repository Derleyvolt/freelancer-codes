#include <stdio.h>
#include <stdlib.h>

void trocar_quick(int* a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int partitionx(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low - 1, j = high + 1;
 
    while (1) {
        // Find leftmost element greater than
        // or equal to pivot
        do {
            i++;
        } while (arr[i] < pivot);
 
        // Find rightmost element smaller than
        // or equal to pivot
        do {
            j--;
        } while (arr[j] > pivot);
 
        // If two pointers met.
        if (i >= j)
            return j;
 
        trocar_quick(&arr[i], &arr[j]);
    }
}

int Partition(int arr[], int low, int high) {
    int pivot, idx;
    idx   = low;
    pivot = high;

    for(int i=low; i < high; i++) {
        if(arr[i] < arr[pivot]) {
            trocar_quick(&arr[i], &arr[idx]);
            idx++;
        }
    }

    trocar_quick(&arr[pivot], &arr[idx]);
    return idx;
}

int partition(int arr[], int low, int high)
{
    // pivot
    int pivot = arr[high];
   
    // Index of smaller element
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller
        // than or equal to pivot
        if (arr[j] <= pivot) {
 
            // increment index of
            // smaller element
            i++;
            trocar_quick(&arr[i], &arr[j]);
        }
    }
    trocar_quick(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
// Generates Random Pivot, swaps pivot with
// end element and calls the partition function
int partition_r(int arr[], int low, int high)
{
    // Generate a random number in between
    // low .. high
    int random = low + rand() % (high - low);
 
    // Swap A[random] with A[high]
    trocar_quick(&arr[random], &arr[high]);
 
    return partition(arr, low, high);
}
 
void quick_sort(int arr[], int low, int high) {
    int idx;

    static int i = 0;

    if(low < high) {
        //printf("%d\n", i);
        //i++;
        idx = Partition(arr, low, high);

        quick_sort(arr, low, idx-1);
        quick_sort(arr, idx+1, high);
    }
}
