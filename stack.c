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

    No* aux  = criar_no(val);
    aux->ant = (*ptr)->final;
    (*ptr)->final = aux;
}

int desenfileirar(Pilha** ptr) {
    if((*ptr)->final != NULL) {
        No* aux       = (*ptr)->final;
        (*ptr)->final = (*ptr)->final->ant;
        free(aux);
        return 1;
    }
    return 0;
}

int obter(Pilha** ptr) {
    if((*ptr)->final != NULL) {
        return (*ptr)->final->val;
    }
}

void liberar_pilha(Pilha** pl) {
    while(desenfileirar(pl));
}

int pilha_vazia(Pilha** pl) {
    if((*pl)->final == NULL) {
        return 1;
    }
    return 0;
}
