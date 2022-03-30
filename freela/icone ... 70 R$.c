#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 100

typedef struct Icone {
	short int **pixels;
	int tamanho;
} Icone;

Icone* icone_cria(int tam) {
	Icone* aux  = (Icone*)malloc(sizeof(Icone));

	if(aux == NULL) {
		return NULL;
	}

	aux->pixels = (short int**)malloc(sizeof(short int*) * tam);

	for(int i = 0; i < tam; i++) {
		aux->pixels[i] = (short int*)malloc(sizeof(short int) * tam);
	}

	aux->tamanho = tam;
	return aux;
}

void icone_libera_memoria(Icone *ic) {
	for(int i = 0; i < ic->tamanho; i++) {
		free(ic->pixels[i]);
	}

	free(ic->pixels);
}

void icone_atribui(Icone* ic, int i, int j, int v) {
	ic->pixels[i][j] = v;
}

int icone_acessa(Icone* ic, int i, int j) {
	return ic->pixels[i][j];
}

int icone_tam(Icone* ic) {
	return ic->tamanho;
}

void icone_preenche_aleatorio(Icone* ic) {
	int pixels_count = rand() % (ic->tamanho * ic->tamanho);
	while(pixels_count) {
		int i = rand() % ic->tamanho;
		int j = rand() % ic->tamanho;

		ic->pixels[i][j] = 1;
		pixels_count--;
	}
}

