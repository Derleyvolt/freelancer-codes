#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
    int valor;
    struct Fila *prox, *ant;
} Fila;

Fila* criar_no(int val) {
    Fila* no  = (Fila*)malloc(sizeof(Fila));
    no->valor = val;
    no->prox  = NULL;
    no->ant   = NULL;
    return no;
}

void inserir(Fila** no, int valor) {
    if((*no) == NULL) {
        (*no) = criar_no(valor);
    } else if((*no)->prox == NULL) {
        (*no)->prox = criar_no(valor);
        (*no)->prox->ant = (*no);
    } else {
        inserir(&(*no)->prox, valor);
    }
}

void mostrar(Fila* no) {
    if(no == NULL)
        return;
    printf("%d\n", no->valor);
    Print(no->prox);
}

Fila* remover(Fila* no) {
    if(no != NULL) {
        Fila* temp = no->prox;
        free(no);
        if(temp != NULL)
            temp->ant = NULL;
        return temp;
    }
}

int main() {
    Fila* fila = NULL;
    for(int i = 0; i < 10; i++) {
        inserir(&fila, i+1);
    }

    fila = remover(fila);

    mostrar(fila);
    return 0;
}
