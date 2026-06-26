#ifndef DECISOR_H
#define DECISOR_H

#include "../core/tsunade.h"
#include "../cognitivo/interpretador.h"
#include "../personalidade/gestor_emocional.h"

EventoEmocional decidirEventoEmocional(
        Tsunade *t,
        const char *frase,
        Intencao intencao);

#endif