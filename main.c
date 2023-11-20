#include <stdio.h>
#include <stdlib.h>

#define V 6

typedef struct {
    int NumVertices;
    int **Mat;
} TipoGrafo;

void Caminho_mais_Curto(TipoGrafo *grafo, int origem, int destino) {
    int i, vert, k, NovaDist, min;
    int *M, *L, *A, *caminho;
    M = (int *)malloc(grafo->NumVertices * sizeof(int));
    L = (int *)malloc(grafo->NumVertices * sizeof(int));
    A = (int *)malloc(grafo->NumVertices * sizeof(int));
    caminho = (int *)malloc(grafo->NumVertices * 3 * sizeof(int));

    for (i = 0; i < grafo->NumVertices; i++) {
        M[i] = 0;
        A[i] = -1;
        L[i] = 300000;
    }

    vert = origem;
    L[vert] = 0;

    while (vert != destino && vert != -1) {
        for (i = 0; i < grafo->NumVertices; i++) {
            if (grafo->Mat[vert][i] != 0 && M[i] == 0) {
                NovaDist = L[vert] + grafo->Mat[vert][i];
                if (NovaDist < L[i]) {
                    L[i] = NovaDist;
                    A[i] = vert;
                }
            }
        }

        M[vert] = 1;
        min = 300000;
        vert = -1;

        for (i = 0; i < grafo->NumVertices; i++) {
            if (M[i] == 0 && L[i] < min) {
                min = L[i];
                vert = i;
            }
        }
    }

    if (vert == destino) {
        printf("Caminho mais curto entre %d e %d tem comprimento %d: ", origem, destino, L[destino]);
        caminho[0] = destino;
        k = 1;
        while (A[vert] != -1) {
            caminho[k] = A[vert];
            vert = A[vert];
            k++;
        }
        for (i = k - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
    } else {
        printf("Não existe caminho entre %d e %d\n", origem, destino);
    }
}


int main() {
    int graph[V][V] = {
        {0, 1, 4, 0, 0, 0},
        {1, 0, 4, 2, 7, 0},
        {4, 4, 0, 3, 5, 0},
        {0, 2, 3, 0, 4, 6},
        {0, 7, 5, 4, 0, 7},
        {0, 0, 0, 6, 7, 0}
    };

    TipoGrafo grafo;
    grafo.NumVertices = V;
    grafo.Mat = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        grafo.Mat[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            grafo.Mat[i][j] = graph[i][j];
        }
    }

    Caminho_mais_Curto(&grafo, 0, 4);

    for (int i = 0; i < V; i++) {
        free(grafo.Mat[i]);
    }
    free(grafo.Mat);

    return 0;
}