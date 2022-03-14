#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAQUINA 100
#define MAX_JOB     100

// ESTRUTURA UTILIZADA PARA SIMULAR AS MÁQUINAS
// CONTÉM O ID DA MAQUINA E O TEMPO PRA EXECUTAR TAL TAREFA
typedef struct maquina {
    int id;
    int tempo;
} maquina;

// CADA OPERAÇÃO É UM NÓ DESSA LISTA
// CADA NÓ CONTÉM UMA CERTA QUANTIDADE DE MAQUINAS QUE
// PODEM EXECUTAR ESSA OPERAÇÃO
// OBS: UM JOB É COMPOSTO POR UMA LISTA
typedef struct lista {
    maquina lista_maquinas[MAX_MAQUINA];
    int quantidade;
    struct lista* prox;
} lista;

// LISTA DE JOBS
lista* JOBS[MAX_JOB];

// FUNÇÃO UTILIZADA PARA CRIAR UMA MÁQUINA
maquina criar_maquina(int id, int tempo) {
    maquina m;
    m.id    = id;
    m.tempo = tempo;
    return m;
}

// FUNÇÃO DESTINADA A CRIAÇÃO DE OPERAÇÕES
lista* inicia_lista(maquina* lista_maquinas, int quantidade) {
    lista* ls = (lista*)malloc(sizeof(lista));
    for(int i = 0; i < quantidade; i++) {
        ls->lista_maquinas[i] = lista_maquinas[i];
    }

    ls->quantidade = quantidade;
    ls->prox = NULL;
    return ls;
}

// 0-indexed
// REMOVE UMA OPERAÇÃO DA LISTA
void remover_no(lista** ls, lista* anterior, int idx) {
    if(*ls == NULL) {
        return;
    }

    lista* aux = *ls;

    if(idx == 0) {
        // sou o primeiro no
        if(anterior == NULL) {
            // só existe um nó na lista
            if(aux->prox == NULL) {
                aux->quantidade = 0;
                return;
            } else {
                lista* temp = aux->prox;
                for(int i = 0; temp->quantidade; i++) {
                    aux->lista_maquinas[i] = temp->lista_maquinas[i];
                    aux->quantidade        = temp->quantidade;
                }

                aux->prox = temp->prox;
                free(temp);
                return;
            }
        }

        // sou o último no
        if(aux->prox == NULL) {
            anterior->prox = NULL;
            free(aux);
        }
    } else {
        remover_no(&(*ls)->prox, *ls, idx-1);
    }
}

// INSERIR UMA OPERAÇÃO NA LISTA
void inserir(lista** ls, maquina* lista_maquinas, int quantidade) {
    if(*ls == NULL) {
        *ls = inicia_lista(lista_maquinas, quantidade);
        return;
    }

    // tratando um caso especial
    if((*ls)->quantidade == 0) {
        for(int i = 0; i < quantidade; i++) {
            (*ls)->lista_maquinas[i] = lista_maquinas[i];
        }
        (*ls)->quantidade = quantidade;
        return;
    }

    inserir(&(*ls)->prox, lista_maquinas, quantidade);
}

// RETORNA O TAMANHO DE UMA LISTA
int tamanho_lista(lista* ls) {
    int tam = 0;
    if(ls != NULL) {
        tam += tamanho_lista(ls->prox) + 1;
    }

    return tam;
}

// FUNÇÃO DESTINADA À AUXILIAR NA INSERÇÃO DE UMA OPERAÇÃO EM UM JOB
maquina* inserir_operacao_aux(int *qtd) {
    printf("Digite o numero de maquinas que podem executar essa operacao\n");
    scanf("%d", qtd);
    getchar();
    maquina* maq = (maquina*)malloc(sizeof(maquina) * (*qtd));
    for(int i = 0; i < *qtd; i++) {
        printf("Digite o id e o tempo da %d maquina\n", i+1);
        scanf("%d %d", &maq[i].id, &maq[i].tempo);
        getchar();
    }
    return maq;
}

// VERIFICA SE EXISTE PELO MENOS UM JOB EXISTENTE
int existe_job() {
    int idx = 0;
    while(JOBS[idx] != NULL) {
        idx++;
    }
    return idx > 0;
}

// DISPONIBILIZA UM MENU QUE PERMITE O USUARIO ESCOLHER UM JOB PRA EXECUTAR UMA TAREFA
int escolher_job(int i) {
    if(existe_job() == 0) {
        return -1;
    }

    int idx = 0;
    if(i == 1)
        printf("Escolha qual job vc deseja inserir a operacao\n\n");
    else {
        printf("Lista de Jobs\n\n");
    }
    while(JOBS[idx] != NULL) {
        printf("Job: %d\n", idx);
        idx++;
    }

    int indice_job; scanf("%d", &indice_job); getchar();
    if(indice_job > idx-1 || indice_job < 0) {
        return -1;
    }

    return indice_job;
}

