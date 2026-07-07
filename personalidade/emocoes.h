/* ==========================================================================
 * emocoes.h — Estado emocional da Tsunade
 *
 * Estrutura com estado emocional corrente, grafo de transições e
 * traços numéricos (energia, curiosidade, empatia).
 * ========================================================================== */

#ifndef EMOCOES_H
#define EMOCOES_H

#include "estado_emocional.h"
#include "grafo_emocoes.h"

/** Estado emocional completo da Tsunade com grafo de transições. */
typedef struct
{
    EstadoEmocional estado;

    GrafoEmocoes *grafo;

    int energia;
    int curiosidade;
    int empatia;

} Emocoes;

/** Cria estado emocional inicial com grafo padrão. */
Emocoes *criarEmocoes(void);

/** Liberta grafo emocional e estrutura. */
void destruirEmocoes(Emocoes *e);

/** Define directamente o estado emocional corrente. */
void mudarEstado(Emocoes *e, EstadoEmocional novo);

/** Avança estado emocional via transição indexada no grafo. */
void avancarEmocao(Emocoes *e, int escolha);

/** Imprime estado emocional actual para diagnóstico. */
void mostrarEmocoes(Emocoes *e);

/** Converte enum de estado em rótulo legível. */
const char *nomeEstado(EstadoEmocional estado);

#endif
