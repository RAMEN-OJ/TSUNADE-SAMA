#ifndef EMOCOES_H
#define EMOCOES_H

#include "estado_emocional.h"
#include "grafo_emocoes.h"

typedef struct
{
    EstadoEmocional estado;

    GrafoEmocoes *grafo;

    int energia;
    int curiosidade;
    int empatia;

} Emocoes;

Emocoes *criarEmocoes(void);

void destruirEmocoes(
        Emocoes *e);

void mudarEstado(
        Emocoes *e,
        EstadoEmocional novo);

void avancarEmocao(
        Emocoes *e,
        int escolha);

void mostrarEmocoes(
        Emocoes *e);

const char *nomeEstado(
        EstadoEmocional estado);

#endif