/* Grafo.h: parte visivel ao programador (TAD Grafo)
 *
 * Atividade Avaliativa 3 - Teoria de Grafos
 * Tema: Redes sociais - Equipe: Giovana, Renan
 */
#ifndef GRAFO_H
#define GRAFO_H

#define MAX_VERT 64

/* Tipo opaco: a struct fica escondida em Grafo.c */
typedef struct grafo Grafo;

/* Dados gerais de uma busca */
typedef struct {
    int origem;
    int destino;                /* -1 = sem objetivo */
    int ordem[MAX_VERT];        /* caminho percorrido (vertices na ordem de visita) */
    int pai[MAX_VERT];          /* vertice que levou a cada vertice (-1 = nenhum) */
    int qtd_visitados;
    int qtd_arestas;            /* arestas percorridas ate descobrir novos vertices */
    int achou;                  /* 1 se o objetivo foi encontrado */
} Busca;

Grafo *cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void   libera_Grafo(Grafo *gr);
int    insereAresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso);

void   imprime_Grafo(Grafo *gr, const char *nomes);   /* lista de adjacencia */
void   imprimeMatriz_Grafo(Grafo *gr, const char *nomes);

void   buscaProfundidade_Grafo(Grafo *gr, int origem, int destino, Busca *res, const char *nomes);
void   buscaLargura_Grafo(Grafo *gr, int origem, int destino, Busca *res, const char *nomes);

#endif
