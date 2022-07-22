#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stCarta{
	int nape;
	int numero;
	struct stCarta *proximo;
}tCarta;

//A, 2, 3, 4, 5, 6, 7, 8, 9, 10, Q, J, K

char vetorNapes[] = { 3,4,5,6 };   // coração, ouro, paus e espadas
int totalBaralho  = 106;            // total de cartas no baralho
tCarta *baralho   = NULL;          // início da pilha de cartas do baralho
tCarta *mesa      = NULL;          // início da pilha de cartas do baralho
tCarta *jogador1  = NULL;          // início da pilha de cartas do jogador
tCarta *jogador2  = NULL;          // início da pilha de cartas da banca
tCarta *jogador3  = NULL;          // início da pilha de cartas da banca
tCarta *jogador4  = NULL;          // início da pilha de cartas da banca

tCarta* criar_elemento(int nape, int numero) {
	tCarta* ret  = (tCarta*)malloc(sizeof(tCarta));
	ret->nape    = nape;
	ret->numero  = numero;
	ret->proximo = NULL;
	return ret;
}

void inserir_pilha(tCarta** p, int nape, int numero) {
	tCarta* aux = *p;
	if(aux == NULL) {
		*p = criar_elemento(nape, numero);
		return;
	}

	inserir_pilha(&(*p)->proximo, nape, numero);
}

void criarBaralho() {
	for(int j = 0; j < 4; j++) {
		for(int i = 0; i < 13; i++) {
			inserir_pilha(&baralho, vetorNapes[j], i+1); 
			inserir_pilha(&baralho, vetorNapes[j], i+1); 
		}
	}
	// inserindo os 2 coringas
	inserir_pilha(&baralho, 13, 0);
	inserir_pilha(&baralho, 13, 0);
}

tCarta *removerBaralho (int pos) {
	tCarta* aux = baralho;
	if(pos == 0) {
		baralho = baralho->proximo;	
		return aux;
	}

	if(pos < 0) {
		return NULL;
	}

	tCarta* ant = baralho;
	while(aux != NULL && pos != 0) {
		ant = aux;
		aux = aux->proximo;
		pos--;
	}

	if(aux == NULL) {
		return NULL;
	}

	ant->proximo = aux->proximo;
	return aux;
}

void embaralharBaralho () {
	tCarta* aux = NULL;

	int vet[106];

	// cria um vetor de posições, pra pegar um elemento aleatório desse vetor e usar como
	// posicão
	for(int i = 0; i < 106; i++) {
		vet[i] = i;
	}

	while(totalBaralho > 0) {
		int pos = rand() % totalBaralho;
		tCarta* e = removerBaralho(pos);

		inserir_pilha(&aux, e->nape, e->numero);

		free(e);

		// swap, jogo a posição pêga e jogo pro final pra não ser mais usada.
		int temp 			 = vet[totalBaralho-1];
		vet[totalBaralho-1]  = vet[pos];
		vet[pos] 			 = temp;

		totalBaralho--;
	}

	baralho = aux;
	totalBaralho = 106;
}

void distribuirBaralho () {
	for(int i = 0; i < totalBaralho; i++) {
		// joga uma carta pro jogador 1, pro jogador 2 pro jogador 3 ou pro jogador 4
		if(i % 4 == 0) {
			inserir_pilha(&jogador1, baralho->nape, baralho->numero);
		} else if(i % 4 == 1) {
			inserir_pilha(&jogador2, baralho->nape, baralho->numero);
		} else if(i % 4 == 2) {
			inserir_pilha(&jogador3, baralho->nape, baralho->numero);
		} else {
			inserir_pilha(&jogador4, baralho->nape, baralho->numero);
		}

		free(removerBaralho(0));
	}
}

void moveLista (tCarta* cabeca1, tCarta* cabeca2) {
	tCarta* aux = cabeca1;
	while(aux->proximo != NULL) {
		aux = aux->proximo;	
	}

	aux->proximo = cabeca2;
}

