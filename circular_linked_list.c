#include <stdio.h>
#include <stdlib.h>

typedef struct circular_list {
    struct circular_list* prox;
    int value;
} circular_list;

typedef struct list {
    circular_list* start;
    circular_list* final;
    int len;
} list;

list* inicialize_list() {
    list* ls = (list*)malloc(sizeof(list));
    ls->len     = 0;
    ls->start   = NULL;
    ls->final   = NULL;
    return ls;
}

circular_list* create_node(int data) {
    circular_list* ls = (circular_list*)malloc(sizeof(circular_list));
    ls->value          = data;
    ls->prox           = NULL;
    return ls;
}

int search(list* list, int data) {
    circular_list* aux = list->start;
    for(int i = 0; i < list->len; i++) {
        if(aux->value == data) {
            return 1;
        }

        aux = aux->prox;
    }

    return 0;
}

void traverse(list* list, int start) {
    if(start >= list->len) {
        return;
    }

    circular_list* aux = list->start;

    for(int i = 0; i < start; i++) {
        aux = aux->prox;
    }

    for(int i = 0; i < list->len; i++) {
        printf("%d ", aux->value);
        aux = aux->prox;
    }

    printf("\n");
}

void insert(list* list, int data) {
    circular_list* aux = list->start;
    if(aux == NULL) {
        list->start = create_node(data);
        list->final  = list->start;
        list->len++;
        return;
    }

    aux = list->start;

    while(aux != list->final) {
        aux  = aux->prox;
    }

    aux->prox        = create_node(data);
    list->final      = aux->prox;
    aux->prox->prox  = list->start;
    list->len++;
}

void erase(list* list, int data) {
    circular_list* aux = list->start, *temp = list->final;

    for(int i = 0; i < list->len; i++) {
        if(aux->value == data) {
            temp->prox  = aux->prox;

            if(aux == list->start) {
                list->start = aux->prox;
            }

            if(aux == list->final) {
                list->final = temp;
            }

            free(aux);
            list->len--;
            return;
        }

        temp = aux;
        aux  = aux->prox;
    }
}   

int main() {
    list* list = inicialize_list();

    for(int i = 0; i < 10; i++) {
        insert(list, i+1);
    }

    erase(list, 6);

    traverse(list, 5);
    return 0;
}
