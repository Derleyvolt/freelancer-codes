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

    raiz->altura = altura(raiz);
    aux->altura  = altura(aux);
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

Arv* rotacao_esq_dir(Arv* raiz) {
    raiz->esq = rotacao_esq(raiz->esq);
    //Arv* aux = rotacao_esq(raiz->esq);
    return rotacao_dir(raiz);
}

Arv* rotacao_dir_esq(Arv* raiz) {
    raiz->dir = rotacao_dir(raiz->dir);
    //Arv* aux = rotacao_dir(raiz->dir);
    return rotacao_esq(raiz);
}

int balanceamento(Arv* root) {
    if(root == NULL)
        return 0;
    return altura(root->esq) - altura(root->dir);
}

int obter_altura(Arv* raiz) {
    if(raiz == NULL) {
        return 0;
    }

    return raiz->altura;
}

Arv* encontrar_min(Arv* root) {
    if(root == NULL) {
        return NULL;
    }

    if(root->esq == NULL) {
        return root;
    }

    return encontrar_min(root->esq);
}

Arv* inserir(Arv* root, int dado) {
    if(root == NULL) {
        return criar_no(dado);
    }

    if(root->dado > dado) {
        // após uma rotação a subárvore terá uma nova raiz.
        // portanto se a subarvore root->esq rotaciona
        // root precisa atualizar root->esq pra apontar pra
        // um novo nó (a nova raiz da subarvore apontada por ele)
        root->esq = inserir(root->esq, dado);

        if(abs(balanceamento(root)) >= 2) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à esquerda
            if(balanceamento(root->esq) == -1) {
                root = rotacao_esq_dir(root);
            } else {
                root = rotacao_dir(root);
            }
        }
    } else if(root->dado < dado) {
        root->dir = inserir(root->dir, dado);

        if(abs(balanceamento(root)) >= 2) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à direita
            if(balanceamento(root->dir) == 1) {
                root = rotacao_dir_esq(root);
            } else {
                root = rotacao_esq(root);
            }
        }
    }
    
    // atualizo a altura e retorno
    root->altura = max(obter_altura(root->dir), obter_altura(root->esq)) + 1;
    return root;
}   

Arv* remover(Arv** arv, int dado) {
    Arv* root = *arv;
    if(root == NULL) {
        return NULL;
    }

    if(root->dado > dado) {
        root->esq = remover(&root->esq, dado);
        if(abs(balanceamento(root)) >= 2) {
            // sei que removi alguém da minha direita 
            if(balanceamento(root->dir) == 1) {
                root = rotacao_dir_esq(root);
            } else {
                root = rotacao_esq(root);
            }
        }
    } else if(root->dado < dado) {
        root->dir = remover(&root->dir, dado);
        if(abs(balanceamento(root)) >= 2) {
            // sei que removi alguém da minha direita
            if(balanceamento(root->esq) == -1) {
                root = rotacao_esq_dir(root);
            } else {
                root = rotacao_dir(root);
            }
        }
    } else {
        if(root->esq == NULL || root->dir == NULL) {
            if(root->esq == NULL) {
                Arv* aux = root->dir;
                free(root);
                return aux;
            }

            if(root->dir == NULL) {
                Arv* aux = root->esq;
                free(root);
                return aux;
            }
        }

        Arv* aux   = encontrar_min(root->dir);
        root->dado = aux->dado;
        root->dir  = remover(&root->dir, root->dado);
    }

    root->altura = max(obter_altura(root->dir), obter_altura(root->esq)) + 1;
    return root;
}

void percorrer(Arv* root) {
    if(root == NULL) return;
    percorrer(root->esq);
    printf("%d\n", root->dado);
    percorrer(root->dir);
}   

void percorrer_in_order(Arv* root) {
    if(root == NULL) return;
    printf("%d\n", root->dado);
    percorrer_in_order(root->esq);
    percorrer_in_order(root->dir);
}

int main() {
    Arv* arv = NULL;

    for(int i = 0; i < 3000; i++) {
        arv = inserir(arv, i+1);
    }

    for(int i = 1; i < 3000; i++) {
        if(i != 200)
            arv = remover(&arv, i+1);
    }

    printf("Altura: %d\n\n", obter_altura(arv));
    percorrer_in_order(arv);
    return 0;
}
