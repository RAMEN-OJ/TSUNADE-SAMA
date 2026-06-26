#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contexto.h"

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

void destruirContexto(
        Contexto *c)
{
    free(c);
}

void atualizarContexto(
        Contexto *c,
        Intencao i,
        const char *frase)
{
    /* GestÃÂ£o da profundidade emocional */

    if(i == INTENCAO_EMOCIONAL)
    {
        c->profundidadeEmocional++;
    }
    else if(i != INTENCAO_DESCONHECIDA)
    {
        c->profundidadeEmocional = 0;
    }

    /* SÃÂ³ atualiza a intenÃÂ§ÃÂ£o se nÃÂ£o for desconhecida */

    if(i != INTENCAO_DESCONHECIDA)
    {
        c->ultimaIntencao = i;
    }

    strncpy(
        c->ultimoAssunto,
        frase,
        sizeof(c->ultimoAssunto)-1);

    c->ultimoAssunto[
        sizeof(c->ultimoAssunto)-1]
        = '\0';

    c->mensagens++;
}

void mostrarContexto(
        Contexto *c)
{
    printf("\n");
    printf("===== CONTEXTO =====\n");

    printf(
        "Mensagens: %d\n",
        c->mensagens);

    printf(
        "Ultimo assunto: %s\n",
        c->ultimoAssunto);

    printf("====================\n");
}
