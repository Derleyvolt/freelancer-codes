#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    int valor;
    struct list *prox;
} TList;

void percorrer(TList* list) {
    if(list == NULL)
        return;
    printf("%d ", list->valor);
    percorrer(list->prox);
}

TList* deletar_elemento(TList* list, int elemento) {
	if(list == NULL)
		return NULL;
	TList* t = list;
	if(list->valor == elemento) {
		t = list->prox;
		free(list);
		return t;
	}
	
	while(list != NULL) {
		if(list->valor == elemento) {
			t = list->prox;
			free(list);
			return t;
		}
		
		list = list->prox;
	}
	
	return t;
}

int pegar_ultimo_elemento(TList** list) {
    if((*list) == NULL)
        return -1;
    TList* aux = (*list), *temp = (*list);
    while(aux->prox != NULL) {
        temp = aux;       // antigo
        aux  = aux->prox; // atual
    }

    int val;
    if(temp == aux) {
        val = (*list)->valor;
        free((*list));
        (*list) = NULL;
        return val;
    } else {
        val = aux->valor;
        temp->prox = NULL;
        free(aux);
        return val;
    }
}

int buscar_valor(TList* list, int elemento) {
	if(list == NULL)
		return -1;
	int pos = 0;
	while(list != NULL) {
		if(list->valor == elemento) {
			return pos;
		}

		pos++;

		list = list->prox;
	}

	return -1;
}

// 0 indexado
TList* deletar_elemento_posicao(TList* list, int pos) {
	if(list == NULL)
		return NULL;

	TList* t = list, *ant;

	while(pos > 0 && list != NULL) {
		ant = list;
		list = list->prox;
		pos--;
	}

	if(list == NULL)
		return t;

	if(t == list) {
		t = list->prox;
		free(list);
		return t;
	} else {
		ant->prox = list->prox;
		free(list);
		return t;
	}
}

// troca a por b
int trocar_valor(TList* list, int a, int b) {
	if(buscar_valor(list, b) >= 0 || buscar_valor(list, a) < 0) {
		return 0;
	}

	while(1) {
		if(list->valor == a) {
			list->valor = b;
			return 1;
		}
		
		list = list->prox;
	}
}

void adicionar(TList** list, int val) {
    if((*list) == NULL) {
        (*list) = (TList*)malloc(sizeof(TList));
        (*list)->valor = val;
        (*list)->prox  = NULL;
    } else {
        adicionar(&(*list)->prox, val);
    }
}

int adicionar_posicao(TList** list, int val, int pos) {
    if((*list) == NULL && pos == 0) {
        (*list) = (TList*)malloc(sizeof(TList));
        (*list)->valor = val;
        (*list)->prox  = NULL;
        return 1;
    } else if(pos == 0) {
        TList* aux = (TList*)malloc(sizeof(TList));
        aux->valor = val;
        aux->prox  = (*list)->prox;

        (*list)->prox = aux;

        int temp       = aux->valor;
        aux->valor     = (*list)->valor;
        (*list)->valor = temp;

        return 1;
    } else if((*list) == NULL) {
        return 0;
    } else {
        return adicionar_posicao(&(*list)->prox, val, pos-1);
    }
}

void Enter() {
	getchar();
	printf("Aperte Enter\n");
	getchar();
}

void menu() {
	system("clear");
	printf("1 - Inserir elemento\n");
	printf("2 - Remocao de determinado valor\n");
	printf("3 - Remocao de um elemento em determinada posicao\n");
	printf("4 - Altarecao de um valor por outro\n");
	printf("5 - Buscar determinado elemento na lista\n");
	printf("6 - Exibir os elementos da lista\n");
	printf("7 - Sair\n");
}

int main() {
    TList* list = NULL;
	int aux, b;

	menu();

	while(1) {
		char c = getchar();
		switch(c) {
			case '1': {
				printf("Digite o elemento a ser inserido\n");
				scanf("%d", &aux);
				if(buscar_valor(list, aux) >= 0) {
					printf("O elemento ja existe na lista\n");
					Enter();
					menu();
					break;
				}

				adicionar(&list, aux);
				printf("Elemento adicionado com sucesso\n");
				Enter();
				menu();
				break;
			}

			case '2': {
				printf("Digite o elemento a ser removido\n");
				scanf("%d", &aux);
				if(buscar_valor(list, aux) < 0) {
					printf("O elemento nao existe na lista\n");
					Enter();
					menu();
					break;
				}

				list = deletar_elemento(list, aux);

				printf("O elemento foi deletado com sucesso\n");
				Enter();
				menu();
				break;
			}

			case '3': {
				printf("Digite a posicao do elemento a ser removido\n");
				scanf("%d", &aux);

				list = deletar_elemento_posicao(list, aux);

				printf("O elemento foi deletado com sucesso\n");
				Enter();
				menu();
				break;
			}

			case '4': {
				printf("Digite 2 valores: o valor a e o b, a sera alterado para b\n");
				scanf("%d%d", &aux, &b);
				if(trocar_valor(list, aux, b) == 0) {
					printf("Ou o valor a nao existe na lista ou o valor b já existe no vetor\n");
					Enter();
					menu();
					break;
				}

				printf("Elemento trocado com sucesso\n");
				Enter();
				menu();
				break;
			}

			case '5': {
				printf("Digite o elemento a ser buscado na lista\n");
				scanf("%d", &aux);
				if(buscar_valor(list, aux) >= 0) {
					printf("O elemento existe na lista\n");
					Enter();
					menu();
					break;
				} else {
					printf("O elemento nao existe na lista\n");
					Enter();
					menu();
				}
				break;
			}

			case '6': {
				printf("Lista dos elementos\n\n");
				percorrer(list);
				printf("\n");
				Enter();
				menu();
				break;
			}

			case '7': {
				return 0;
				break;
			}
		}
	}

    return 0;
}
