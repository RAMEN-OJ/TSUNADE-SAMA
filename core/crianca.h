/*======================================================================
  crianca.h
  Interface para registo de interações no perfil da criança.
  Atualiza estatísticas e atributos emocionais conforme o tipo de ação.
======================================================================*/

#ifndef CRIANCA_H
#define CRIANCA_H

#include "../memoria/perfil.h"
#include "../cognitivo/interpretacao.h"
#include "../cognitivo/interpretador.h"

/* Regista uma interação no perfil, ajustando energia, humor e contadores; retorna void */
void registrarInteracao(PerfilCrianca *perfil, TipoAcao acao, Intencao intencao);

#endif
