#include <stdio.h>
#include <stdlib.h>

typedef struct s_list {
    int val;
    struct s_list* prox;
} s_list;

s_list* create_node(int val) {
    s_list* node = (s_list*)malloc(sizeof(s_list));
    node->val    = val;
    node->prox   = NULL;
    return node;
}

void insert(s_list** list, int val) {
    if((*list) == NULL) {
        (*list) = create_node(val);
        return;
    }

    insert(&(*list)->prox, val);
}

int empty(s_list* list) {
    return list == NULL;    
}

int front(s_list* list) {
    return list->val;
}

// deixa o list nula quando eu apago o último elemento
void pop_front(s_list** list) {
    if((*list) == NULL)
        return;
    s_list* tmp = (*list);
    (*list) = (*list)->prox;
    free(tmp);
}

// essa função não faz checagem quanto ao tamanho da lista
// isso vc precisa fazer por fora, quando chamar a função
int pos(s_list* list, int i) {
    if(i == 0) {
        return list->val;
    }
    return pos(list->prox, i-1);
}

void traverse(s_list* list) {
    if(list == NULL)
        return;
    printf("%d ", list->val);
    traverse(list->prox);
}

// O(n^2)
void sort(s_list* list) {
    if(list == NULL) {
        return;
    }

    for(s_list* i = list; i != NULL; i = i->prox) {
        for(s_list* j = i->prox; j != NULL; j = j->prox) {
            if(j->val < i->val) {
                int aux = i->val;
                i->val  = j->val;
                j->val  = aux;
            }
        }
    }
}

int main() {
    s_list* list = NULL;

    for(int i = 9; i >= 0; i--) {
        insert(&list, i+1);
    }

    sort(list);

    traverse(list);
    return 0;
}
