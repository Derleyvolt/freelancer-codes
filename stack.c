#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha {
    int val;
    struct Pilha* ant;
} Pilha;

Pilha* inicializar(int val) {
    Pilha* temp = (Pilha*)malloc(sizeof(Pilha));
    temp->val   = val;
    temp->ant   = NULL;
    return temp;
}

void inserir(Pilha** pl, int val) {
    if((*pl) == NULL) {
        (*pl) = inicializar(val);
        return;
    }

    Pilha* aux = inicializar(val);
    aux->ant = (*pl);
    (*pl) = aux;
}

int remover(Pilha** pl) {
    int val    = (*pl)->val;
    Pilha* aux = (*pl);
    (*pl)      = (*pl)->ant;
    free(aux);
    return val;
}

int top(Pilha* pl) {
    return pl->val;
}

int vazio(Pilha* pl) {
    return pl == NULL;
}

int main() {
    Pilha* pl = NULL;
    inserir(&pl, 1);
    inserir(&pl, 2);
    inserir(&pl, 3);
    inserir(&pl, 4);
    inserir(&pl, 5);

    while(!vazio(pl)) {
        printf("%d\n", remover(&pl));
    }

    return 0;
}
