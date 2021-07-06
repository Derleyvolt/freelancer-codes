#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct que reprenseta cada usuario da fila
typedef struct Fila {
    char nome[50];
    int prioridade;
    struct Fila* ant, *prox;
} Fila;

Fila* criar_no(int prioridade, char nome[]) {
    Fila* f = (struct Fila*)malloc(sizeof(struct Fila));
    f->prox = NULL;
    f->ant  = NULL;
    f->prioridade = prioridade;
    strcpy(f->nome, nome);
    return f;
}

// insere os elementos na fila ordenando-os pela suas
// prioridades
Fila* inserir_recursivamente(Fila** fila, int prioridade, char nome[]) {
    if((*fila) == NULL) {
        (*fila) = criar_no(prioridade, nome);
        return (*fila);
    } else {
        if( prioridade < (*fila)->prioridade ) {
            Fila *f = criar_no(prioridade, nome);
            f->prox = (*fila);
            f->ant  = (*fila)->ant;
            (*fila)->ant = f;
            return f;
        } else {
            (*fila)->prox = inserir_recursivamente(&(*fila)->prox, prioridade, nome);
            return (*fila);
        }
    }
}

// retira o elemento da cabeÃ§a da fila
Fila* retirar(Fila* fila) {
    if(fila == NULL)
        return NULL;
    // pega o proximo elemento
    Fila* f = fila->prox;
    free(fila);

    // verifica se o proximo elemento existe, entÃ£o ele serÃ¡
    // a nova cabeÃ§a da fila
    if(f != NULL) {
        f->ant = NULL;
    }

    return f;
}

// percorre a fila recurisvamente mostrando os dados dos usuarios
void percorrer_recursivo(Fila* fila) {
    if(fila == NULL)
        return;
    if(fila->prioridade == 1) {
        printf("nome: %s  prioridade: usuario preferencial\n", fila->nome);
    } else if(fila->prioridade == 2) {
        printf("nome: %s  prioridade: usuario exclusivo\n", fila->nome);
    } else {
        printf("nome: %s  prioridade: comum\n", fila->nome);
    }

    // chama a si mesmo
    percorrer_recursivo(fila->prox);
}

int main() {
    Fila* fila = NULL;

    inserir_recursivamente(&fila, 0, "rato");
    inserir_recursivamente(&fila, 1, "gato");
    inserir_recursivamente(&fila, 2, "pato");

    percorrer_recursivo(fila);
    return 0;
}
