#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int val;
    struct no* ant;
} No;

typedef struct pilha {
    No* final;
} Pilha;

Pilha* inicializar() {
    Pilha* aux = (Pilha*)malloc(sizeof(Pilha));
    aux->final = NULL;
    return aux;
}

No* criar_no(int val) {
    No* aux   = (No*)malloc(sizeof(No));
    aux->val  = val;
    aux->ant  = NULL;
    return aux;
}

void enfileirar(Pilha** ptr, int val) {
    if((*ptr)->final == NULL) {
        (*ptr)->final = criar_no(val);
        return;
    }

    No* aux = criar_no(val);
    aux->ant = (*ptr)->final;
    (*ptr)->final = aux;
}

float desenfileirar(Pilha** ptr) {
    if((*ptr)->final != NULL) {
        No* aux       = (*ptr)->final;
        (*ptr)->final = (*ptr)->final->ant;
        free(aux);
        return 1;
    }
    return 0;
}

float obter(Pilha** ptr) {
    return (*ptr)->final->val;
}

void liberar_pilha(Pilha** pl) {
    while(desenfileirar(pl));
}

void percorrer(Pilha** pl) {
    if((*pl)->final == NULL) {
        return;
    }

    No* aux = (*pl)->final;
    while(aux != NULL) {
        printf("%.2f\n", aux->val);
        aux = aux->ant;
    }
}

int pilha_vazia(Pilha** pl) {
    if((*pl)->final == NULL) {
        return -1;
    }
    return 1;
}

int main() {
    Pilha* ptr = inicializar();
    enfileirar(&ptr, 10);

    desenfileirar(&ptr);

    printf("%p\n", ptr->final);
    return 0;
}
