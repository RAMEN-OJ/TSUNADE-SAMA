/*======================================================================
  analisador.h
  Interface do analisador de intenções por vocabulário.
  Classifica frases em intenções dialogais (saudação, estudo, jogo, etc.).
======================================================================*/

#ifndef ANALISADOR_H
#define ANALISADOR_H

#include "../conhecimento/vocabulario.h"

/* Analisa frase token a token e devolve a intenção de maior prioridade */
Intencao analisarFrase(Vocabulario *v,const char *frase);

#endif
