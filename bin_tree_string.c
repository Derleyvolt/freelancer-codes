#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (a > b ? a : b)

typedef struct BSTree {
    char str[50];
    struct BSTree* left, *right;
} Node;

int maior(const char a[50], const char b[50]) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    for(int i = 0; i < min(len_a, len_b); i++) {
        if(a[i] > b[i]) {
            return 1;
        } else if(a[i] < b[i]) {
            return 0;
        }
    }

    return len_a > len_b;
}

Node* criar_node(char str[50]) {
    Node* no = (Node*)malloc(sizeof(Node));
    strcpy(no->str, str);
    no->left   = NULL;
    no->right  = NULL;
}

void inserir(Node** no, char str[50]) {
    if((*no) == NULL) {
        (*no) = criar_node(str);
    } else {
        if(maior(str, (*no)->str)) {
            inserir(&(*no)->right, str);
        } else if(maior((*no)->str, str)) {
            inserir(&(*no)->left, str);
        } else {
            return;
        }
    }
}

int buscar(Node* no, char str[50]) {
    if(no == NULL)
        return -1;

    if(strcmp(no->str, str) == 0)
        return 1;
    
    if(maior(str, no->str))
        return buscar(no->right, str);
    else
        return buscar(no->left, str);
}

void percorrer(Node* node) {
    if(node == NULL)
		return;
	percorrer(node->left);
	printf("%s\n", node->str);
	percorrer(node->right);
}

int main() {
    Node* tree = NULL;

    inserir(&tree, "rato");
    inserir(&tree, "pato");
    inserir(&tree, "ratox");
    inserir(&tree, "ato");

    percorrer(tree);
    return 0;  
}
