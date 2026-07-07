#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../core/tsunade.h"
#include "interpretacao.h"

int executarInterpretacao(
        Tsunade *t,
        Interpretacao *i,
        const char *frase,
        char *resposta);

#endif