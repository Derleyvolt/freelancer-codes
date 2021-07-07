#include <stdio.h>
#include <stdlib.h>

typedef struct DList {
    int valor;
    struct DList *prox, *ant;
} Node;

Node* criar_no(int val) {
    Node* no  = (Node*)malloc(sizeof(Node));
    no->valor = val;
    no->prox  = NULL;
    no->ant   = NULL;
    return no;
}

void inserir(Node** no, int valor) {
    if((*no) == NULL) {
        (*no) = criar_no(valor);
    } else if((*no)->prox == NULL) {
        (*no)->prox = criar_no(valor);
        (*no)->prox->ant = (*no);
    } else {
        inserir(&(*no)->prox, valor);
    }
}

void Print(Node* no) {
    if(no == NULL)
        return;
    printf("%d\n", no->valor);
    Print(no->prox);
}

Node* remover_elemento(Node* no, int valor) {
    if(no == NULL) {
        return NULL;
    }

    Node* temp = no;

    while(no != NULL && no->valor != valor) {
        no = no->prox;
    }

    if(no == NULL)
        return temp;

    if(no->ant == NULL) {
        temp = no->prox;
        if(temp != NULL)
            temp->ant = NULL;
        free(no);
        return temp;
    }

    Node* aux = no->prox;

    if(aux != NULL) {
        aux->ant = no->ant;
    }

    no->ant->prox = no->prox;

    free(no);
    return temp;
}

int main() {
    DList* lista_dupla = NULL;
    for(int i = 0; i < 10; i++) {
        inserir(&lista_dupla, i+1);
    }

    lista_dupla = remover_elemento(Fila, 1);
    lista_dupla = remover_elemento(Fila, 7);
    lista_dupla = remover_elemento(Fila, 10);

    Print(Fila);
    return 0;
}
