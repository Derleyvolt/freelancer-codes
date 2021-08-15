#include <stdio.h>
#include "linked_list.c"

#define maxn 1000

int n, m;

int mat[maxn][maxn];
int vis[maxn];

void dfs(int u, int d) {
    if(u == d) {
        printf("Voce conseguiu chegar na saida do labirinto\n");
        exit(0);
    }

    vis[u] = 1;

    for(int i = 0; i < n; i++) {
        if(mat[u][i] == 1 && vis[i] == 0) {
            dfs(i, d);
        }
    }
}

int main() {
    printf("Se existem n vertices, entao seus identificadores devem ir ate n, no maximo\n\n");

    printf("Digite o numero de vertices do grafo\n");
    scanf("%d", &n);
    printf("Digite o numero de arestas do grafo\n");
    scanf("%d", &m);
    printf("Digite as m arestas do grafo\n");
    for(int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        mat[u][v] = 1;
        mat[v][u] = 1;
    }

    printf("Digite o vertice de partida e o vertice de saida\n");
    int u, v; scanf("%d%d", &u, &v);

    dfs(u, v);

    printf("Voce nao conseguiu encontrar a saida do labirinto\n");
    return 0;
}