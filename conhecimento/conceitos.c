#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conceitos.h"

static NoSemantico *buscarNoSemantico(
        BaseConhecimento *b,
        const char *conceito)
{
    return (NoSemantico *)
            procurarHash(
                b->indice,
                conceito);
}

static NoSemantico *criarNoSemantico(
        BaseConhecimento *b,
        const char *conceito)
{
    NoSemantico *novo =
        malloc(sizeof(NoSemantico));

    if(novo==NULL)
        return NULL;

    strcpy(
        novo->conceito,
        conceito);

    novo->adjacentes = NULL;

    novo->proximo = b->grafo;

    b->grafo = novo;

    inserirHash(
            b->indice,
            conceito,
            novo);

    return novo;
}

static void adicionarVizinho(
        NoSemantico *origem,
        const char *relacao,
        const char *destino)
{
    Vizinho *v =
        malloc(sizeof(Vizinho));

    if(v==NULL)
        return;

    strcpy(v->relacao,relacao);

    strcpy(v->destino,destino);

    v->proximo =
        origem->adjacentes;

    origem->adjacentes = v;
}

BaseConhecimento *criarBaseConhecimento(void)
{
    BaseConhecimento *b =
        malloc(sizeof(BaseConhecimento));

    if(b == NULL)
        return NULL;

    b->quantidade = 0;

    b->indice = criarHash();
    b->grafo = NULL;
    return b;
}

void destruirBaseConhecimento(
        BaseConhecimento *b)
{
    destruirHash(b->indice);

    free(b);
}

void adicionarRelacao(
        BaseConhecimento *b,
        const char *sujeito,
        const char *relacao,
        const char *objeto)
{
    for(int i=0;i<b->quantidade;i++)
    {
        if(strcmp(
                b->lista[i].sujeito,
                sujeito)==0 &&
           strcmp(
                b->lista[i].relacao,
                relacao)==0)
        {
            strcpy(
                b->lista[i].objeto,
                objeto);

            return;
        }
    }

    if(b->quantidade>=MAX_CONCEITOS)
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

    NoSemantico *origem =
        buscarNoSemantico(
                b,
                sujeito);

if(origem==NULL)
{
    origem =
        criarNoSemantico(
                b,
                sujeito);
}

adicionarVizinho(
        origem,
        relacao,
        objeto);
}

Relacao *procurarRelacao(
        BaseConhecimento *b,
        const char *sujeito)
{
    NoSemantico *no =
        procurarHash(
                b->indice,
                sujeito);

    if(no == NULL)
        return NULL;

    for(int i = 0; i < b->quantidade; i++)
    {
        if(strcmp(
                b->lista[i].sujeito,
                sujeito) == 0)
        {
            return &b->lista[i];
        }
    }

    return NULL;
}
void salvarConhecimento(
        BaseConhecimento *b)
{
    FILE *f =
        fopen(
            "dados/conhecimento.dat",
            "w");

    if(f==NULL)
        return;

    for(int i=0;i<b->quantidade;i++)
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

    if(f==NULL)
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
    void imprimirGrafo(
        BaseConhecimento *b)
{
    printf("\n========== GRAFO ==========\n");

    NoSemantico *n = b->grafo;

    while(n)
    {
        printf("%s\n", n->conceito);

        Vizinho *v = n->adjacentes;

        while(v)
        {
            printf("   |--%s--> %s\n",
                   v->relacao,
                   v->destino);

            v = v->proximo;
        }

        printf("\n");

        n = n->proximo;
    }

    printf("===========================\n");
}

NoSemantico *procurarNoSemantico(
        BaseConhecimento *b,
        const char *conceito)
{
    return (NoSemantico *)
            procurarHash(
                    b->indice,
                    conceito);
}