// INSERE UMA OPERAÇÃO NUM JOB ESCOLHIDO
int inserir_operacao() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    int qtd;
    maquina* aux = inserir_operacao_aux(&qtd);
    inserir(&JOBS[indice_job], aux, qtd);
    return 1;
}

// CRIA UM JOB VAZIO, OU SEJA, SEM NENHUMA OPERAÇÃO
void criar_job() {
    int qtd;
    for(int i = 0; i < MAX_JOB; i++) {
        if(JOBS[i] == NULL) {
            JOBS[i] = (lista*)malloc(sizeof(lista));
            JOBS[i]->quantidade = 0;
            JOBS[i]->prox = NULL;
            return;
        }
    }
}

// LISTA AS OPERAÇÕES DE UM DETERMINADO JOB
int lista_operacoes_job() {
    int indice_job = escolher_job(0);
    if(indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    lista* aux = JOBS[indice_job];

    int idx = 1;
    while(aux != NULL && aux->quantidade > 0) {
        printf("Operacao %d:\n", idx);
        for(int i = 0; i < aux->quantidade; i++) {
            printf("          Maquina: %d, Tempo: %d\n", aux->lista_maquinas[i].id, aux->lista_maquinas[i].tempo);
        }
        aux = aux->prox;
        idx++;
    }
}

// REMOVER UMA OPERAÇÃO ESPECÍFICA DE UM JOB
int remover_operacao() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    int idx = 0;

    lista* aux = JOBS[indice_job];

    while(aux != NULL && aux->quantidade > 0) {
        printf("Operacao: %d\n", idx);
        idx++;
        aux = aux->prox;
    }

    if(idx == 0) {
        return -1;
    }

    printf("Escolha qual operacao voce deseja remover: ");
    int op; scanf("%d", &op); getchar();
    if(op < 0 || op > idx) {
        return -1;
    }

    remover_no(&JOBS[indice_job], NULL, op);
    return 1;
}

// ALTERAR A OPERAÇÃO DE UM JOB ESPECÍFICO
int alterar_operacao() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    int idx = 0;

    lista* aux = JOBS[indice_job];
    while(aux != NULL && aux->quantidade > 0) {
        printf("Operacao: %d\n", idx);
        idx++;
        aux = aux->prox;
    }

    if(idx == 0) {
        return -1;
    }

    printf("Escolha qual operacao voce deseja alterar: ");
    int op; scanf("%d", &op); getchar();
    if(op < 0 || op > idx-1) {
        return -1;
    }

    aux = JOBS[indice_job];
    while(op > 0) {
        aux = aux->prox;
        op--;
    }


    int qtd;
    maquina* maq = inserir_operacao_aux(&qtd);

    for(int i = 0; i < qtd; i++) {
        aux->lista_maquinas[i] = maq[i];
    }

    aux->quantidade = qtd;
    return 1;
}

// MOSTRA O TEMPO MÍNIMO NECESSÁRIO PARA CONCLUIR UM JOB
int listar_tempo_minimo_aux(int indice_job, int f) {
    lista* aux = JOBS[indice_job];

    int tempo_minimo = 0;

    if(f == 1) {
        system("cls");
        printf("Job %d\n\n", indice_job);
    }

    int idx = 0;

    while(aux != NULL) {
        int min = 1000000;
        int id;
        for(int i = 0; i < aux->quantidade; i++) {
            if(min > aux->lista_maquinas[i].tempo) {
                min = aux->lista_maquinas[i].tempo;
                id  = aux->lista_maquinas[i].id;
            }
        }
        if(f == 1)
            printf("Operacao %d: Maquina: %d, Tempo: %d\n", idx, id, min);
        tempo_minimo += min;
        aux = aux->prox;
        idx++;
    }
    if(f == 1)
        printf("\nTempo minimo necessario para completar o Job %d eh: %d\n", indice_job, tempo_minimo);
    return tempo_minimo;
}

// FUNÇÃO AUXILIAR PARA MOSTRAR O TEMPO MÍNIMO
int listar_tempo_minimo() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    return listar_tempo_minimo_aux(indice_job, 1);
}

