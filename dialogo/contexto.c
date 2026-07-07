/* ==========================================================================
 * contexto.c — Contexto conversacional
 *
 * Gestão do ciclo de vida e actualização do contexto de diálogo,
 * incluindo rastreio de profundidade emocional entre mensagens.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contexto.h"

/**
 * Aloca e inicializa um contexto com intenção desconhecida e contadores zerados.
 */
Contexto *criarContexto(void)
{
    Contexto *c =
        malloc(sizeof(Contexto));

    c->ultimaIntencao =
        INTENCAO_DESCONHECIDA;

    c->mensagens = 0;

    c->profundidadeEmocional = 0;

    strcpy(c->ultimoAssunto,
           "nenhum");

    return c;
}

/**
 * Liberta a memória do contexto conversacional.
 */
void destruirContexto(Contexto *c)
{
    free(c);
}

/**
 * Actualiza intenção, assunto e profundidade emocional após cada mensagem.
 */
void atualizarContexto(Contexto *c, Intencao i, const char *frase)
{
    if(i == INTENCAO_EMOCIONAL)
    {
        if(c->ultimaIntencao == INTENCAO_EMOCIONAL)
        {
            if(c->profundidadeEmocional < 4)
                c->profundidadeEmocional++;
        }
        else
            c->profundidadeEmocional = 0;
    }
    else if(i != INTENCAO_DESCONHECIDA)
    {
        c->profundidadeEmocional = 0;
    }

    if(i != INTENCAO_DESCONHECIDA)
        c->ultimaIntencao = i;

    strncpy(c->ultimoAssunto, frase, sizeof(c->ultimoAssunto) - 1);
    c->ultimoAssunto[sizeof(c->ultimoAssunto) - 1] = '\0';

    c->mensagens++;
}

/**
 * Imprime resumo do contexto actual no ecrã.
 */
void mostrarContexto(Contexto *c)
{
    printf("\n");
    printf("===== CONTEXTO =====\n");
    printf("Mensagens: %d\n", c->mensagens);
    printf("Ultimo assunto: %s\n", c->ultimoAssunto);
    printf("====================\n");
}
