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

int main() {
    s_list* list = NULL;

    for(int i = 0; i < 10; i++) {
        insert(&list, i+1);
    }

    printf("%d\n", pos(list, 0));

    //traverse(list);
    return 0;
}
