#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conceitos.h"

BaseConhecimento *criarBaseConhecimento(void)
{
    BaseConhecimento *b =
        malloc(sizeof(BaseConhecimento));

    if(b == NULL)
        return NULL;

    b->quantidade = 0;

    return b;
}

void destruirBaseConhecimento(
        BaseConhecimento *b)
{
    free(b);
}

void adicionarRelacao(
        BaseConhecimento *b,
        const char *sujeito,
        const char *relacao,
        const char *objeto)
{
    for(int i = 0; i < b->quantidade; i++)
    {
        if(strcmp(
                b->lista[i].sujeito,
                sujeito) == 0 &&
           strcmp(
                b->lista[i].relacao,
                relacao) == 0)
        {
            strcpy(
                b->lista[i].objeto,
                objeto);

            return;
        }
    }

    if(b->quantidade >= MAX_CONCEITOS)
        return;

    strcpy(
        b->lista[b->quantidade].sujeito,
        sujeito);

    strcpy(
        b->lista[b->quantidade].relacao,
        relacao);

    strcpy(
        b->lista[b->quantidade].objeto,
        objeto);

    b->quantidade++;
}

void salvarConhecimento(
        BaseConhecimento *b)
{
    FILE *f =
        fopen(
            "dados/conhecimento.dat",
            "w");

    if(f == NULL)
        return;

    for(int i = 0;
        i < b->quantidade;
        i++)
    {
        fprintf(
            f,
            "%s|%s|%s\n",
            b->lista[i].sujeito,
            b->lista[i].relacao,
            b->lista[i].objeto);
    }

    fclose(f);
}

void carregarConhecimento(
        BaseConhecimento *b)
{
    FILE *f =
        fopen(
            "dados/conhecimento.dat",
            "r");

    if(f == NULL)
        return;

    char linha[500];

    while(fgets(
            linha,
            sizeof(linha),
            f))
    {
        linha[
            strcspn(
                linha,
                "\n")] = '\0';

        char *sujeito =
            strtok(
                linha,
                "|");

        char *relacao =
            strtok(
                NULL,
                "|");

        char *objeto =
            strtok(
                NULL,
                "|");

        if(sujeito &&
           relacao &&
           objeto)
        {
            adicionarRelacao(
                b,
                sujeito,
                relacao,
                objeto);
        }
    }

    fclose(f);
}
