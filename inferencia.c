#include <string.h>

#include "inferencia.h"

int inferirRelacao(
        BaseConhecimento *base,
        const char *origem,
        const char *destino)
{
    for(int i = 0; i < base->quantidade; i++)
    {
        if(strcmp(base->lista[i].sujeito, origem) == 0 &&
           strcmp(base->lista[i].relacao, "Ã©") == 0)
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