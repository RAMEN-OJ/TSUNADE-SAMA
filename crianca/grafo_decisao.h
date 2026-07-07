/* ==========================================================================
 * grafo_decisao.h — Grafo de acções ponderadas
 *
 * Estrutura simples que acumula acções candidatas com pesos de
 * prioridade para seleção da melhor acção autónoma.
 * ========================================================================== */

#ifndef GRAFO_DECISAO_H
#define GRAFO_DECISAO_H

#define MAX_ACOES 20

/** Acção candidata com nome e peso de prioridade. */
typedef struct
{
    char nome[50];
    int peso;

} Acao;

/** Conjunto de acções candidatas para decisão autónoma. */
typedef struct
{
    Acao acoes[MAX_ACOES];

    int total;

} GrafoDecisao;

/** Reinicia o grafo de decisão sem acções. */
void iniciarGrafoDecisao(GrafoDecisao *g);

/** Regista acção candidata com peso de prioridade. */
void adicionarAcao(
        GrafoDecisao *g,
        const char *nome,
        int peso);

/** Devolve ponteiro para a acção de maior peso. */
Acao *melhorAcao(
        GrafoDecisao *g);

#endif
