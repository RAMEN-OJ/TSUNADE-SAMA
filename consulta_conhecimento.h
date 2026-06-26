#ifndef CONSULTA_CONHECIMENTO_H
#define CONSULTA_CONHECIMENTO_H

#include "../conhecimento/conceitos.h"

int consultarConhecimento(
        BaseConhecimento *base,
        const char *frase,
        char *resposta);

#endif
