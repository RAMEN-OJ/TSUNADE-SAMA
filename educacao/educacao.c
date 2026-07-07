/* ==========================================================================
 * educacao.c — Módulo educativo (lições estruturadas)
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "educacao.h"
#include "licoes_data.h"

Educacao *criarEducacao(void)
{
    Educacao *e = malloc(sizeof(Educacao));

    if(e == NULL)
        return NULL;

    e->licaoAtual = LICAO_NENHUMA;
    e->modo = MODO_LIVRE;
    e->conteudoId = 0;
    e->etapa = 0;
    e->pontuacao = 0;
    e->ativa = 0;

    return e;
}

void destruirEducacao(Educacao *e)
{
    free(e);
}

void iniciarLicao(Educacao *e, TipoLicao tipo)
{
    e->licaoAtual = tipo;
    e->modo = MODO_LICAO;
    e->conteudoId = (int)tipo;
    e->etapa = 0;
    e->pontuacao = 0;
    e->ativa = 1;
}

static int respostaContemLista(const char *frase, const char *lista)
{
    char copiaFrase[256];
    char copiaLista[256];
    char *token;
    size_t i;

    if(frase == NULL || lista == NULL)
        return 0;

    for(i = 0; frase[i] != '\0' && i < sizeof(copiaFrase) - 1; i++)
        copiaFrase[i] = (char)tolower((unsigned char)frase[i]);
    copiaFrase[i] = '\0';

    strncpy(copiaLista, lista, sizeof(copiaLista) - 1);
    copiaLista[sizeof(copiaLista) - 1] = '\0';

    token = strtok(copiaLista, "|");
    while(token != NULL)
    {
        if(strstr(copiaFrase, token) != NULL)
            return 1;
        token = strtok(NULL, "|");
    }

    return 0;
}

static void terminarAtividade(Educacao *e)
{
    e->ativa = 0;
    e->modo = MODO_LIVRE;
    e->etapa = 0;
}

int responderEducacao(Educacao *e, const char *frase, char *resposta)
{
    const DadosLicao *d;

    if(e == NULL || resposta == NULL)
        return 0;

    if(!e->ativa || e->modo != MODO_LICAO)
        return 0;

    d = obterDadosLicao(e->licaoAtual);
    if(d == NULL)
        return 0;

    if(e->etapa == 0)
    {
        snprintf(resposta, 512, "%s\n%s", d->intro, d->pergunta);
        e->etapa++;
        return 1;
    }

    if(e->etapa == 1)
    {
        if(frase != NULL && frase[0] != '\0' &&
           respostaContemLista(frase, d->palavrasCertas))
        {
            e->pontuacao++;
            snprintf(resposta, 512, "%s", d->feedbackOk);
        }
        else if(frase == NULL || frase[0] == '\0')
        {
            snprintf(resposta, 512, "%s\n%s", d->intro, d->pergunta);
            return 1;
        }
        else
        {
            snprintf(resposta, 512, "%s", d->feedbackErr);
        }

        terminarAtividade(e);
        return 1;
    }

    return 0;
}
