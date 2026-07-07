/*======================================================================
  analisador.c
  Analisador de intenções dialogais por vocabulário.
  Tokeniza frases e seleciona a intenção de maior prioridade.
======================================================================*/

#include <string.h>
#include <ctype.h>
#include <stddef.h>

#include "analisador.h"

/* Devolve valor de prioridade numérica para desempate entre intenções; parâmetro: i */
static int prioridadeIntencao(Intencao i)
{
    switch(i)
    {
        case INTENCAO_EMOCIONAL:  return 10;
        case INTENCAO_DESPEDIDA:  return 9;
        case INTENCAO_SAUDACAO:   return 8;
        case INTENCAO_AJUDA:      return 6;
        case INTENCAO_HISTORIA:   return 5;
        case INTENCAO_ESTUDO:     return 5;
        case INTENCAO_JOGO:       return 5;
        default:                  return 0;
    }
}

/* Analisa frase token a token e devolve intenção de maior prioridade; parâmetros: v, frase */
Intencao analisarFrase(Vocabulario *v, const char *frase)
{
    char copia[256];
    Intencao melhor = INTENCAO_DESCONHECIDA;
    int melhorPrioridade = -1;
    char *token;

    strncpy(copia, frase, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    token = strtok(copia, " ,.!?;:\n");

    /* --- análise por token --- */
    while(token != NULL)
    {
        size_t j;

        for(j = 0; token[j]; j++)
            token[j] = (char)tolower((unsigned char)token[j]);

        {
            Intencao i = interpretarPalavra(v, token);
            int prio = prioridadeIntencao(i);

            if(i != INTENCAO_DESCONHECIDA && prio > melhorPrioridade)
            {
                melhor = i;
                melhorPrioridade = prio;
            }
        }

        token = strtok(NULL, " ,.!?;:\n");
    }

    return melhor;
}
