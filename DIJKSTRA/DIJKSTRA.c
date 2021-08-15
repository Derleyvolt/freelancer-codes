#include <stdio.h>
#include <stdlib.h>
#include "heap.c"

#define maxn 1000

int n, m;

vertex *arr;

int mat[maxn][maxn];
int dist[maxn];

void dijkstra(int s, int d) {
    int len = 0;
    dist[s] = 0;
    vertex v;
    v.dist = 0;
    v.u    = s;
    arr[len] = v;
    len++;
    while(len > 0) {
        vertex v = arr[0];
        swap(&arr[0], &arr[len-1]);
        heap_down(arr, len-1, 0);
        len--;

        for(int i = 1; i <= n; i++) {
            v.dist = mat[v.u][i];
            if(mat[v.u][i] >= 1 && dist[i] > dist[v.u] + v.dist) {
                dist[i]  = dist[v.u] + v.dist;
                v.u      = i;
                v.dist   = dist[i];

                arr[len] = v;

                len++;
                heap_up(arr, len, len-1);
            }
        }
    }

    if(dist[d] == 1e9+7) {
        printf("Nao eh possivel alcancar o vertice %d a partir de %d\n", s, d);
    } else {
        printf("A menor distancia entre o vertice %d e %d eh: %d\n", s, d, dist[d]);
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
    printf("Digite as m arestas do grafo e seus respectivos pesos\n");
    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        mat[u][v] = w;
        mat[v][u] = w;
    }

    arr = (vertex*)malloc(sizeof(vertex) * n * 100);

    printf("Digite os 2 vertices que voce quer medir a distancia\n");
    int s, d; scanf("%d%d", &s, &d);

    dijkstra(s, d);
    return 0;
}