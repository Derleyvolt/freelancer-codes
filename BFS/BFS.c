#include <stdio.h>
#include "queue.c"

#define maxn 1000

int n, m;

int mat[maxn][maxn];
int vis[maxn];
int dist[maxn];

void bfs(int u, int d) {
    vis[u]  = 1;
    dist[u] = 0;
    Node* fila = NULL;
    insert_back(&fila, u);
    int len = 1;
    while(len > 0) {
        int v = fila->valor; fila = remove_front(fila);
        len--;
        for(int i = 1; i <= n; i++) {
            if(mat[v][i] == 1 && vis[i] == 0) {
                dist[i] = dist[v]+1;
                vis[i]  = 1;
                insert_back(&fila, i);
                len++;
            }
        }
    }

    if(dist[d] == 1e9+7) {
        printf("Nao eh possivel alcancar o vertice %d a partir de %d\n", d, u);
    } else {
        printf("A menor distancia entre o vertice %d e %d eh: %d\n", u, d, dist[d]);
    }
}

int main() {
    for(int i = 0; i < maxn; i++) {
        dist[i] = 1e9 + 7;
    }

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

    printf("Digite os 2 vertices que voce quer medir a distancia\n");
    int u, v; scanf("%d%d", &u, &v);

    bfs(u, v);
    return 0;
}