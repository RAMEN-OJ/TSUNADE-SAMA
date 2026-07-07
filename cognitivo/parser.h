/*======================================================================
  parser.h
  Interface do analisador sintático de frases.
  Converte texto livre numa estrutura Interpretacao tipada.
======================================================================*/

#ifndef PARSER_H
#define PARSER_H

#include "interpretacao.h"

/* Analisa frase e preenche estrutura de interpretação; parâmetros: frase, inter (saída) */
void interpretarFrase(const char *frase, Interpretacao *inter);

#endif
