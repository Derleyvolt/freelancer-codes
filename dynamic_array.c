#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    char buf[100];
    int  freq;
} data;

typedef struct array {
    data* ptr;
    int length;
    int capacity;
} array;

array* inicialize() {
    array* aux      = (array*)malloc(sizeof(array));
    aux->ptr        = (data*)malloc(sizeof(data) * 100);
    aux->capacity   = 100;
    aux->length     = 0;

    return aux;
}

void push_back(array* arr, data val) {
    if(arr->length == arr->capacity) {
        data* temp = (data*)malloc(sizeof(data) * arr->length * 2);

        for(int i = 0; i < arr->length; i++) {
            temp[i] = arr->ptr[i];
        }

        free(arr->ptr);
        arr->ptr = temp;
        arr->capacity = arr->capacity * 2;
    }

    arr->ptr[arr->length] = val;
    arr->length++;
}

void push_pop(array* arr) {
    arr->length = arr->length - (arr->length > 0);
}

int main() {
    array* arr;
    arr = inicialize();

    data dt;

    for(int i = 0; i < 50; i++) {
        dt.freq = i+1;
        push_back(arr, dt);
    }

    for(int i = 0; i < arr->length; i++) {
        printf("%d ", arr->ptr[i].freq);
    }

    printf("\n");
    return 0;
}
