#include <string.h>

#include "inferencia.h"

#include "../conhecimento/conceitos.h"


/*=========================================================
    INFERÊNCIA LÓGICA
=========================================================*/
int inferirRelacao(
        BaseConhecimento *base,
        const char *origem,
        const char *destino)
{
    for(int i = 0; i < base->quantidade; i++)
    {
        if(strcmp(base->lista[i].sujeito, origem) == 0 &&
           strcmp(base->lista[i].relacao, "eh") == 0)
        {
            char intermediario[100];

            strcpy(
                intermediario,
                base->lista[i].objeto);

            for(int j = 0; j < base->quantidade; j++)
            {
                if(strcmp(
                        base->lista[j].sujeito,
                        intermediario) == 0 &&
                   strcmp(
                        base->lista[j].relacao,
                        "Ã©") == 0 &&
                   strcmp(
                        base->lista[j].objeto,
                        destino) == 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/*=========================================================
    HERANÇA SEMÂNTICA
=========================================================*/
int herdaPropriedade(
        BaseConhecimento *base,
        const char *conceito,
        const char *propriedade,
        char *origem)
{
    NoSemantico *no =
        procurarNoSemantico(
                base,
                conceito);

    if(no == NULL)
        return 0;

    Vizinho *v = no->adjacentes;

    while(v)
    {
        if(strcmp(
                v->relacao,
                propriedade) == 0)
        {
            strcpy(
                origem,
                v->destino);

            return 1;
        }

        v = v->proximo;
    }

    no = procurarNoSemantico(
            base,
            conceito);

    if(no == NULL)
        return 0;

    v = no->adjacentes;

    while(v)
    {
        if(strcmp(
                v->relacao,
                "eh") == 0)
        {
            if(herdaPropriedade(
                    base,
                    v->destino,
                    propriedade,
                    origem))
            {
                return 1;
            }
        }

        v = v->proximo;
    }

    return 0;
}

/*=========================================================
    RESPOSTAS
=========================================================*/
int responderInferencia(
        BaseConhecimento *base,
        const char *conceito,
        char *resposta)
{
    resposta[0]='\0';

    NoSemantico *no =
        procurarNoSemantico(
                base,
                conceito);

    if(no==NULL)
        return 0;

    sprintf(
        resposta,
        "Conhecimento sobre %s\n\n",
        no->conceito);

    Vizinho *v=no->adjacentes;

    int total=0;

    while(v)
    {
        strcat(resposta,"• ");

        strcat(resposta,v->relacao);

        strcat(resposta," ");

        strcat(resposta,v->destino);

        strcat(resposta,"\n");

        total++;

        v=v->proximo;
    }

    char buffer[50];

    sprintf(
        buffer,
        "\nTotal de relações: %d",
        total);

    strcat(
        resposta,
        buffer);

    return 1;
}

/*=========================================================
    PESQUISA GERAL
=========================================================*/

int pesquisarConhecimento(
        BaseConhecimento *base,
        const char *texto,
        char *resposta)
{
    resposta[0] = '\0';

    for(int i=0;i<base->quantidade;i++)
    {
        if(strstr(base->lista[i].sujeito,texto) ||
           strstr(base->lista[i].relacao,texto) ||
           strstr(base->lista[i].objeto,texto))
        {
            strcat(resposta,
                   base->lista[i].sujeito);

            strcat(resposta," ");

            strcat(resposta,
                   base->lista[i].relacao);

            strcat(resposta," ");

            strcat(resposta,
                   base->lista[i].objeto);

            strcat(resposta,"\n");
        }
    }

    return resposta[0]!='\0';
}


/*=========================================================
    INFERÊNCIA COMPLETA
=========================================================*/

int executarInferencia(
        BaseConhecimento *base,
        const char *frase,
        char *resposta)
{
    if(responderInferencia(
            base,
            frase,
            resposta))
        return 1;

    if(pesquisarConhecimento(
            base,
            frase,
            resposta))
        return 1;

    return 0;
}