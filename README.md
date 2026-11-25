# Implementação de Grafos em C - Rede Social

**Universidade Tecnológica Federal do Paraná (UTFPR)**  
**Disciplina:** Estratégias de Programação 2026-02  
**Professor:** Claydon Kossoski  
**Tema:** Implementação de grafos em C  
**Equipe:** Giovana Furlan, Renan Cáceres 

## 📌 Sobre o Projeto
Este projeto consiste na implementação, em linguagem C, do grafo modelado na Atividade Avaliativa 2. O grafo representa uma rede social de relacionamentos (amizades) entre 8 usuários.

**Características do Grafo (Atividade 2):**
*   **Tipo:** Grafo simples, não direcionado e não ponderado.
*   **Vértices (8):** A, B, C, D, E, F, G, H (representando os usuários).
*   **Arestas (8):** Relações de amizade: {A,B}, {A,C}, {B,D}, {B,E}, {C,F}, {D,G}, {E,H}, {F,H}.
*   O grafo é conexo e bipartido.

## ⚙️ Funcionalidades Implementadas

O programa conta com um menu interativo no terminal que permite ao usuário selecionar e executar as seguintes funcionalidades:

1.  **Busca em Profundidade (DFS):** Implementada de forma recursiva, utilizando backtracking para explorar os vértices.
2.  **Busca em Largura (BFS):** Implementada utilizando uma estrutura de fila (queue) para explorar os níveis do grafo.
3.  **Caminho Percorrido:** Exibição organizada da sequência de vértices visitados durante a execução de cada algoritmo.
4.  **Dados Gerais da Busca:** Após cada busca, o sistema exibe um relatório contendo:
    *   Vértice de origem;
    *   Vértices visitados;
    *   Quantidade de vértices visitados;
    *   Quantidade de arestas percorridas;
    *   Caminho percorrido;
    *   Indicação se o objetivo foi encontrado ou não.

## 🛠️ Como Compilar e Executar

Para compilar e rodar o projeto, você precisará de um compilador C (como o `gcc`) instalado em sua máquina.

**1. Clone o repositório:**
```bash
git clone https://github.com/RenanCaceres/grafos.git
cd grafos