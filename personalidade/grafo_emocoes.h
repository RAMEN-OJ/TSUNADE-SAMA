#ifndef GRAFO_EMOCOES_H
#define GRAFO_EMOCOES_H

#include "estado_emocional.h"

#define MAX_ESTADOS 10

typedef struct
{
    EstadoEmocional destino;

    int peso;

} LigacaoEmocional;

typedef struct
{
    EstadoEmocional estado;

    LigacaoEmocional vizinhos[10];

    int quantidade;

} NoEmocional;

typedef struct
{
    NoEmocional nos[MAX_ESTADOS];

    int quantidade;

} GrafoEmocoes;

GrafoEmocoes *criarGrafoEmocoes(void);

void destruirGrafoEmocoes(
        GrafoEmocoes *g);

void adicionarLigacao(
        GrafoEmocoes *g,
        EstadoEmocional origem,
        EstadoEmocional destino,
        int peso);

EstadoEmocional proximoEstado(
        GrafoEmocoes *g,
        EstadoEmocional atual,
        int indice);

void construirGrafoPadrao(
        GrafoEmocoes *g);

#endif