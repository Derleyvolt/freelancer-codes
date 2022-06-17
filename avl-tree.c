#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) (a > b ? a : b)

typedef struct Tree {
    int data;
    struct Tree* left;
    struct Tree* right;
    int height;
} Tree;

Tree* create_node(int data) {
    Tree* aux    = (Tree*)malloc(sizeof(Tree));
    aux->left    = NULL;
    aux->right   = NULL;
    aux->data    = data;
    aux->height  = 1;
    return aux;
}

int get_height(Tree* raiz) {
    if(raiz == NULL) {
        return 0;
    }

    return raiz->height;
}

Tree* right_rotation(Tree* raiz) {
    Tree* aux    = raiz->left;
    raiz->left   = aux->right;
    aux->right   = raiz;

    raiz->height = max(get_height(raiz->left), get_height(raiz->right))+1;
    aux->height  = max(get_height(aux->left), get_height(aux->right))+1;
    return aux;
}

Tree* left_rotation(Tree* raiz) {
    Tree* aux    = raiz->right;
    raiz->right  = aux->left;
    aux->left    = raiz;

    raiz->height = max(get_height(raiz->left), get_height(raiz->right))+1;
    aux->height  = max(get_height(aux->left), get_height(aux->right))+1;
    return aux;
}

Tree* left_right_rotation(Tree* raiz) {
    raiz->left = left_rotation(raiz->left);
    return right_rotation(raiz);
}

Tree* right_left_rotation(Tree* raiz) {
    raiz->right = right_rotation(raiz->right);
    return left_rotation(raiz);
}

int balanced(Tree* root) {
    if(root == NULL)
        return 0;
    return get_height(root->left) - get_height(root->right);
}

Tree* find_min(Tree* root) {
    if(root == NULL) {
        return NULL;
    }

    if(root->left == NULL) {
        return root;
    }

    return find_min(root->left);
}

Tree* insert(Tree* root, int data) {
    if(root == NULL) {
        return create_node(data);
    }

    if(root->data > data) {
        // após uma rotação a subárvore terá uma nova raiz.
        // portanto se a subarvore root->left rotaciona
        // root precisa atualizar root->left pra apontar pra
        // um novo nó (a nova raiz da subarvore apontada por ele)
        root->left = insert(root->left, data);

        if(abs(balanced(root)) >= 2) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à esquerda
            if(balanced(root->left) == -1) {
                root = left_right_rotation(root);
            } else {
                root = right_rotation(root);
            }
        }
    } else if(root->data < data) {
        root->right = insert(root->right, data);

        if(abs(balanced(root)) >= 2) {
            // o desbalanceamento com ctz aconteceu na subárvore
            // à direita
            if(balanced(root->right) == 1) {
                root = right_left_rotation(root);
            } else {
                root = left_rotation(root);
            }
        }
    }
    
    // atualizo a height e retorno
    root->height = max(get_height(root->right), get_height(root->left)) + 1;
    return root;
}   

Tree* remove_(Tree** arv, int data) {
    Tree* root = *arv;
    if(root == NULL) {
        return NULL;
    }

    if(root->data > data) {
        root->left = remove_(&root->left, data);
        if(abs(balanced(root)) >= 2) {
            // sei que removi alguém da minha esquerda 
            root = balanced(root->right) == 1 ? right_left_rotation(root) : left_rotation(root);
        }
    } else if(root->data < data) {
        root->right = remove_(&root->right, data);
        if(abs(balanced(root)) >= 2) {
            // sei que removi alguém da minha direita
            root = balanced(root->left) == -1 ? left_right_rotation(root) : right_rotation(root);
        }
    } else {
        if(root->left == NULL || root->right == NULL) {
            Tree* aux = root->left == NULL ? root->right : root->left;
            free(root);
            return aux;
        }

        Tree* aux   = find_min(root->right);
        root->data  = aux->data;
        root->right = remove_(&root->right, root->data);

        // essa checagem é necessária, pois eu removi alguém à minha
        if(abs(balanced(root)) >= 2) {
            root = balanced(root->left) == -1 ? left_right_rotation(root) : right_rotation(root);
        }
    }

    root->height = max(get_height(root->right), get_height(root->left)) + 1;
    return root;
}

void inOrder_traverse(Tree* root) {
    if(root == NULL) return;
    inOrder_traverse(root->left);
    printf("%d\n", root->data);
    inOrder_traverse(root->right);
}   

void preOrder_traverse(Tree* root) {
    if(root == NULL) return;
    preOrder_traverse(root->left);
    printf("%d\n", root->data);
    preOrder_traverse(root->right);
}

int is_not_balanced_tree(Tree* root) {
    if(root == NULL) {
        return 0;
    }

    if(abs(balanced(root)) >= 2) {
        return 1;
    }

    int a = is_not_balanced_tree(root->left);
    int b = is_not_balanced_tree(root->right);

    return a + b;
}

int main() {
    Tree* arv = NULL;

    srand(time(NULL));

    for(int i = 1; i <= 10000; i++) {
        arv = insert(arv, rand() % 50000);
    }

    for(int i = 1; i <= 10000; i++) {
        if(i % 2 != 0)
            arv = remove_(&arv, i);
    }

    preOrder_traverse(arv);
    printf("\n\nAltura: %d\n\n", get_height(arv));

    printf("\n\n%d\n", !is_not_balanced_tree(arv));
    return 0;
}
