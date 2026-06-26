#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "consulta_conhecimento.h"

int consultarConhecimento(
        BaseConhecimento *base,
        const char *frase,
        char *resposta)
{
    char copia[256];

    strcpy(copia, frase);

    copia[
        strcspn(
            copia,
            "\n")] = '\0';

    /* O QUE É */

    if(strstr(copia, "o que é "))
    {
        char *pos =
            strstr(
                copia,
                "o que é ");

        pos += 8;

        while(*pos == ' ')
            pos++;

        if(strncmp(pos, "um ", 3) == 0)
            pos += 3;

        if(strncmp(pos, "uma ", 4) == 0)
            pos += 4;

        char assunto[100];

        strcpy(
            assunto,
            pos);

        assunto[
            strcspn(
                assunto,
                "?")] = '\0';

        for(int i = 0;
            i < base->quantidade;
            i++)
        {
            if(strcmp(
                    base->lista[i].sujeito,
                    assunto) == 0)
            {
                sprintf(
                    resposta,
                    "%s %s %s.",
                    base->lista[i].sujeito,
                    base->lista[i].relacao,
                    base->lista[i].objeto);

                return 1;
            }
        }

        sprintf(
            resposta,
            "Ainda não sei o que é %s.",
            assunto);

        return 1;
    }

    /* ONDE FICA */

    if(strstr(copia, "onde fica "))
    {
        char *pos =
            strstr(
                copia,
                "onde fica ");

        pos += 10;

        char assunto[100];

        strcpy(
            assunto,
            pos);

        assunto[
            strcspn(
                assunto,
                "?")] = '\0';

        for(int i = 0;
            i < base->quantidade;
            i++)
        {
            if(strcmp(
                    base->lista[i].sujeito,
                    assunto) == 0 &&
               strcmp(
                    base->lista[i].relacao,
                    "fica em") == 0)
            {
                sprintf(
                    resposta,
                    "%s fica em %s.",
                    base->lista[i].sujeito,
                    base->lista[i].objeto);

                return 1;
            }
        }

        sprintf(
            resposta,
            "Ainda não sei onde fica %s.",
            assunto);

        return 1;
    }

    /* QUEM CRIOU */

    if(strstr(copia, "quem criou "))
    {
        char *pos =
            strstr(
                copia,
                "quem criou ");

        pos += 11;

        char assunto[100];

        strcpy(
            assunto,
            pos);

        assunto[
            strcspn(
                assunto,
                "?")] = '\0';

        for(int i = 0;
            i < base->quantidade;
            i++)
        {
            if(strcmp(
                    base->lista[i].sujeito,
                    assunto) == 0 &&
               strcmp(
                    base->lista[i].relacao,
                    "foi criado por") == 0)
            {
                sprintf(
                    resposta,
                    "%s foi criado por %s.",
                    base->lista[i].sujeito,
                    base->lista[i].objeto);

                return 1;
            }
        }

        sprintf(
            resposta,
            "Ainda não sei quem criou %s.",
            assunto);

        return 1;
    }

    return 0;
}
