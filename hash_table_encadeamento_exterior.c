
#include <stdio.h>
#include <stdlib.h>
#include "lista.c"

// O TRATAMENTO DE COLISÕES É BASEADO NO MÉTODO DE ENCADEAMENTO EXTERIOR.

typedef struct Hash {
	s_list** base;

	int len;
} Hash;

void initialize_hash(Hash* h, int len) {
	h->base = (s_list**)malloc(sizeof(s_list*) * len);
	h->len  = len;
	for(int i = 0; i < len; i++) {
		h->base[i] = NULL;
	}
}	

int H(int k, int n) {
	return k % n;
}

void insert(Hash* h, int k) {
	int pos = H(k, h->len);
	if(h->base[pos] == NULL) {
		h->base[pos] = create_node(k);
	} else {
		push_back(&h->base[pos], k);
	}
}

int search(Hash* h, int k) {
	int pos = H(k, h->len);
	if(h->base[pos] != NULL) {
		s_list* aux = l_search(h->base[pos], k);
		return aux != NULL;
	} else {
		return 0;
	}
}

int main() {
    Hash hs;
    initialize_hash(&hs, 10);
    insert(&hs, 10);
    return 0;
}
