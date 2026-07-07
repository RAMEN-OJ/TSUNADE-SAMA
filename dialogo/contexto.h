/* ==========================================================================
 * contexto.h — Contexto conversacional
 *
 * Mantém o estado da conversa actual: última intenção, assunto, contagem
 * de mensagens e profundidade emocional da troca dialogal.
 * ========================================================================== */

#ifndef CONTEXTO_H
#define CONTEXTO_H

#include "../cognitivo/interpretador.h"

/** Estado acumulado da sessão de diálogo corrente. */
typedef struct
{
    Intencao ultimaIntencao;

    char ultimoAssunto[100];

    int mensagens;
    int profundidadeEmocional;
} Contexto;

/** Cria um contexto conversacional com valores iniciais. */
Contexto *criarContexto(void);

/** Liberta a estrutura de contexto. */
void destruirContexto(Contexto *c);

/** Actualiza o contexto após cada turno de conversa. */
void atualizarContexto(Contexto *c, Intencao i, const char *frase);

/** Imprime o estado actual do contexto para diagnóstico. */
void mostrarContexto(Contexto *c);

#endif
