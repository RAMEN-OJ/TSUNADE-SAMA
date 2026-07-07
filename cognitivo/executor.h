/*======================================================================
  executor.h
  Interface do executor de ações cognitivas.
  Despacha interpretações para os módulos especializados adequados.
======================================================================*/

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../core/tsunade.h"
#include "interpretacao.h"

/* Executa ação correspondente ao tipo de interpretação; retorna 1 se tratada */
int executarInterpretacao(Tsunade *t, Interpretacao *i, const char *frase, char *resposta);

#endif
