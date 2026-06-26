#include <stdlib.h>

#include "grafo_emocoes.h"

static NoEmocional *buscarNo(
        GrafoEmocoes *g,
        EstadoEmocional estado)
{
    for(int i=0;i<g->quantidade;i++)
    {
        if(g->nos[i].estado==estado)
            return &g->nos[i];
    }

    return NULL;
}

GrafoEmocoes *criarGrafoEmocoes(void)
{
    GrafoEmocoes *g =
        malloc(sizeof(GrafoEmocoes));

    if(g==NULL)
        return NULL;

    g->quantidade=0;

    construirGrafoPadrao(g);

    return g;
}

void destruirGrafoEmocoes(
        GrafoEmocoes *g)
{
    free(g);
}

void adicionarLigacao(
        GrafoEmocoes *g,
        EstadoEmocional origem,
        EstadoEmocional destino,
        int peso)
{
    NoEmocional *no =
        buscarNo(g, origem);

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

EstadoEmocional proximoEstado(
        GrafoEmocoes *g,
        EstadoEmocional atual,
        int indice)
{
    NoEmocional *no =
        buscarNo(g, atual);

    if(no==NULL)
        return atual;

    if(indice>=no->quantidade)
        return atual;

    return no->vizinhos[indice].destino;
}

void construirGrafoPadrao(
        GrafoEmocoes *g)
{
    adicionarLigacao(g,FELIZ,CURIOSA,5);
    adicionarLigacao(g,FELIZ,ORGULHOSA,3);

    adicionarLigacao(g,CURIOSA,FELIZ,4);
    adicionarLigacao(g,CURIOSA,BRINCALHONA,5);

    adicionarLigacao(g,BRINCALHONA,FELIZ,5);

    adicionarLigacao(g,PREOCUPADA,FELIZ,2);

    adicionarLigacao(g,ORGULHOSA,FELIZ,4);
}