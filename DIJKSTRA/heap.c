#include <stdio.h>

typedef struct {
    int u, dist;
} vertex;

void swap(vertex* a, vertex *b) {
    vertex temp = *a;
    *a          = *b;
    *b          = temp;
}

void heap_down(vertex *arr, int n, int i) {
    int l = i*2+1;
    int r = i*2+2;

    int tmp = i;

    if(l < n && arr[l].dist < arr[i].dist) {
        tmp = l;
    }

    if(r < n && arr[r].dist < arr[tmp].dist) {
        tmp = r;
    }

    if(tmp != i) {
        swap(&arr[tmp], &arr[i]);
        heap_down(arr, n, tmp);
    }
}

void heap_up(vertex* arr, int n, int i) {
    int parent = (i-1)/2;
    if(i > 0 && arr[i].dist > arr[parent].dist) {
        swap(&arr[i], &arr[parent]);
        heap_up(arr, n, (i-2)/2);
    }
}

// int main() {
//     vertex arr[3] = { {1, 5}, {2, 3}, {5, 7} };

//     int n = sizeof(arr)/sizeof(vertex);

//     for(int i = 0; i < 3; i++) {
//         heap_down(arr, n, i);
//     }

//     for(int i = 0; i < n; i++) {
//         printf("%d\n", arr[0].d);
//         swap(&arr[0], &arr[n-i-1]);
//         heap_down(arr, n-i-1, 0);
//     }

//     return 0;
// }