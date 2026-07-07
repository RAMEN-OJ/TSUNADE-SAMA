/* ==========================================================================
 * comportamento.h — Comportamento temporal da criança
 *
 * Simulação de passagem de tempo e comportamento proactivo da babá
 * virtual com sugestões de acção autónoma.
 * ========================================================================== */

#ifndef COMPORTAMENTO_H
#define COMPORTAMENTO_H

#include "../core/tsunade.h"

/** Decrementa energia e incrementa fome a cada ciclo temporal. */
void passarTempoCrianca(Tsunade *t);

/** Invoca sugestão de acção autónoma e anexa à resposta. */
void executarComportamentoBaba(Tsunade *t, char *resposta);

#endif