// FUNÇÃO AUXILIAR PARA MOSTRAR O TEMPO MÁXIMO
int listar_tempo_maximo_aux(int indice_job, int f) {
    lista* aux = JOBS[indice_job];

    int tempo_maximo = 0;
    if(f == 1) {
        system("cls");
        printf("Job %d\n\n", indice_job);
    }

    int idx = 0;

    while(aux != NULL) {
        int max = -1;
        int id;
        for(int i = 0; i < aux->quantidade; i++) {
            if(max < aux->lista_maquinas[i].tempo) {
                max = aux->lista_maquinas[i].tempo;
                id  = aux->lista_maquinas[i].id;
            }
        }
        if(f == 1)
            printf("Operacao %d: Maquina: %d, Tempo: %d\n", idx, id, max);
        tempo_maximo += max;
        aux = aux->prox;
        idx++;
    }

    if(f == 1)
        printf("\nTempo maximo necessario para completar o Job %d eh: %d\n", indice_job, tempo_maximo);
    return tempo_maximo;
}

// MOSTRA O TEMPO MÁXIMO NECESSÁRIO PARA CONCLUIR UM JOB
int listar_tempo_maximo() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    return listar_tempo_maximo_aux(indice_job, 1);
}

// MOSTRA O TEMPO MÉDIO PARA EXECUTAR UMA OPERAÇÃO DE UM JOB
int listar_tempo_medio() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    int idx = 0;

    lista* aux = JOBS[indice_job];
    while(aux != NULL && aux->quantidade > 0) {
        printf("Operacao: %d\n", idx);
        idx++;
        aux = aux->prox;
    }

    if(idx == 0) {
        return -1;
    }

    printf("Escolha qual operacao: ");
    int op; scanf("%d", &op); getchar();
    if(op < 0 || op > idx) {
        return -1;
    }

    aux = JOBS[indice_job];

    while(op > 0) {
        aux = aux->prox;
        op--;
    }

    double tempo_medio = 0;

    for(int i = 0; i < aux->quantidade; i++) {
        tempo_medio += aux->lista_maquinas[i].tempo;
    }

    printf("Tempo medio para executar a operacao eh: %.2lf\n", tempo_medio/aux->quantidade);
    return 1;
}

// REMOVE UM JOB ESPECÍFICO DA LISTA DE JOBS
int remover_job() {
    int indice_job = escolher_job(1);
    if(indice_job == -1) {
        return -1;
    }

    free(JOBS[indice_job]);

    for(int i = indice_job; JOBS[i] != NULL; i++) {
        JOBS[i] = JOBS[i+1];
    }

    return 1;
}

// MENU DE OPÇÕES
int menu() {
    system("cls");
    printf("1  - Inserir Operacao\n");
    printf("2  - Remover Operacao\n");
    printf("3  - Alterar Operacao\n");
    printf("4  - Criar Job\n");
    printf("5  - Listar Job\n");
    printf("6  - Salvar\n");
    printf("7  - Carregar\n");
    printf("8  - Listar tempo minimo para completar o Job\n");
    printf("9  - Listar tempo maximo para completar o Job\n");
    printf("10 - Listar tempo medio para completar uma Operacao\n");
    printf("11 - Remover Job\n");
    printf("12 - Mostrar Process Plan dos Jobs\n");
    printf("13 - Sair\n");
    int n; scanf("%d", &n);
    getchar();

    if(n < 1 || n > 13) {
        return -1;
    }

    return n;
}

// FUNÇÃO AUXILIAR
void print_chars(char ch, int count, int newline) {
	for(int i = 0; i < count; i++) {
		printf("%c", ch);
	}

	if(newline == 1) {
		printf("\n");
	}
}

// FUNÇÃO UTILIZADA PARA MOSTRAR O PROCESS PLAN DOS JOBS
void mostrar_tabela() {
    char *str1 = "Process Plan";
	int len_str1 = strlen(str1);
	char *str2 = "Operation";
	int len_str2 = strlen(str2);

    system("cls");

	printf("%s", str1);
	print_chars(' ', 7, 0);
	printf("%s\n", str2);

    int idx = 0;
    char buf[10];
    while(JOBS[idx] != NULL) {
        printf("%d", idx);
        itoa(idx, buf, 10);
	    print_chars(' ', strlen(str1)-strlen(buf) + 7, 0);
        lista* aux = JOBS[idx];

        int tempo_min = 100000;
        int id;

        while(aux != NULL) {
            for(int i = 0; i < aux->quantidade; i++) {
                if(tempo_min > aux->lista_maquinas[i].tempo) {
                    tempo_min = aux->lista_maquinas[i].tempo;
                    id        = aux->lista_maquinas[i].id;
                }
            }

            printf("[%d, %d]", id, tempo_min);
            if(aux->prox != NULL) {
                printf(" ---> ");
            }

            aux = aux->prox;
        }
        printf("\n");
        idx++;
    }
}

