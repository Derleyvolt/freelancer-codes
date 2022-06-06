#include <stdio.h>
#include <stdlib.h>

typedef struct lista_circular {
    struct lista_circular* prox;
    int valor;
} lista_circular;

typedef struct lista {
    lista_circular* inicio;
    lista_circular* final;
    int tamanho;
} lista;

lista* iniciar_lista() {
    lista* ls = (lista*)malloc(sizeof(lista));
    ls->tamanho = 0;
    ls->inicio  = NULL;
    ls->final   = NULL;
    return ls;
}

lista_circular* criar_no(int dado) {
    lista_circular* ls = (lista_circular*)malloc(sizeof(lista_circular));
    ls->valor          = dado;
    ls->prox           = NULL;
    return ls;
}

int buscar(lista* list, int dado) {
    lista_circular* aux = list->inicio;
    for(int i = 0; i < list->tamanho; i++) {
        if(aux->valor == dado) {
            return 1;
        }

        aux = aux->prox;
    }

    return 0;
}

void percorrer(lista* list, int start) {
    if(start >= list->tamanho) {
        return;
    }

    lista_circular* aux = list->inicio;

    for(int i = 0; i < start; i++) {
        aux = aux->prox;
    }

    for(int i = 0; i < list->tamanho; i++) {
        printf("%d ", aux->valor);
        aux = aux->prox;
    }

    printf("\n");
}

void inserir(lista* list, int dado) {
    lista_circular* aux = list->inicio;
    if(aux == NULL) {
        list->inicio = criar_no(dado);
        list->final  = list->inicio;
        list->tamanho++;
        return;
    }

    aux = list->inicio;

    while(aux != list->final) {
        aux  = aux->prox;
    }

    aux->prox        = criar_no(dado);
    list->final      = aux->prox;
    aux->prox->prox  = list->inicio;
    list->tamanho++;
}

void remover(lista* list, int dado) {
    lista_circular* aux = list->inicio, *temp = list->final;

    for(int i = 0; i < list->tamanho; i++) {
        if(aux->valor == dado) {
            temp->prox  = aux->prox;

            if(aux == list->inicio) {
                list->inicio = aux->prox;
            }

            if(aux == list->final) {
                list->final = temp;
            }

            free(aux);
            list->tamanho--;
            return;
        }

        temp = aux;
        aux = aux->prox;
    }
}   

int main() {
    lista* list = iniciar_lista();

    for(int i = 0; i < 10; i++) {
        inserir(list, i+1);
    }

    remover(list, 6);
    
    percorrer(list, 5);
    return 0;
}
