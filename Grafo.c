/* Grafo.c: implementacao oculta (listas de adjacencia como listas
 * sequenciais estaticas de tamanho Gmax). Indices comecam em 0. */
#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

struct grafo {
    int eh_ponderado;
    int nro_vert;
    int Gmax;          /* grau maximo: tamanho de cada lista */
    int **arestas;     /* arestas[i][k] = k-esimo vizinho de i */
    float **pesos;
    int *grau;         /* quantas posicoes de arestas[i] estao em uso */
};

Grafo *cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado) {
    if (nro_vertices <= 0 || nro_vertices > MAX_VERT || grau_max <= 0) return NULL;
    Grafo *gr = (Grafo *)malloc(sizeof(struct grafo));
    if (gr == NULL) return NULL;

    gr->nro_vert = nro_vertices;
    gr->Gmax = grau_max;
    gr->eh_ponderado = eh_ponderado ? 1 : 0;
    gr->grau = (int *)calloc(nro_vertices, sizeof(int));
    gr->arestas = (int **)malloc(nro_vertices * sizeof(int *));
    for (int i = 0; i < nro_vertices; i++)
        gr->arestas[i] = (int *)malloc(grau_max * sizeof(int));

    if (gr->eh_ponderado) {
        gr->pesos = (float **)malloc(nro_vertices * sizeof(float *));
        for (int i = 0; i < nro_vertices; i++)
            gr->pesos[i] = (float *)malloc(grau_max * sizeof(float));
    } else {
        gr->pesos = NULL;
    }
    return gr;
}

void libera_Grafo(Grafo *gr) {
    if (gr == NULL) return;
    for (int i = 0; i < gr->nro_vert; i++) free(gr->arestas[i]);
    free(gr->arestas);
    if (gr->eh_ponderado) {
        for (int i = 0; i < gr->nro_vert; i++) free(gr->pesos[i]);
        free(gr->pesos);
    }
    free(gr->grau);
    free(gr);
}

/* Insere a aresta orig->dest (e dest->orig se nao for digrafo). Retorna 1 se ok. */
int insereAresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso) {
    if (gr == NULL) return 0;
    if (orig < 0 || orig >= gr->nro_vert) return 0;
    if (dest < 0 || dest >= gr->nro_vert) return 0;
    if (gr->grau[orig] >= gr->Gmax) return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if (gr->eh_ponderado) gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if (!eh_digrafo) insereAresta(gr, dest, orig, 1, peso);
    return 1;
}

/* ---------- Impressao ---------- */

void imprime_Grafo(Grafo *gr, const char *nomes) {
    if (gr == NULL) return;
    printf("\n=== LISTA DE ADJACENCIA ===\n");
    for (int i = 0; i < gr->nro_vert; i++) {
        printf("  %c: ", nomes[i]);
        for (int j = 0; j < gr->grau[i]; j++)
            printf("%c%s", nomes[gr->arestas[i][j]], j < gr->grau[i] - 1 ? ", " : "");
        printf("   (grau %d)\n", gr->grau[i]);
    }
}

void imprimeMatriz_Grafo(Grafo *gr, const char *nomes) {
    if (gr == NULL) return;
    int n = gr->nro_vert;
    int m[MAX_VERT][MAX_VERT] = {{0}};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < gr->grau[i]; j++)
            m[i][gr->arestas[i][j]] = 1;

    printf("\n=== MATRIZ DE ADJACENCIA ===\n    ");
    for (int j = 0; j < n; j++) printf("%c ", nomes[j]);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("  %c ", nomes[i]);
        for (int j = 0; j < n; j++) printf("%d ", m[i][j]);
        printf("\n");
    }
}

/* ---------- Busca ---------- */

static void inicia_Busca(Busca *res, int origem, int destino, int n) {
    res->origem = origem;
    res->destino = destino;
    res->qtd_visitados = 0;
    res->qtd_arestas = 0;
    res->achou = 0;
    for (int i = 0; i < n; i++) { res->pai[i] = -1; res->ordem[i] = -1; }
}

static void visita(Busca *res, int u) {
    res->ordem[res->qtd_visitados++] = u;
    if (u == res->destino) res->achou = 1;
}

/* DFS recursiva com backtracking */
static void buscaProf(Grafo *gr, int u, int *visitado, Busca *res,
                      const char *nomes, int nivel) {
    visitado[u] = 1;
    visita(res, u);
    printf("%*sVisitando %c\n", nivel * 2, "", nomes[u]);
    if (res->achou) {
        printf("%*sObjetivo %c encontrado!\n", nivel * 2, "", nomes[u]);
        return;
    }
    for (int i = 0; i < gr->grau[u]; i++) {
        int v = gr->arestas[u][i];
        if (!visitado[v]) {
            res->pai[v] = u;
            res->qtd_arestas++;
            printf("%*sAresta {%c,%c}: avancando\n", nivel * 2, "", nomes[u], nomes[v]);
            buscaProf(gr, v, visitado, res, nomes, nivel + 1);
            if (res->achou) return;
            printf("%*sBacktracking: de %c volta para %c\n", nivel * 2, "", nomes[v], nomes[u]);
        }
    }
}

void buscaProfundidade_Grafo(Grafo *gr, int origem, int destino, Busca *res, const char *nomes) {
    int visitado[MAX_VERT] = {0};
    inicia_Busca(res, origem, destino, gr->nro_vert);
    buscaProf(gr, origem, visitado, res, nomes, 0);
}

/* BFS com fila (FIFO) */
void buscaLargura_Grafo(Grafo *gr, int origem, int destino, Busca *res, const char *nomes) {
    int visitado[MAX_VERT] = {0};
    int fila[MAX_VERT], ini = 0, fim = 0;

    inicia_Busca(res, origem, destino, gr->nro_vert);
    visitado[origem] = 1;
    fila[fim++] = origem;

    while (ini < fim) {
        int u = fila[ini++];               /* remove da fila */
        visita(res, u);
        printf("Visitando %c\n", nomes[u]);
        if (res->achou) {
            printf("Objetivo %c encontrado!\n", nomes[u]);
            return;
        }
        for (int i = 0; i < gr->grau[u]; i++) {
            int v = gr->arestas[u][i];
            if (!visitado[v]) {
                visitado[v] = 1;
                res->pai[v] = u;
                res->qtd_arestas++;
                fila[fim++] = v;           /* insere na fila */
                printf("  Aresta {%c,%c}: insere %c na fila\n", nomes[u], nomes[v], nomes[v]);
            }
        }
        printf("  Fila: [");
        for (int i = ini; i < fim; i++)
            printf("%c%s", nomes[fila[i]], i < fim - 1 ? " " : "");
        printf("]\n");
    }
}
