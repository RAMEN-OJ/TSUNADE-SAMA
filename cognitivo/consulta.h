/*======================================================================
  consulta.h
  Interface do módulo de consultas ao perfil e conhecimento.
  Responde perguntas sobre dados pessoais e relações semânticas.
======================================================================*/

#ifndef CONSULTA_H
#define CONSULTA_H

#include "../conhecimento/conceitos.h"
#include "../memoria/perfil.h"

/* Responde consultas sobre dados do perfil da criança; retorna 1 se respondeu */
int responderConsulta(PerfilCrianca *perfil, const char *frase, char *resposta);

/* Lista relações conhecidas sobre um conceito; retorna 1 se encontrou */
int consultarConhecimento(BaseConhecimento *base, const char *conceito, char *resposta);

/* Alias semântico para consultarConhecimento; retorna 1 se encontrou */
int responderConsultaSemantica(BaseConhecimento *base, const char *conceito, char *resposta);    

#endif
