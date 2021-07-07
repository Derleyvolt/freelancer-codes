#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* left, *right;
} Node;

Node* criar_node(int val) {
    Node* no = (Node*)malloc(sizeof(Node));
    no->val  = val;
    no->left  = NULL;
    no->right  = NULL;
}

void inserir(Node** no, int val) {
    if((*no) == NULL) {
        (*no) = criar_node(val);
    } else {
        if(val > (*no)->val) {
            inserir(&(*no)->right, val);
        } else if(val < (*no)->val) {
            inserir(&(*no)->left, val);
        } else {
            return;
        }
    }
}

int buscar(Node* no, int val) {
    if(no == NULL)
        return -1;

    if(no->val == val)
        return 1;
    
    if(val > no->val)
        return buscar(no->right, val);
    else
        return buscar(no->left, val);
}

Node* apagar(Node* node, int val) {
	if(node == NULL)
		return NULL;
	if(node->val == val) {
		
	}
}

void percorrer(Node* node) {
    if(node == NULL)
		return;
	percorrer(node->left);
	printf("%d\n", node->val);
	percorrer(node->right);
}

Node* min_value(Node* node) {
    if(node == NULL)
        return NULL;
    while(node->left != NULL) {
        node = node->left;
    }

    return node;
}

Node* remove_node(Node* node, int val) {
    if(node == NULL)
        return NULL;
    if(node->val > val) {
        node->left = remove_node(node->left, val);
    } else if(node->val < val) {
        node->right = remove_node(node->right, val);
    } else {
        Node* temp;
        if(node->left == NULL) {
            // O nó não tem filho á esquerda
            temp = node->right;
            free(node);
            return temp;
        } else if(node->right == NULL) {
            // O nó não tem filho á direita
            temp = node->left;
            free(node);
            return temp;
        }

        // O nó tem dois filhos


        // quer o menor nó da subarvore à direita
        temp = min_value(node->right);
        // esse tal menor nó agora está na posição do cara deletado
        node->val = temp->val;

        // como esse tal menor nó foi puxado pra cima, a subarvore da qual
        // ele era root precisa ser corrigida pois ele foi deletado
        // daquela posicao..

        // o cara que será deletado dessa vez por ser o 
        // meu filho á direita, então preciso linkar o retorno
        // ao meu novo filho á direita
        node->right = remove_node(temp, temp->val);
    }

    return node;
}

int main() {
	Node* no = NULL;
	inserir(&no, 10);
	inserir(&no, 11);
	inserir(&no, 12);
	inserir(&no, 13);

    no = remove_node(no, 10);

    percorrer(no);
	return 0;  
}
