#include <string.h>
#include <ctype.h>

#include "analisador.h"

Intencao analisarFrase(
        Vocabulario *v,
        const char *frase)
{
    char copia[256];

    strncpy(copia, frase, sizeof(copia)-1);

    copia[sizeof(copia)-1] = '\0';

    char *token =
        strtok(copia, " ,.!?;:\n");

    while(token != NULL)
    {
        for(int i = 0; token[i]; i++)
        {
            token[i] =
                tolower(token[i]);
        }

        Intencao i =
            interpretarPalavra(
                v,
                token);

        if(i != INTENCAO_DESCONHECIDA)
        {
            return i;
        }

        token =
            strtok(NULL,
                   " ,.!?;:\n");
    }

    return INTENCAO_DESCONHECIDA;
}
