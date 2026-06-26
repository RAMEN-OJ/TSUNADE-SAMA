#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "educacao.h"

Educacao *criarEducacao(void)
{
    Educacao *e =
        malloc(sizeof(Educacao));

    if(e == NULL)
        return NULL;

    e->licaoAtual = LICAO_NENHUMA;

    e->etapa = 0;

    e->pontuacao = 0;

    e->ativa = 0;

    return e;
}

void destruirEducacao(
        Educacao *e)
{
    free(e);
}

void iniciarLicao(
        Educacao *e,
        TipoLicao tipo)
{
    e->licaoAtual = tipo;

    e->etapa = 0;

    e->pontuacao = 0;

    e->ativa = 1;
}

int responderEducacao(
        Educacao *e,
        const char *frase,
        char *resposta)
{
    if(e == NULL)
        return 0;

    (void)frase;

    if(!e->ativa)
        return 0;

    switch(e->licaoAtual)
    {
        case LICAO_ANIMAIS:

            if(e->etapa == 0)
            {
                sprintf(
                    resposta,
                    "Hoje vamos aprender os animais! Sabes o que é um leão?");

                e->etapa++;

                return 1;
            }

            if(e->etapa == 1)
            {
                sprintf(
                    resposta,
                    "Muito bem! O leão é conhecido como o rei da selva.");

                e->ativa = 0;

                return 1;
            }

            break;

        default:
            break;
    }

    return 0;
}