int main() {
    while(1) {
        switch (menu()) {
            case 1: {
                int ret = inserir_operacao();
                if(ret == -1) {
                    printf("Nao foi possivel inserir uma nova operacao\n");
                }
                getchar();
                break;
            }

            case 2: {
                int ret = remover_operacao();
                if(ret == -1) {
                    printf("Nao foi possivel remover a operacao\n");
                } else {
                    printf("A operacao foi removida com sucesso\n");
                }
                getchar();
                break;
            }

            case 3: {
                int ret = alterar_operacao();
                if(ret == -1) {
                    printf("Nao foi possivel alterar a opecarao\n");
                } else {
                    printf("Operacao alterada com sucesso\n");
                }

                getchar();
                break;
            }

            case 4: {
                criar_job();
                printf("Job criado com sucesso\n");
                getchar();
                break;
            }

            case 5: {
                int ret = lista_operacoes_job();
                if(ret == -1) {
                    printf("Nao foi possivel listar as operacoes\n");
                }
                getchar();
                break;
            }

            case 6: {
                char buf[50];
                printf("Digite o nome do arquivo que voce deseja salvar os jobs: ");
                scanf("%s", buf);
                FILE* fp = fopen(buf, "w");

                if(fp == NULL) {
                    printf("Nao foi possivel salvar o arquivo\n");
                    getchar();
                    break;
                }

                int idx = 0;

                while(JOBS[idx] != NULL) {
                    lista* aux = JOBS[idx];

                    int tam = tamanho_lista(JOBS[idx]);

                    // quantidade de operacoes
                    fprintf(fp, "%d\n", tam);

                    for(int i = 0; i < tam; i++) {
                        fprintf(fp, "%d\n", aux->quantidade);
                        for(int i = 0; i < aux->quantidade; i++) {
                            fprintf(fp, "%d %d\n", aux->lista_maquinas[i].id, aux->lista_maquinas[i].tempo);
                        }
                        aux = aux->prox;
                    }

                    idx++;
                }

                printf("Jobs salvos com sucesso\n");
				fclose(fp);
                getchar();
                break;
            }

            case 7: {
				char buf[50];
                printf("Digite o nome do arquivo que voce deseja carregar os dados: ");
                scanf("%s", buf);
                getchar();
                FILE* fp = fopen(buf, "r");

                if(fp == NULL) {
                    printf("Nao foi possivel abrir o arquivo\n");
                    getchar();
                    break;
                }

				int jobs_qtd;
				int idx = 0;

				while(fscanf(fp, "%d", &jobs_qtd) != EOF) {
					JOBS[idx] = (lista*)malloc(sizeof(lista));
					JOBS[idx]->quantidade = 0;
					JOBS[idx]->prox       = NULL;
					lista* aux = JOBS[idx];
					for(int i = 0; i < jobs_qtd; i++) {
						int op_qtd; fscanf(fp, "%d", &op_qtd);
						aux->quantidade = op_qtd;
						for(int j = 0; j < op_qtd; j++) {
							maquina maq;
							fscanf(fp, "%d %d", &maq.id, &maq.tempo);
							aux->lista_maquinas[j] = maq;
						}
                        
                        if(i+1 >= jobs_qtd) continue;

						aux->prox = (lista*)malloc(sizeof(lista));
                        aux->prox->quantidade = 0;
                        aux->prox->prox       = NULL;
                        aux                   = aux->prox;
					}

					idx++;
				}

				fclose(fp);
				printf("Arquivo carregado com sucesso\n");
				getchar();
				break;
            }

            case 8: {
                int ret = listar_tempo_minimo();
                if(ret == -1) {
                    printf("Nao foi possivel listar o tempo do respectivo Job\n");
                }
                getchar();
                break;
            }

            case 9: {
                int ret = listar_tempo_maximo();
                if(ret == -1) {
                    printf("Nao foi possivel listar o tempo do respectivo Job\n");
                }
                getchar();
                break;
            }

            case 10: {
                int ret = listar_tempo_medio();
                if(ret == -1) {
                    printf("Nao foi possivel calcular o tempo medio do Job\n");
                } 
                getchar();
                break;
            }

            case 11: {
                int ret = remover_job();
                if(ret == -1) {
                    printf("Nao foi possivel remover o Job\n");
                } else {
                    printf("Job removido com sucesso\n");
                }
                getchar();
                break;
            }

            case 12: {
                mostrar_tabela();
                getchar();
                break;
            }

            case 13: {
                return 0;
            }

            default:
                break;
        }
    }

    return 0;
}
