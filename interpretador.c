#include <stdio.h>
#include <string.h>
#include "interpretador.h"
#include <ctype.h>

void paraMinusculas(char *dest, const char *orig)
{
    int i = 0;

    while(orig[i] != '\0')
    {
        dest[i] = tolower((unsigned char)orig[i]);
        i++;
    }

    dest[i] = '\0';
}

static int contem(const char *texto,
                  const char *palavra)
{
    return strstr(texto, palavra) != NULL;
}

Intencao interpretar(const char *frase)
{
    char texto[256];

    paraMinusculas(texto, frase);

    if(contem(texto, "ola") ||
       contem(texto, "oi"))
    {
        return INTENCAO_SAUDACAO;
    }

    if(contem(texto, "historia"))
    {
        return INTENCAO_HISTORIA;
    }

    if(contem(texto, "matematica") ||
       contem(texto, "estudar"))
    {
        return INTENCAO_ESTUDO;
    }

    if(contem(texto, "jogo") ||
       contem(texto, "jogar"))
    {
        return INTENCAO_JOGO;
    }

    if(contem(texto, "triste") ||
       contem(texto, "feliz"))
    {
        return INTENCAO_EMOCIONAL;
    }

    if(contem(texto, "ajuda"))
    {
        return INTENCAO_AJUDA;
    }

    if(contem(texto, "adeus") ||
       contem(texto, "tchau"))
    {
        return INTENCAO_DESPEDIDA;
    }

    return INTENCAO_DESCONHECIDA;
}

const char *nomeIntencao(Intencao i)
{
    switch(i)
    {
        case INTENCAO_SAUDACAO:
            return "SAUDACAO";

        case INTENCAO_HISTORIA:
            return "HISTORIA";

        case INTENCAO_ESTUDO:
            return "ESTUDO";

        case INTENCAO_JOGO:
            return "JOGO";

        case INTENCAO_EMOCIONAL:
            return "EMOCIONAL";

        case INTENCAO_AJUDA:
            return "AJUDA";

        case INTENCAO_DESPEDIDA:
            return "DESPEDIDA";

        default:
            return "DESCONHECIDA";
    }
}
