/*======================================================================
  motor.h
  Interface pública do motor de execução da Tsunade.
  Declara apresentação inicial e ciclo de interação com o utilizador.
======================================================================*/

#ifndef MOTOR_H
#define MOTOR_H

#include "tsunade.h"

/* Apresenta a Tsunade ao utilizador com saudação personalizada; parâmetro: t (instância) */
void apresentarTsunade(Tsunade *t);

/* Executa um ciclo completo de interação: estado, decisão autónoma e processamento de frase; parâmetro: t */
void executarCiclo(Tsunade *t);

#endif
