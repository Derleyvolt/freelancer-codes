#include <stdio.h>
#include <stdlib.h>

typedef struct singly_linked_list {
    int val;
    struct singly_linked_list* prox;
} singly_linked_list;

singly_linked_list* create_node(int val) {
    singly_linked_list* node = (singly_linked_list*)malloc(sizeof(singly_linked_list));
    node->val    = val;
    node->prox   = NULL;
    return node;
}

void push_front(singly_linked_list** list, int val) {
    if(*list == NULL) {
        (*list) = create_node(val);
    } else {
        singly_linked_list* aux   = create_node(val);
        int a         = aux->val;
        aux->val      = (*list)->val;
        (*list)->val = a;

        aux->prox      = (*list)->prox;
        (*list)->prox = aux;
    }
}

void push_back(singly_linked_list** list, int val) {
    if((*list) == NULL) {
        (*list) = create_node(val);
        return;
    }

    push_back(&(*list)->prox, val);
}

int empty(singly_linked_list* list) {
    return list == NULL;    
}

int front(singly_linked_list* list) {
    return list->val;
}

void pop_front(singly_linked_list** list) {
    if((*list) == NULL)
        return;
    singly_linked_list* tmp = (*list);
    (*list) = (*list)->prox;
    free(tmp);
}

int pos(singly_linked_list* list, int i) {
    if(i == 0) {
        return list->val;
    }

    return pos(list->prox, i-1);
}

singly_linked_list* erase(singly_linked_list** list, int val) {
    if(*list == NULL) {
        return NULL;
    }

    singly_linked_list* aux = *list;

    if(aux->val == val) {
        if(aux->prox != NULL) {
            aux->val     = aux->prox->val;
            singly_linked_list* temp = aux->prox;
            aux->prox    = aux->prox->prox;
            free(temp);
            return aux;
        } else {
            // este é o último elemento da list
            free(aux);
            return NULL;
        }
    }

    aux->prox = erase(&aux->prox, val);
    return aux;
}

void traverse(singly_linked_list* list) {
    if(list == NULL)
        return;
    printf("%d ", list->val);
    traverse(list->prox);
}

// O(n^2)
void sort(singly_linked_list* list) {
    if(list == NULL) {
        return;
    }

    for(singly_linked_list* i = list; i != NULL; i = i->prox) {
        for(singly_linked_list* j = i->prox; j != NULL; j = j->prox) {
            if(j->val < i->val) {
                int aux = i->val;
                i->val  = j->val;
                j->val  = aux;
            }
        }
    }
}

singly_linked_list* search(singly_linked_list* ls, int val) {
    if(ls == NULL) {
        return NULL;
    }

    if(ls->val == val) {
        return ls;
    }

    return search(ls->prox, val);
}

int length(singly_linked_list* ls) {
    if(ls == NULL) {
        return 0;
    }

    return 1 + length(ls->prox);
}

int main() {
    singly_linked_list* list = NULL;

    for(int i = 10; i >= 0; i--) {
        push_back(&list, i);
    }

    list = erase(&list, 8);

    push_front(&list, -5);
    
    traverse(list);
    return 0;
}
