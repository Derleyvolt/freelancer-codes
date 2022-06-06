#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct queue {
    int vet[MAXN];
    int head, tail, len;
} queue;

queue inicialize_queue() {
    queue q;
    q.head = 0; 
    q.tail = 0;
    q.len  = 0;
    return q;
}

void insert(queue* q, int x) {
    if(q->len >= MAXN) {
        return;
    }

    q->vet[q->tail] = x;
    q->len++;
    q->tail = (q->tail + 1) % MAXN;
}

void erase(queue* q) {
    if(q->len > 0) {
        q->head = (q->head + 1) % MAXN;
        q->len--;
    }
}

void traverse(queue* q) {
    int ptr = q->head;
    for(int i = 0; i < q->len; i++) {
        printf("%d ", q->vet[(ptr + i) % MAXN]);
    }
}

int front(queue* q) {
    return q->vet[q->head];
}

int main() {
    queue q;
    q = inicialize_queue();

    for(int i = 0; i < 10; i++) {
        insert(&q, i+1);
    }

    erase(&q);
    insert(&q, 100);

    traverse(&q);
    return 0;
}
