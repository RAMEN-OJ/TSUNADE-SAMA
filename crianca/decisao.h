/* ==========================================================================
 * decisao.h — Decisão autónoma da criança virtual
 *
 * API para detectar necessidade de intervenção, executar acções
 * autónomas e sugerir acções com base no perfil e grafo de decisão.
 * ========================================================================== */

#ifndef DECISAO_H
#define DECISAO_H

#include "../core/tsunade.h"

/** Avalia se o perfil exige acção autónoma imediata. */
int precisaIntervencaoAutonoma(Tsunade *t);

/** Escolhe e executa a melhor acção autónoma, preenchendo resposta. */
int executarDecisao(Tsunade *t, char *resposta);

/** Acrescenta sugestão de acção à resposta se necessário. */
void sugerirAcao(Tsunade *t, char *resposta);

#endif