void imprimirLista (tCarta *cabeca) {
	tCarta* aux = cabeca;
	printf("\n");
	while(aux != NULL) {
		switch (aux->numero)
		{
		case 0: {
			printf(" Naipe: %d, Carta: Coringa ", aux->nape);
			break;
		}

		case 1: {
			printf(" Naipe: %d, Carta: A ", aux->nape);
			break;
		}
		
		case 11: {
			printf(" Naipe: %d, Carta: Q ", aux->nape);
			break;
		}

		case 12: {
			printf(" Naipe: %d, Carta: J ", aux->nape);
			break;
		}

		case 13: {
			printf(" Naipe: %d, Carta: K ", aux->nape);
			break;
		}

		default: {
			printf(" Naipe: %d, Carta: %d ", aux->nape, aux->numero);
			break;
		}

		}

		aux = aux->proximo;
		printf("\n");
	}
}

int main (int argc, char* argv[]){
	char op;
	int vez=1;
	int contador=1;
	tCarta *removida;
	srand(time(NULL));
	criarBaralho();
	embaralharBaralho();
	distribuirBaralho();
		while(jogador1!=NULL && jogador2!=NULL && jogador3!=NULL && jogador4!=NULL) {
			if(vez==1){
				printf("Jogador 1");
				imprimirLista(jogador1);
				removida=jogador1;
				jogador1=jogador1 -> proximo;
				removida -> proximo=mesa;
				mesa=removida;
				printf("mesa(%d)", contador);
				imprimirLista(mesa);
				if(removida->numero==contador || removida->numero==0){
					moveLista(jogador1, mesa);
					mesa=NULL;
					printf("jogador1=");
					imprimirLista(jogador1);
					printf("mesa(%d)=", contador);
					imprimirLista(mesa);
					contador=0;	
				}
				vez=2;
			} else if(vez==2) {
				printf("Jogador 2 =");
				imprimirLista(jogador2);
				removida=jogador2;
				jogador2=jogador2 -> proximo;
				removida -> proximo=mesa;
				mesa=removida;
				printf("mesa(%d)=", contador);
				imprimirLista(mesa);
				if(removida->numero==contador || removida->numero==0){
					moveLista(jogador2, mesa);
					mesa=NULL;
					printf("jogador2=");
					imprimirLista(jogador2);
					printf("mesa(%d)=", contador);
					imprimirLista(mesa);
					contador=0;
				}
				vez=3;			
			} else if(vez == 3) {
				printf("Jogador 3 =");
				imprimirLista(jogador3);
				removida=jogador3;
				jogador3=jogador3 -> proximo;
				removida -> proximo=mesa;
				mesa=removida;
				printf("mesa(%d)=", contador);
				imprimirLista(mesa);
				if(removida->numero==contador || removida->numero==0){
					moveLista(jogador3, mesa);
					mesa=NULL;
					printf("jogador3=");
					imprimirLista(jogador3);
					printf("mesa(%d)=", contador);
					imprimirLista(mesa);
					contador=0;
				}
				vez=4;	
			} else {
				printf("Jogador 4 =");
				imprimirLista(jogador4);
				removida=jogador4;
				jogador4=jogador4 -> proximo;
				removida -> proximo=mesa;
				mesa=removida;
				printf("mesa(%d)=", contador);
				imprimirLista(mesa);
				if(removida->numero==contador || removida->numero==0){
					moveLista(jogador4, mesa);
					mesa=NULL;
					printf("jogador4=");
					imprimirLista(jogador4);
					printf("mesa(%d)=", contador);
					imprimirLista(mesa);
					contador=0;
				}
				vez=1;
			}

			contador++;
			if(contador>13){
				contador=1;
			}
			printf("pressione enter");
			getchar();
	}
	
	if(jogador1 == NULL) {
		printf("jogador1 venceu!");
	} else if(jogador2 == NULL) {
		printf("jogador2 venceu!");
	} else if(jogador3 == NULL) {
		printf("jogador3 venceu!");
	} else {
		printf("jogador4 venceu!");
	}

	return 0;
}
