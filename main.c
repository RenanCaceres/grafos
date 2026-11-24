/* main.c - Atividade Avaliativa 3 (Teoria de Grafos)
 * Rede social: grafo simples, nao direcionado, nao ponderado (Atividade 2).
 * Compilar: gcc -Wall -o grafo main.c Grafo.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Grafo.h"

#define N 8
#define GRAU_MAX 3   /* grau maximo do grafo (vertice B) */

static const char NOMES[N + 1] = "ABCDEFGH";

static void limpar_linha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Le vertice A-H; se permitir_nenhum, '0' retorna -1; -2 em EOF */
static int ler_vertice(const char *msg, int permitir_nenhum) {
    char c;
    for (;;) {
        printf("%s", msg);
        if (scanf(" %c", &c) != 1) return -2;
        limpar_linha();
        c = (char)toupper((unsigned char)c);
        if (permitir_nenhum && c == '0') return -1;
        if (c >= 'A' && c < 'A' + N) return c - 'A';
        printf("Vertice invalido.\n");
    }
}

static void imprime_dados(const Busca *b, const char *nome) {
    printf("\n--- Dados gerais da busca (%s) ---\n", nome);
    printf("Vertice de origem          : %c\n", NOMES[b->origem]);
    if (b->destino >= 0) printf("Vertice objetivo           : %c\n", NOMES[b->destino]);
    else printf("Vertice objetivo           : (nenhum - percurso completo)\n");

    printf("Vertices visitados         : {");
    for (int i = 0; i < b->qtd_visitados; i++)
        printf("%c%s", NOMES[b->ordem[i]], i < b->qtd_visitados - 1 ? ", " : "");
    printf("}\n");
    printf("Qtd. de vertices visitados : %d\n", b->qtd_visitados);
    printf("Qtd. de arestas percorridas: %d\n", b->qtd_arestas);

    printf("Caminho percorrido         : ");
    for (int i = 0; i < b->qtd_visitados; i++)
        printf("%c%s", NOMES[b->ordem[i]], i < b->qtd_visitados - 1 ? " -> " : "");
    printf("\n");

    if (b->destino >= 0) {
        if (b->achou) {
            int pilha[MAX_VERT], topo = 0;
            printf("Objetivo                   : ENCONTRADO (%c)\n", NOMES[b->destino]);
            for (int v = b->destino; v != -1; v = b->pai[v]) pilha[topo++] = v;
            printf("Caminho origem->objetivo   : ");
            for (int i = topo - 1; i >= 0; i--)
                printf("%c%s", NOMES[pilha[i]], i > 0 ? " -> " : "");
            printf("\n");
        } else {
            printf("Objetivo                   : NAO encontrado\n");
        }
    }
}

static void exibir_menu(void) {
    printf("\n=========== REDE SOCIAL - GRAFO ===========\n");
    printf(" 1 - Mostrar lista de adjacencia\n");
    printf(" 2 - Mostrar matriz de adjacencia\n");
    printf(" 3 - Busca em profundidade (DFS)\n");
    printf(" 4 - Busca em largura (BFS)\n");
    printf(" 5 - Executar DFS e BFS (comparar)\n");
    printf(" 0 - Sair\n");
    printf("===========================================\n");
    printf("Opcao: ");
}

int main(void) {
    /* Arestas da Atividade 2 (A=0, B=1, ..., H=7) */
    const int arestas[][2] = {{0,1},{0,2},{1,3},{1,4},{2,5},{3,6},{4,7},{5,7}};
    const int nro_arestas = sizeof(arestas) / sizeof(arestas[0]);

    Grafo *gr = cria_Grafo(N, GRAU_MAX, 0);
    if (gr == NULL) { fprintf(stderr, "Erro ao criar o grafo.\n"); return 1; }
    for (int i = 0; i < nro_arestas; i++)
        insereAresta(gr, arestas[i][0], arestas[i][1], 0, 0);   /* nao digrafo */

    int opcao;
    for (;;) {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            if (feof(stdin)) break;
            limpar_linha();
            printf("Entrada invalida.\n");
            continue;
        }
        limpar_linha();
        if (opcao == 0) break;

        if (opcao == 1) imprime_Grafo(gr, NOMES);
        else if (opcao == 2) imprimeMatriz_Grafo(gr, NOMES);
        else if (opcao >= 3 && opcao <= 5) {
            int o = ler_vertice("Vertice de origem (A-H): ", 0);
            if (o == -2) break;
            int d = ler_vertice("Vertice objetivo (A-H, ou 0 para percurso completo): ", 1);
            if (d == -2) break;
            Busca b;
            if (opcao == 3 || opcao == 5) {
                printf("\n=== BUSCA EM PROFUNDIDADE (DFS) ===\n");
                buscaProfundidade_Grafo(gr, o, d, &b, NOMES);
                imprime_dados(&b, "DFS");
            }
            if (opcao == 4 || opcao == 5) {
                printf("\n=== BUSCA EM LARGURA (BFS) ===\n");
                buscaLargura_Grafo(gr, o, d, &b, NOMES);
                imprime_dados(&b, "BFS");
            }
        } else printf("Opcao invalida.\n");
    }

    libera_Grafo(gr);
    printf("\nEncerrando.\n");
    return 0;
}
