#include <stdio.h>

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
    ls->inicio  = 0;
    ls->final   = 0;
    return ls;
}

lista_circular* criar_no(int dado) {
    lista_circular* ls = (lista_circular*)malloc(sizeof(lista_circular));
    ls->valor          = dado;
    ls->prox           = NULL;
    return ls;
}


lista_circular* inserir(lista_circular* ls, int dado) {
    if(ls == NULL) {
        ls = criar_no(dado);
        return ls;
    }

    if(ls->valor < dado) {
        ls->prox = inserir(ls->prox, dado);
    } else {
        lista_circular* temp = criar_no(dado);
        temp->prox = ls;
        return temp;
    }
}

void inserir_dado(lista* ls, int dado) {
    if(ls->tamanho == 0) {
        ls->final = inserir(&ls->inicio, dado);
    } else {
        lista_circular* aux = inserir(&ls->inicio, dado);
        if(ls->final->prox != ls->inicio) {
            ls->final = ls->final->prox;
        }
    }

    ls->tamanho++;
}

lista_circular* remover(lista_circular* ls, int dado, lista_circular* final, int* flag) {
    if(ls->valor == dado) {
        *flag = 1;
        lista_circular* aux = ls->prox;
        free(ls);
        return aux;
    } else if(ls != final) {
        ls->prox = remover(ls->prox, dado, final, flag);
    } else {
        return final;
    }
}

lista_circular* remover(lista_circular* ls, int dado, lista_circular* final, int* flag) {
    lista_circular* aux = ls, *temp = NULL;
    while(aux != NULL && aux->valor != dado) {
        temp = aux;
        aux = aux->prox;
    }

    if(aux == NULL) {
        return final;
    }

    if(aux != NULL) {
        
    }
}

int remover_dado(lista* ls, int dado) {
    int flag = 0;
    if(ls->tamanho > 0) {
        lista_circular* aux = remover(ls, dado, ls->final, &flag);
        if(ls->final)
    } else {
        return 0;
    }
}

int main() {

    return 0;
}
