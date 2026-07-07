/*======================================================================
  decisor.h
  Interface do decisor de eventos emocionais.
  Mapeia frases e intenções para eventos do gestor emocional.
======================================================================*/

#ifndef DECISOR_H
#define DECISOR_H

#include "../core/tsunade.h"
#include "../cognitivo/interpretador.h"
#include "../personalidade/gestor_emocional.h"

/* Decide evento emocional com base na frase e intenção; retorna EventoEmocional */
EventoEmocional decidirEventoEmocional(Tsunade *t, const char *frase, Intencao intencao);

#endif
