#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    char val[30]; // '+', '*', '/', '-', numbers
    struct Tree* esq, *dir;
} No;

No* criar_no_tree(const char val[]) {
    No* aux = (No*)malloc(sizeof(No));
    strcpy(aux->val, val);
    aux->dir = NULL;
    aux->esq = NULL;
    return aux;
}

void inserir(No** ptr, const char val[]) {
    No* aux = (*ptr);
    if(aux == NULL) {
        (*ptr) = criar_no_tree(val);
        return;
    }

    if(val > aux->val) {
        inserir(&aux->dir, val);
    } else if(val < aux->val) {
        inserir(&aux->esq, val);
    } else {
        return;
    }
}

void percorrer(No* no) {
    if(no == NULL) {
        return;
    }

    percorrer(no->esq);
    printf("%d\n", no->val);
    percorrer(no->dir);
}

int avaliable(No* no) {
    if(no == NULL) {
        return 1;
    }

    printf("%s\n", no->val);

    if(no->val[0] >= '0' && no->val[0] <= '9') {
        return no->val[0]-'0';
    }

    if(no->val[0] == '+') {
        return avaliable(no->esq) + avaliable(no->dir);
    } else if(no->val[0] == '-') {
        return avaliable(no->esq) - avaliable(no->dir);
    } else if(no->val[0] == '*') {
        return avaliable(no->esq) * avaliable(no->dir);
    } else {
        return avaliable(no->esq) / avaliable(no->dir);
    }
}

int main() {
    No* no = NULL;

    // 3 + 5 * 8
    no           = criar_no_tree("+");
    no->esq      = criar_no_tree("3");
    no->dir      = criar_no_tree("*");
    no->dir->esq = criar_no_tree("5");
    no->dir->dir = criar_no_tree("8");

    // 3 * (2 + 5 * 4)
    // no           = criar_no_tree("*");
    // no->esq      = criar_no_tree("3");
    // no->dir      = criar_no_tree("+");
    // no->dir->esq = criar_no_tree("2");
    // no->dir->dir = criar_no_tree("*");
    // no->dir->dir->esq = criar_no_tree("5");
    // no->dir->dir->dir = criar_no_tree("4");

    int aux = avaliable(no);
    printf("%d\n", aux);

    return 0;
}
