#include "buble_sort.c"
#include "insertion_sort.c"
#include "merge_sort.c"
#include "quick_sort.c"
#include "time.h"
#include <stdlib.h>

const int maxn = 100000;

int arr1[100000];
int arr2[100000];
int arr3[100000];
int arr4[100000];

void print_arr2() {
    for(int i = 0; i < maxn; i++) {
        printf("%d ", arr2[i]);
    }
}

void calcular_tempo(int n, int vezes) {
    double merge_tempo     = 0.0;
    double buble_tempo     = 0.0;
    double quick_tempo     = 0.0;
    double insertion_tempo = 0.0;

    int aux = vezes;

    while(aux--) {
	int j;
        for(int i = n-1, j = 0; i >= 0; i--, j++) {
            arr1[j] = i;
	    arr2[j] = i;
            arr3[j] = i;
	    arr4[j] = i;
        }

        clock_t t;

        t = clock();

        merge_sort(arr1, 0, n-1);

        t = clock() - t;

        merge_tempo += ((double)t)/CLOCKS_PER_SEC;

        /////////////////////////////////

        t = clock();

        insertion_sort(arr2, n);

        t = clock() - t;

        insertion_tempo += ((double)t)/CLOCKS_PER_SEC;

        /////////////////////////////////

        t = clock();

        bubble_sort(arr3, n);

        t = clock() - t;

        buble_tempo += ((double)t)/CLOCKS_PER_SEC;

        /////////////////////////////////

        t = clock();

        quick_sort(arr4, 0, n-1);

        t = clock() - t;

        quick_tempo += ((double)t)/CLOCKS_PER_SEC;
    }

    merge_tempo     = merge_tempo/vezes;
    quick_tempo     = quick_tempo/vezes;
    insertion_tempo = insertion_tempo/vezes;
    buble_tempo     = buble_tempo/vezes;

    printf("\n\nCOMPARACAO DE TEMPOS\n\n");

    printf("O tempo do MergeSort foi: %.5f segundos\n", merge_tempo);
    printf("O tempo do Quicksort foi: %.5f segundos\n", quick_tempo);
    printf("O tempo do BubleSort foi: %.5f segundos\n", buble_tempo);
    printf("O tempo do InsertionSort foi: %.5f segundos\n\n", insertion_tempo);
}

int menu() {
    system("cls");
    printf("==== MENU ====\n\n");
    printf("(1) n = 1000\n");
    printf("(2) n = 5000\n");
    printf("(3) n = 10000\n");
    printf("(4) n = 50000\n");
    printf("(5) n = 100000\n");
    int i; scanf("%d", &i);

    return i == 1 ? 1000 : i == 2 ? 5000 : i == 3 ? 10000 : i == 4 ? 50000 : i == 5 ? 100000 : -1;
}

int is_ordered(int n) {
    for(int i = 0; i < n-1; i++) {
        if(arr1[i] > arr1[i+1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    while(1) {
        int n = menu();
        if(n == -1) {
            printf("Voce digitou uma opcao incorreta, tente novamente\n");
        }
        printf("Digite a quantidade de vezes a serem executados os algoritmos (>= 10)\n");
        int vezes; scanf("%d", &vezes);
        calcular_tempo(n, vezes);
        system("pause");
    }

    return 0;
}
