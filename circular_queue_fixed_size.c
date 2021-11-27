#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct FILA {
    int vet[MAXN];
    int head, tail, tamanho;
}FILA;

FILA* inicializar() {
    FILA* f = (FILA*)malloc(sizeof(FILA));
    f->head    = 0; 
    f->tail    = 0;
    f->tamanho = 0;
    return f;
}

void inserir(FILA* f, int x) {
    if(f->tamanho >= MAXN) {
        return;
    }

    f->vet[f->tail] = x;
    f->tamanho++;
    f->tail = (f->tail + 1) % MAXN;
}

void deletar(FILA* f) {
    if(f->tamanho > 0) {
        f->head = (f->head + 1) % MAXN;
    }
}

void mostrar(FILA* f) {
    int l = f->head;
    while(l != f->tail) {
        printf("%d ", f->vet[l]);
        l = (l + 1) % MAXN;
    }
}

int main() {
    FILA* f;
    f = inicializar();

    for(int i = 0; i < 10; i++) {
        inserir(f, i+1);
    }

    mostrar(f);
    return 0;
}
