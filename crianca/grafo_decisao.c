/* ==========================================================================
 * grafo_decisao.c — Grafo de acções ponderadas
 *
 * Implementação do registo de acções candidatas e selecção da
 * acção com maior peso de prioridade.
 * ========================================================================== */

#include <string.h>

#include "grafo_decisao.h"

/**
 * Reinicia contador de acções do grafo de decisão.
 */
void iniciarGrafoDecisao(GrafoDecisao *g)
{
    g->total = 0;
}

/**
 * Adiciona acção ao grafo se ainda houver capacidade disponível.
 */
void adicionarAcao(GrafoDecisao *g, const char *nome, int peso)
{
    if(g == NULL || g->total >= MAX_ACOES)
        return;

    strncpy(g->acoes[g->total].nome, nome, sizeof(g->acoes[g->total].nome) - 1);
    g->acoes[g->total].nome[sizeof(g->acoes[g->total].nome) - 1] = '\0';
    g->acoes[g->total].peso = peso;
    g->total++;
}

/**
 * Selecciona a acção com o maior peso entre as candidatas registadas.
 */
Acao *melhorAcao(GrafoDecisao *g)
{
    int melhor = 0;
    int i;

    if(g == NULL || g->total == 0)
        return NULL;

    for(i = 1; i < g->total; i++)
    {
        if(g->acoes[i].peso > g->acoes[melhor].peso)
            melhor = i;
    }

    return &g->acoes[melhor];
}
