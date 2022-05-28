#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

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

int altura(Arv* raiz) {
    if(raiz == NULL)
        return -1;
    return max(altura(raiz->dir), altura(raiz->esq)) + 1;
}

Arv* rotacao_dir(Arv* raiz) {
    Arv* aux   = raiz->esq;
    raiz->esq  = aux->dir;
    aux->dir   = raiz;

    raiz->altura  = altura(raiz);
    aux->altura   = altura(aux);
    return aux;
}

Arv* rotacao_esq(Arv* raiz) {
    Arv* aux   = raiz->dir;
    raiz->dir  = aux->esq;
    aux->esq   = raiz;

    raiz->altura  = altura(raiz);
    aux->altura   = altura(aux);
    return aux;
}

Arv* inserir(Arv** arv, int dado) {
    Arv* root = *arv;
    if(root == NULL) {
        (*arv) = criar_no(dado);
        return (*arv);
    }

    if(root->dado > dado) {
        // após uma rotação a subárvore terá uma nova raiz.
        // portanto se a subarvore root->esq rotaciona
        // root precisa atualizar root->esq pra apontar pra
        // um novo nó (a nova raiz da subarvore apontada por ele)
        root->esq = inserir(&root->esq, dado);
        if(abs(altura(root->esq) - altura(root->dir)) >= 2) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à esquerda
            root = rotacao_dir(root);
        }
    } else if(root->dado < dado) {
        root->dir = inserir(&root->dir, dado);

        if(abs(altura(root->esq) - altura(root->dir)) >= 2) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à direita
            root = rotacao_esq(root);
        }
    }

    // atualizo a altura e retorno
    root->altura = altura(root);
    return root;
}   

void remover(Arv** arv, int dado) {
    
}

void percorrer(Arv* root) {
    if(root == NULL) return;
    percorrer(root->esq);
    printf("%d\n", root->dado);
    percorrer(root->dir);
}   

int main() {
    Arv* arv = NULL;
    for(int i = 0; i < 200; i++) {
        arv = inserir(&arv, i+1);
    }

    percorrer(arv);
    return 0;
}