void icone_imprime(Icone* ic) {
	for(int i = 0; i < ic->tamanho; i++) {
		for(int j = 0; j < ic->tamanho; j++) {
			if(ic->pixels[i][j] == 1) {
				printf("%c", 219);
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

Icone* icone_copia(Icone* ic) {
	Icone* copy = icone_cria(ic->tamanho);

	for(int i = 0; i < copy->tamanho; i++) {
		for(int j = 0; j < copy->tamanho; j++) {
			copy->pixels[i][j] = ic->pixels[i][j];
		}
	}

	return copy;
}

Icone* icone_rotaciona(Icone* ic1) {
	//int **mat = (int**)malloc(sizeof(int) * ic1->tamanho * ic1->tamanho);
	Icone* aux = icone_cria(ic1->tamanho);
	for(int i = 0; i < ic1->tamanho; i++) {
		for(int j = 0; j < ic1->tamanho; j++) {
			aux->pixels[j][ic1->tamanho-1-i] = ic1->pixels[i][j];
		}
	}

	return aux;
}

Icone* reflexao_vertical(Icone* ic) {
	Icone* aux = icone_cria(ic->tamanho);

	for(int i = 0; i < ic->tamanho/2; i++) {
		for(int j = 0; j < ic->tamanho; j++) {
			aux->pixels[aux->tamanho-1-i][j] = ic->pixels[i][j];
		}
	}

	for(int i = ic->tamanho/2; i < ic->tamanho; i++) {
		for(int j = 0; j < ic->tamanho; j++) {
			aux->pixels[i-aux->tamanho/2][j] = ic->pixels[ic->tamanho-1-(i-ic->tamanho/2)][j];
		}
	}

	return aux;
}

Icone* reflexao_horizontal(Icone* ic) {
	Icone* aux = icone_cria(ic->tamanho);

	for(int i = 0; i < ic->tamanho; i++) {
		for(int j = 0; j < ic->tamanho/2; j++) {
			aux->pixels[i][aux->tamanho-1-j] = ic->pixels[i][j];
		}
	}

	for(int i = 0; i < ic->tamanho; i++) {
		for(int j = ic->tamanho/2; j < ic->tamanho; j++) {
			aux->pixels[i][j-ic->tamanho/2] = ic->pixels[i][ic->tamanho-1-j+ic->tamanho/2];
		}
	}

	return aux;
}

int eh_simetrico_horizontal(Icone* ic) {
	for(int i = 0; i < ic->tamanho; i++) {
		for(int j = 0; j < ic->tamanho/2; j++) {
			if(ic->pixels[i][j] != ic->pixels[i][ic->tamanho-1-j]) {
				return 0;
			}
		}
	}

	return 1;
}

int eh_simetrico_vertical(Icone* ic) {
	for(int i = 0; i < ic->tamanho/2; i++) {
		for(int j = 0; j < ic->tamanho; j++) {
			if(ic->pixels[i][j] != ic->pixels[ic->tamanho-1-i][j]) {
				return 0;
			}
		}
	}

	return 1;
}

void print_matrix(int mat[3][3]) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

Icone* criar_icone_opc() {
	printf("Digite o tamanho do icone: ");
	int len; scanf("%d", &len); getchar();
	printf("1 - Preencher aleatoriamente\n");
	printf("2 - Preencher manulamente\n");
	int in; scanf("%d", &in); getchar();
	if(in != 1 && in != 2) {
		return NULL;
	}

	Icone* ic = icone_cria(len);
	if(in == 2) {
		for(int i = 0; i < len; i++) {
			for(int j = 0; j < len; j++) {
				printf("Digite 1 ou 0 (preenchido ou vazio) na posicao icone[%d][%d] do icone\n", i, j);
				scanf("%d", &ic->pixels[i][j]); getchar();
				if(ic->pixels[i][j] != 0) {
					ic->pixels[i][j] = 1;
				} else {
					ic->pixels[i][j] = ' ';
				}
			}
		}

		return ic;
	} else {
		icone_preenche_aleatorio(ic);
		return ic;
	}
}

void limpar_tela() {
	system("cls||clear");
}

void mostrar_icones(Icone* icons[MAXN]) {
	printf("\n\n");
	int contador = 1;
	for(int i = 0; i < MAXN; i++) {
		if(icons[i] != NULL) {
			printf("Icone %d ----------\n", contador);
			icone_imprime(icons[i]);
			printf("\n\n");
			contador++;
		}
	}
}

int Apagar_icone(Icone* icons[MAXN]) {
	mostrar_icones(icons);
	printf("\nDigite qual icone vc deseja apagar: ");
	int n; scanf("%d", &n); getchar();
	for(int i = 0; i < MAXN; i++) {
		if(icons[i] != NULL && n == 1) {
			icone_libera_memoria(icons[i]);
			icons[i] = NULL;
			return 1;
		}

		if(icons[i] != NULL) n--;
	}

	return -1;
}

int verificar_simetria(Icone* icons[MAXN]) {
	mostrar_icones(icons);
	printf("\nDigite qual icone verificar: ");
	int n; scanf("%d", &n); getchar();
	for(int i = 0; i < MAXN; i++) {
		if(n == 1 && icons[i] != NULL) {
			if(eh_simetrico_vertical(icons[i]) == 0 && eh_simetrico_horizontal(icons[i]) == 0) {
				printf("O icone nao eh simetrico\n");
			}

			if(eh_simetrico_vertical(icons[i]) == 1) {
				printf("O icone eh simetrico vertical\n");
			}

			if(eh_simetrico_horizontal(icons[i]) == 1) {
				printf("O icone eh simetrico horizontal\n");
			}

			return 1;
		}

		if(icons[i] != NULL) n--;
	}

	return -1;
}

void alocar(Icone* ic, Icone* icons[MAXN]) {
	for(int i = 0; i < MAXN; i++) {
		if(icons[i] == NULL) {
			icons[i] = ic;
			return;
		}
	}
}

int rotacionar(Icone* icons[MAXN]) {
	mostrar_icones(icons);
	printf("\nDigite qual icone verificar: ");
	int n; scanf("%d", &n); getchar();
	for(int i = 0; i < MAXN; i++) {
		if(icons[i] != NULL && n == 1) {
			Icone* aux = icone_rotaciona(icons[i]);
			icone_imprime(aux);
			printf("\nVoce deseja armazenar o icone? 1 - Sim, 0 - Nao\n");
			int n; scanf("%d", &n); getchar();
			if(n == 1) {
				alocar(aux, icons);
			}

			return 1;
		}

		if(icons[i] != NULL) n--;
	}

	return -1;
}

int criar_reflexao(Icone* icons[MAXN]) {
	mostrar_icones(icons);
	printf("\nDigite qual icone verificar: ");
	int n; scanf("%d", &n); getchar();

	for(int i = 0; i < MAXN; i++) {
		if(icons[i] != NULL && n == 1) {

			printf("Voce deseja armazenar o icone? 1 - Sim, 0 - Nao\n");
			int f, x; scanf("%d", &f); getchar();

			Icone* aux;

			if(f == 1) {
				printf("1 - Reflexao vertical\n");
				printf("2 - Reflexao horizontal\n");
				scanf("%d", &x); getchar();

				if(x == 1) {
					aux = reflexao_vertical(icons[i]);
					limpar_tela();
					icone_imprime(aux);
					alocar(aux, icons);
				} else if(x == 2) {
					aux = reflexao_horizontal(icons[i]);
					limpar_tela();
					icone_imprime(aux);
					alocar(aux, icons);
				} else {
					return -1;
				}

				return 1;
			} else {
				printf("1 - Reflexao vertical\n");
				printf("2 - Reflexao horizontal\n");
				scanf("%d", &x); getchar();

				if(x == 1) {
					aux = reflexao_vertical(icons[i]);
					limpar_tela();
					icone_imprime(aux);
				} else if(x == 2) {
					aux = reflexao_horizontal(icons[i]);
					limpar_tela();
					icone_imprime(aux);
				} else {
					return -1;
				}

				return 1;
			}
		}

		if(icons[i] != NULL) n--;
	}

	return -1;
}

int menu() {
	limpar_tela();
	printf("1 - Criar icone\n");
	printf("2 - Mostrar icones\n");
	printf("3 - Apagar icone\n");
	printf("4 - Verificar simetria\n");
	printf("5 - Criar reflexao\n");
	printf("6 - Rotacionar\n");
	printf("7 - Sair\n");
	int n; scanf("%d", &n); getchar();
	return n;
}

int main() {
	srand(time(NULL));
	Icone* icons[MAXN];
	for(int i = 0; i < MAXN; i++) icons[i] = NULL;

	while(1) {
		switch (menu()) {
		case 1: {
			Icone* ic = criar_icone_opc();
			alocar(ic, icons);
			if(ic != NULL) {
				printf("Icone criado com sucesso\n");
			} else {
				printf("Nao foi possivel criar o icone\n");
			}

			getchar();
			break;
		}

		case 2: {
			mostrar_icones(icons);
			getchar();
			break;
		}

		case 3: {
			int n = Apagar_icone(icons);
			if(n != -1) {
				printf("Icone apagado com sucesso\n");
			} else {
				printf("Nao foi possivel apagar um icone\n");
			}

			getchar();
			break;
		}

		case 4: {
			int n = verificar_simetria(icons);
			if(n == -1) {
				printf("Nao foi possivel verificar o icone\n");
			}

			getchar();
			break;
		}

		case 5: {
			int n = criar_reflexao(icons);
			if(n == -1) {
				printf("Nao foi possivel criar a reflexao do icone\n");
			}

			getchar();
			break;
		}
		
		case 6: {
			int n = rotacionar(icons);
			if(n == -1) {
				printf("Nao foi possivel rotacionar o icone\n");
			}

			getchar();
			break;
		}

		case 7: {
			exit(0);
		}

		default:
			break;
		}
	}
}
