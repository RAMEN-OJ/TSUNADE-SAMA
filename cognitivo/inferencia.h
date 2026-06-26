#ifndef INFERENCIA_H
#define INFERENCIA_H

#include "../conhecimento/conceitos.h"

int inferirRelacao(
        BaseConhecimento *base,
        const char *origem,
        const char *destino);

#endif