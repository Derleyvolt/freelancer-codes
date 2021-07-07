#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
    int valor;
    struct Fila *prox, *ant;
} Node;

Node* criar_no(int val) {
    Node* no  = (Node*)malloc(sizeof(Node));
    no->valor = val;
    no->prox  = NULL;
    no->ant   = NULL;
    return no;
}

void insert_back(Node** no, int valor) {
    if((*no) == NULL) {
        (*no) = criar_no(valor);
    } else if((*no)->prox == NULL) {
        (*no)->prox = criar_no(valor);
        (*no)->prox->ant = (*no);
    } else {
        insert_back(&(*no)->prox, valor);
    }
}

void Print(Node* no) {
    if(no == NULL)
        return;
    printf("%d\n", no->valor);
    Print(no->prox);
}

Node* remove_front(Node* no) {
    if(no != NULL) {
        Node* temp = no->prox;
        free(no);
        if(temp != NULL)
            temp->ant = NULL;
        return temp;
    }
}

int main() {
    Fila* fila = NULL;
    for(int i = 0; i < 10; i++) {
        insert_back(&fila, i+1);
    }

    fila = remove_front(fila);

    Print(fila);
    return 0;
}
