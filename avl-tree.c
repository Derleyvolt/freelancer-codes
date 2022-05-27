#include <stdio.h>
#include <stdlib.h>

// https://gist.github.com/Harish-R/097688ac7f48bcbadfa5

typedef struct Arv {
    int dado;
    struct Arv* esq;
    struct Arv* dir;
    int altura;
} Arv;

Arv* criar_no(int dado) {
    Arv* aux    = (Arv*)malloc(sizeof(Arv));
    aux->esq    = NULL;
    aux->dir    = NULL;
    aux->dado   = dado;
    aux->altura = 0;
    return aux;
}

/// 50236
int altura(Arv* raiz) {
    if(raiz == NULL)
        return 0;
    return max(altura(raiz->dir), altura(raiz->esq)) + 1;
}

void rotacao_direita(Arv* raiz) {
    Arv* esq_raiz = raiz->esq;
    Arv* dir_raiz = raiz->dir;
    raiz->esq     = dir_raiz->dir;
    esq_raiz->dir = raiz;
    raiz->altura = altura(raiz);
}

void rotacao_esquerda(Arv* raiz) {
    
}

void inserir(Arv** arv, int dado) {
    Arv* root = *arv;
    if(root == NULL) {
        (*arv) = criar_no(dado);
        return;
    }

    if(root->dado > dado) {
        return inserir(&root->esq, dado);
    } else if(root->dado < dado) {
        return inserir(&root->dir, dado);
    }
}   

int main() {

    return 0;
}
