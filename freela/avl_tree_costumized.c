#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b)       (a > b ? a : b)
#define NUMERO_COLUNAS  10

typedef struct {
    char* dados[NUMERO_COLUNAS];
} avl_info;

typedef struct avl_tree {
    avl_info dado;
    struct avl_tree* esq;
    struct avl_tree* dir;
    int altura;
} avl_tree;

int eh_float(char* A) {
	return strchr(A, '.') != NULL;
}

int eh_numero(char* A) {
    for(int i = 0; A[i] != 0; i++) {
        if(!isdigit(A[i])) {
            return 0;
        }
    }

    return 1;
}

// retorna true se A > B
int comp(char* A, char* B) {
	if(eh_float(A)) {
		return atof(A) >= atof(B);
	} else if(eh_numero(A)) {
        return atoi(A) >= atoi(B);
    } else {
        return strcmp(A, B) >= 0;
    }
}

avl_tree* criar_no(avl_info dado) {
    avl_tree* aux   = (avl_tree*)malloc(sizeof(avl_tree));
    aux->esq        = NULL;
    aux->dir        = NULL;
    aux->dado       = dado;
    aux->altura     = 0;
    return aux;
}

int altura(avl_tree* raiz) {
    if(raiz == NULL)
        return -1;
    return max(altura(raiz->dir), altura(raiz->esq)) + 1;
}

avl_tree* rotacao_dir(avl_tree* raiz) {
    avl_tree* aux   = raiz->esq;
    raiz->esq  = aux->dir;
    aux->dir   = raiz;

    raiz->altura  = altura(raiz);
    aux->altura   = altura(aux);
    return aux;
}

avl_tree* rotacao_esq(avl_tree* raiz) {
    avl_tree* aux   = raiz->dir;
    raiz->dir  = aux->esq;
    aux->esq   = raiz;

    raiz->altura  = altura(raiz);
    aux->altura   = altura(aux);
    return aux;
}

int balanceada(avl_tree* esq, avl_tree* dir) {
    return abs(altura(esq) - altura(dir)) < 2;
}

avl_tree* inserir(avl_tree* root, avl_info dado, int idx) {
    if(root == NULL) {
        return criar_no(dado);
    }

    if(comp(root->dado.dados[idx], dado.dados[idx])) {
        // após uma rotação a subárvore terá uma nova raiz.
        // portanto se a subarvore root->esq rotaciona
        // root precisa atualizar root->esq pra apontar pra
        // um novo nó (a nova raiz da subarvore apontada por ele)
        root->esq = inserir(root->esq, dado, idx);
        if(!balanceada(root->esq, root->dir)) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à esquerda
            root = rotacao_dir(root);
        }
    } else if(!comp(root->dado.dados[idx], dado.dados[idx])) {
        root->dir = inserir(root->dir, dado, idx);

        if(!balanceada(root->esq, root->dir)) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à direita
            root = rotacao_esq(root);
        }
    }

    // atualizo a altura e retorno
    root->altura = altura(root);
    return root;
}   

void remover(avl_tree** arv, int dado) {

}

void printar_linha(avl_info info) {
    for(int i = 0; i < NUMERO_COLUNAS; i++) {
        if(i+1 < NUMERO_COLUNAS)
            printf("%s,", info.dados[i]);
        else
            printf("%s", info.dados[i]);
    }

    printf("\n");
}

void percorrer(avl_tree* root, int idx) {
    if(root == NULL) return;
    percorrer(root->esq, idx);
    printar_linha(root->dado);
    percorrer(root->dir, idx);
}   

void tirar_newline(char* str) {
    if(str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = 0;
    }
}

void parsear(char str[100], avl_info* info) {
    int col = 0, idx = 0;

    for(int i = 0; str[i] != 0 && str[i] != '\r'; i++) {
        if(str[i] == ',') {
            info->dados[col] = (char*)malloc(sizeof(char) * 100);
            col++;
        }
    }

    info->dados[col] = (char*)malloc(sizeof(char) * 100);
    col = 0;

    for(int i = 0; str[i] != 0 && str[i] != '\r'; i++) {
        if(str[i] != ',') {
            info->dados[col][idx] = str[i];
            idx++;
        } else {
            info->dados[col][idx] = 0;
            col++;
            idx = 0;
        }
    }

    info->dados[col][idx] = 0;
}

void load_file(avl_tree** t, char* filename, int idx) {
    FILE* fp = fopen(filename, "r");
    char buf[100];
    int cnt = 0;
    // LEIO CADA LINHA DA TABELA VINHO.CSV E INSERO NA ÁRVORE AVL
    while(fgets(buf, 100, fp) != NULL) {
        avl_info info;
        parsear(buf, &info);
        (*t) = inserir(*t, info, idx);
    }

    fclose(fp);
}

int show_col(avl_tree* root, int idx) {
    if(root == NULL) {
        return 0;
    }

    show_col(root->esq, idx);
    printf("%s\n", root->dado.dados[idx]);
    show_col(root->dir, idx);
	return 1;
}

void filter_data(avl_tree* root, int idx, char* value) {
    if(root == NULL) {
        return;
    }

    if(comp(root->dado.dados[idx], value)) {
        if(strcmp(root->dado.dados[idx], value) == 0) {
            printar_linha(root->dado);
        }

        filter_data(root->esq, idx, value);
    } else {
        filter_data(root->dir, idx, value);
    }
}

int main() {
    avl_tree* arv = NULL;

    load_file(&arv, "teste.csv", 0);

	filter_data(arv, 0, "01-06-2010");
	
    //show_col(arv, 0); // PRINTAR A COLUNA DE INDICE 0 EM ORDEM CRESCENTE.

    //percorrer(arv, 0);
    return 0;
}
