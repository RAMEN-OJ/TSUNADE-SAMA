#ifndef BFS_SEMANTICO_H
#define BFS_SEMANTICO_H

#include "../conhecimento/conceitos.h"

int existeCaminho(
        BaseConhecimento *base,
        const char *origem,
        const char *destino);

int encontrarCaminho(
        BaseConhecimento *b,
        const char *origem,
        const char *destino,
        char caminho[][100],
        int *quantidade);
#endif