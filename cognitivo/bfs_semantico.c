#include <string.h>

#include "../conhecimento/conceitos.h"

#include "bfs_semantico.h"

#define MAX_FILA 500

typedef struct
{
    NoSemantico *no;

    int pai;

} ItemFila;

typedef struct
{
    NoSemantico *no;

} NoFila;

int existeCaminho(
        BaseConhecimento *base,
        const char *origem,
        const char *destino)
{
    NoSemantico *inicio =
            procurarNoSemantico(
                    base,
                    origem);

    if(inicio == NULL)
        return 0;

    NoFila fila[MAX_FILA];

    int ini = 0;
    int fim = 0;

    NoSemantico *visitados[MAX_CONCEITOS];

    int qtdVisitados = 0;

    fila[fim++].no = inicio;

    while(ini < fim)
    {
        NoSemantico *atual =
                fila[ini++].no;

        if(strcmp(
                atual->conceito,
                destino)==0)
            return 1;

        int visitado = 0;

        for(int i=0;i<qtdVisitados;i++)
        {
            if(visitados[i]==atual)
            {
                visitado=1;
                break;
            }
        }

        if(visitado)
            continue;

        visitados[qtdVisitados++] = atual;

        Vizinho *v =
                atual->adjacentes;

        while(v)
        {
            NoSemantico *prox =
                    procurarNoSemantico(
                            base,
                            v->destino);

            if(prox)
            {
                fila[fim++].no = prox;
            }

            v = v->proximo;
        }
    }

    return 0;
}

int encontrarCaminho(
        BaseConhecimento *b,
        const char *origem,
        const char *destino,
        char caminho[][100],
        int *quantidade)
{
    ItemFila fila[500];

    int inicio=0;
    int fim=0;

    NoSemantico *raiz =
        procurarNoSemantico(
                b,
                origem);

    if(raiz==NULL)
        return 0;

    fila[fim].no = raiz;
    fila[fim].pai = -1;
    fim++;

    while(inicio<fim)
    {
        ItemFila atual =
            fila[inicio];

        if(strcmp(
                atual.no->conceito,
                destino)==0)
        {
            int pilha[500];
            int n=0;

            int p=inicio;

            while(p!=-1)
            {
                pilha[n++]=p;
                p=fila[p].pai;
            }

            *quantidade=0;

            for(int i=n-1;i>=0;i--)
            {
                strcpy(
                    caminho[*quantidade],
                    fila[pilha[i]].no->conceito);

                (*quantidade)++;
            }

            return 1;
        }

        Vizinho *v =
            atual.no->adjacentes;

        while(v)
        {
            NoSemantico *prox =
                procurarNoSemantico(
                        b,
                        v->destino);

            if(prox)
            {
                fila[fim].no = prox;
                fila[fim].pai = inicio;
                fim++;
            }

            v=v->proximo;
        }

        inicio++;
    }

    return 0;
}