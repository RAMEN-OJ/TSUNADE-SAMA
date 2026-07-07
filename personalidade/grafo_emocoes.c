/* ==========================================================================
 * grafo_emocoes.c — Grafo de transições emocionais
 *
 * Implementação do grafo de estados emocionais com criação de nós
 * dinâmica, ligações ponderadas e topologia padrão da personalidade.
 * ========================================================================== */

#include <stdlib.h>

#include "grafo_emocoes.h"

/**
 * Procura nó correspondente a um estado emocional no grafo.
 */
static NoEmocional *buscarNo(GrafoEmocoes *g, EstadoEmocional estado)
{
    for(int i=0;i<g->quantidade;i++)
    {
        if(g->nos[i].estado==estado)
            return &g->nos[i];
    }
    return NULL;
}

/**
 * Aloca grafo emocional e constrói ligações padrão.
 */
GrafoEmocoes *criarGrafoEmocoes(void)
{
    GrafoEmocoes *g = malloc(sizeof(GrafoEmocoes));

    if(g==NULL)
        return NULL;

    g->quantidade=0;

    construirGrafoPadrao(g);

    return g;
}

/**
 * Liberta memória do grafo emocional.
 */
void destruirGrafoEmocoes(GrafoEmocoes *g)
{
    free(g);
}

/**
 * Regista ligação ponderada, criando nó de origem se necessário.
 */
void adicionarLigacao(GrafoEmocoes *g, EstadoEmocional origem, EstadoEmocional destino, int peso)
{
    NoEmocional *no = buscarNo(g, origem);

    if(no==NULL)
    {
        no=&g->nos[g->quantidade++];
        no->estado=origem;
        no->quantidade=0;
    }

    no->vizinhos[no->quantidade].destino=destino;
    no->vizinhos[no->quantidade].peso=peso;

    no->quantidade++;
}

/**
 * Devolve estado destino da transição indexada a partir do estado actual.
 */
EstadoEmocional proximoEstado(GrafoEmocoes *g, EstadoEmocional atual, int indice)
{
    NoEmocional *no = buscarNo(g, atual);

    if(no==NULL)
        return atual;

    if(indice>=no->quantidade)
        return atual;

    return no->vizinhos[indice].destino;
}

/**
 * Define transições emocionais predefinidas da personalidade Tsunade.
 */
void construirGrafoPadrao(GrafoEmocoes *g)
{
    adicionarLigacao(g,FELIZ,CURIOSA,5);
    adicionarLigacao(g,FELIZ,ORGULHOSA,3);

    adicionarLigacao(g,CURIOSA,FELIZ,4);
    adicionarLigacao(g,CURIOSA,BRINCALHONA,5);

    adicionarLigacao(g,BRINCALHONA,FELIZ,5);

    adicionarLigacao(g,PREOCUPADA,FELIZ,2);

    adicionarLigacao(g,ORGULHOSA,FELIZ,4);
}
