/* ==========================================================================
 * atividades.h — Actividades educativas e lúdicas
 *
 * Orquestração de histórias, jogos, exercícios e lições iniciadas
 * por acções autónomas ou pelo utilizador.
 * ========================================================================== */

#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include <stddef.h>

#include "educacao.h"

/** Indica se existe uma actividade educativa em curso. */
int atividadeAtiva(Educacao *e);

/** Devolve rótulo legível do modo de actividade actual. */
const char *nomeModoAtividade(Educacao *e);

/** Inicia actividade a partir de frase natural do utilizador. */
int iniciarAtividadePorPedido(Educacao *e, const char *frase, char *resposta, size_t tamanho);

/** Inicia actividade conforme nome da acção autónoma (Ensinar, Brincar, etc.). */
int iniciarAtividadePorAcao(Educacao *e, const char *nomeAcao, char *resposta, size_t tamanho);

/** Avança a actividade activa com base na resposta do utilizador. */
int continuarAtividade(Educacao *e, const char *frase, char *resposta, size_t tamanho);

#endif
