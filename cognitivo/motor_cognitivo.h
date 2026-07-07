/*======================================================================
  motor_cognitivo.h
  Interface do motor cognitivo central da Tsunade.
  Declara a função principal de processamento de linguagem natural.
======================================================================*/

#ifndef MOTOR_COGNITIVO_H
#define MOTOR_COGNITIVO_H

#include "../core/tsunade.h"

/* Processa uma frase e gera resposta cognitiva; retorna 1 se tratada, 0 caso contrário */
int pensar(Tsunade *t, const char *frase, char *resposta);

#endif
