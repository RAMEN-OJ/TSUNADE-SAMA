/*======================================================================
  aprendizagem.h
  Interface do módulo de aprendizagem por conversa.
  Extrai e persiste dados de perfil e conhecimento semântico.
======================================================================*/

#ifndef APRENDIZAGEM_H
#define APRENDIZAGEM_H

#include "../core/tsunade.h"
#include "../memoria/perfil.h"
#include "../conhecimento/conceitos.h"

/* Extrai valor associado a uma chave na frase; retorna ponteiro estático ou NULL */
char *extrairValor(const char *frase, const char *chave);

/* Aprende dados pessoais (nome, idade, preferências) no perfil; retorna 1 se aprendeu */
int aprenderPerfil(PerfilCrianca *perfil, const char *frase, char *resposta);

/* Aprende relação semântica (sujeito-relação-objeto) na base; retorna 1 se aprendeu */
int aprenderConhecimento(BaseConhecimento *base, const char *frase, char *resposta);

/* Tenta aprender perfil ou conhecimento a partir de conversa livre; retorna 1 se tratou */
int tentarAprendizagemConversa(Tsunade *t, const char *frase, char *resposta);

#endif
