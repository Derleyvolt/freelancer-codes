#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
typedef struct arv {
    int data;
    struct arv* esq;
    struct arv* dir;
} arv;
 
void emOrdem(arv* raiz) {
    if (raiz != NULL) {
        inorder(raiz->esq);
        printf("%d ", raiz->data);
        inorder(raiz->dir);
    }
}
 
void inserir(arv** rz, int key) {
    arv* raiz = *rz;

    if (raiz == NULL) {
        arv* temp;
        temp = (arv*)malloc(sizeof(arv));
        temp->data = key;
        temp->esq = NULL;
        temp->dir = NULL;
        *rz = temp;
        return;
    }

    arv* atual = raiz;
    arv* prev  = NULL;

    while(atual != NULL) {
        prev = atual;
        if(atual->data > key) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (prev->data > key) {
        prev->esq       = (arv*)malloc(sizeof(arv));
        prev->esq->data = key;
        prev->esq->esq  = NULL;
        prev->esq->dir  = NULL;
    }
    else {
        prev->dir       = (arv*)malloc(sizeof(arv));
        prev->dir->data = key;
        prev->dir->esq  = NULL;
        prev->dir->dir  = NULL;
    }
}
 
arv* deletar(arv* raiz, int key) {
    arv* atual = raiz;
    arv* anterior = NULL;
 
    while (atual != NULL && atual->data != key) {
        anterior = atual;
        if (key < atual->data)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
 
    if (atual == NULL) {
        return raiz;
    }
 
    if (atual->esq == NULL || atual->dir == NULL) {
        arv* novo;
 
        if (atual->esq == NULL)
            novo = atual->dir;
        else
            novo = atual->esq;
 
        if (anterior == NULL)
            return novo;
 
        if (atual == anterior->esq)
            anterior->esq = novo;
        else
            anterior->dir = novo;
 
        free(atual);
    }
    else {
        arv* p = NULL;
        arv* temp;

        temp = atual->dir;
        while (temp->esq != NULL) {
            p = temp;
            temp = temp->esq;
        }

        if (p != NULL)
            p->esq = temp->dir;
        else
            atual->dir = temp->dir;
 
        atual->data = temp->data;
        free(temp);
    }
    return raiz;
}

int buscar(arv* tree, int val) {
    arv* atual = tree;

    while(atual != NULL && atual->data != val) {
        if(atual->data > val) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if(atual != NULL) {
        return 1;
    }

    return 0;
}

int main() {
    arv* root = NULL;

    srand(time(NULL));

    int* arr = (int*)malloc(sizeof(int) * 100000);

    for(int i = 0; i < 100000; i++) {
        arr[i] = rand() % 100000;
        inserir(&root, arr[i]);
    }

    for(int i = 0; i < 100000; i++) {
        if(i % 1161 != 0)
            root = deletar(root, arr[i]);
    }

    emOrdem(root);
    free(arr);
    return 0;
}
