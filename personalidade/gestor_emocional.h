#ifndef GESTOR_EMOCIONAL_H
#define GESTOR_EMOCIONAL_H

#include "emocoes.h"

typedef enum
{
    EVENTO_NEUTRO,

    EVENTO_APRENDEU,

    EVENTO_PERGUNTA,

    EVENTO_BRINCADEIRA,

    EVENTO_ERRO,

    EVENTO_ELOGIO

} EventoEmocional;

void processarEventoEmocional(
        Emocoes *e,
        EventoEmocional evento);

#endif