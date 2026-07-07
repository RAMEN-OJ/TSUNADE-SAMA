/* ==========================================================================
 * gestor_emocional.h — Gestor de eventos emocionais
 *
 * Mapeia eventos da interacção (aprendizagem, brincadeira, erro, etc.)
 * em transições de estado emocional da Tsunade.
 * ========================================================================== */

#ifndef GESTOR_EMOCIONAL_H
#define GESTOR_EMOCIONAL_H

#include "emocoes.h"

/** Tipos de evento que influenciam o estado emocional. */
typedef enum
{
    EVENTO_NEUTRO,

    EVENTO_APRENDEU,

    EVENTO_PERGUNTA,

    EVENTO_BRINCADEIRA,

    EVENTO_ERRO,

    EVENTO_ELOGIO

} EventoEmocional;

/** Processa evento e actualiza estado emocional via grafo. */
void processarEventoEmocional(Emocoes *e, EventoEmocional evento);

#endif
