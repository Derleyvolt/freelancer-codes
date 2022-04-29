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

void push_front(s_list** lista, int val) {
    if(*lista == NULL) {
        (*lista) = create_node(val);
    } else {
        s_list* aux   = create_node(val);
        int a         = aux->val;
        aux->val      = (*lista)->val;
        (*lista)->val = a;

        aux->prox      = (*lista)->prox;
        (*lista)->prox = aux;
    }
}

void push_back(s_list** list, int val) {
    if((*list) == NULL) {
        (*list) = create_node(val);
        return;
    }

    push_back(&(*list)->prox, val);
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

s_list* erase(s_list** lista, int val) {
    if(*lista == NULL) {
        return NULL;
    }

    s_list* aux = *lista;

    if(aux->val == val) {
        if(aux->prox != NULL) {
            aux->val     = aux->prox->val;
            s_list* temp = aux->prox;
            aux->prox    = aux->prox->prox;
            free(temp);
            return aux;
        } else {
            // este é o último elemento da lista
            free(aux);
            return NULL;
        }
    }

    aux->prox = erase(&aux->prox, e);
    return aux;
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

s_list* buscar(s_list* ls, int val) {
    if(ls == NULL) {
        return NULL;
    }
    if(ls->val == val) {
        return ls;
    }
    return buscar(ls->prox, val);
}

int main() {
    s_list* lista = NULL;

    for(int i = 10; i >= 0; i--) {
        push_back(&lista, i);
    }

    lista = erase(&lista, 8);

    push_front(&lista, -5);
    
    traverse(lista);
    return 0;
}
