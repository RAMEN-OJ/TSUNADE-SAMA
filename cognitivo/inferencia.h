#ifndef INFERENCIA_H
#define INFERENCIA_H

#include "../conhecimento/conceitos.h"

int inferirRelacao(
        BaseConhecimento *base,
        const char *origem,
        const char *destino);

int herdaPropriedade(
        BaseConhecimento *base,
        const char *conceito,
        const char *propriedade,
        char *origem);

int responderInferencia(
        BaseConhecimento *base,
        const char *conceito,
        char *resposta);

int pesquisarConhecimento(
        BaseConhecimento *base,
        const char *texto,
        char *resposta);

int executarInferencia(
        BaseConhecimento *base,
        const char *frase,
        char *resposta);

#endif