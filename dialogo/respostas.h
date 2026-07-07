/* ==========================================================================
 * respostas.h — Geração de respostas dialogais
 *
 * API para produzir respostas da Tsunade com base na intenção detectada,
 * no contexto conversacional e no perfil da criança.
 * ========================================================================== */

#ifndef RESPOSTAS_H
#define RESPOSTAS_H

#include <stddef.h>

#include "../cognitivo/interpretador.h"
#include "../memoria/perfil.h"
#include "../personalidade/emocoes.h"
#include "contexto.h"

/** Gera a resposta textual adequada à intenção e ao estado da conversa. */
const char *gerarResposta(Intencao i, Contexto *c, PerfilCrianca *perfil);

/** Adapta o tom da resposta ao estado emocional actual da Tsunade. */
void enriquecerComEmocao(Emocoes *emocoes, char *resposta, size_t tamanho);

#endif
