#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "memoria_busca.h"

int buscarMemoria(
        MemoriaEpisodica *m,
        const char *frase,
        char *resposta)
{
    char palavra[100];

    if(sscanf(
        frase,
        "o que sabes sobre %99s",
        palavra) != 1)
    {
        return 0;
    }

    palavra[
        strcspn(
            palavra,
            "?\n")] = '\0';

    strcpy(
        resposta,
        "Lembro-me de:\n");

    int encontrados = 0;

    for(int i = 0;
        i < m->quantidade;
        i++)
    {
        if(strstr(
            m->lista[i].texto,
            palavra))
        {
            strcat(
                resposta,
                "- ");

            strcat(
                resposta,
                m->lista[i].texto);

            encontrados++;
        }
    }

    if(encontrados == 0)
    {
        strcpy(
            resposta,
            "Nao me lembro de nada sobre isso.");

        return 1;
    }

    return 1;
}
