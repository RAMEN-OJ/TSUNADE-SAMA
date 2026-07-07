/*======================================================================
  inferencia.h
  Interface do módulo de inferência e pesquisa semântica.
  Navega o grafo de conhecimento e responde consultas complexas.
======================================================================*/

#ifndef INFERENCIA_H
#define INFERENCIA_H

#include "../conhecimento/conceitos.h"

/* Verifica existência de caminho entre dois conceitos no grafo; retorna 1 se existe */
int inferirRelacao(BaseConhecimento *base, const char *origem, const char *destino);

/* Herda propriedade de um conceito via relações do grafo; retorna 1 se encontrou */
int herdaPropriedade(BaseConhecimento *base, const char *conceito, const char *propriedade, char *origem);

/* Responde consulta de inferência sobre um conceito; retorna 1 se respondeu */
int responderInferencia(BaseConhecimento *base, const char *conceito, char *resposta);
  
/* Pesquisa conhecimento por texto livre ou conceito; retorna 1 se encontrou */
int pesquisarConhecimento(BaseConhecimento *base, const char *texto, char *resposta);

/* Executa inferência completa a partir de uma frase; retorna 1 se respondeu */
int executarInferencia(BaseConhecimento *base, const char *frase, char *resposta);
 
#endif
