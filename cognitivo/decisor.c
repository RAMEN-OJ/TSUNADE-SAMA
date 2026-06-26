#include <string.h>

#include "decisor.h"

EventoEmocional decidirEventoEmocional(
        Tsunade *t,
        const char *frase,
        Intencao intencao)
{
    (void)t;

    if(frase == NULL)
        return EVENTO_NEUTRO;

    /* Palavras têm prioridade */

    if(strstr(frase,"obrigado") != NULL)
        return EVENTO_ELOGIO;

    if(strstr(frase,"parabéns") != NULL)
        return EVENTO_ELOGIO;

    if(strstr(frase,"brincar") != NULL)
        return EVENTO_BRINCADEIRA;

    if(strstr(frase,"jogar") != NULL)
        return EVENTO_BRINCADEIRA;

    /* Depois usa a intenção */

    switch(intencao)
    {
        case INTENCAO_ESTUDO:
            return EVENTO_APRENDEU;

        case INTENCAO_AJUDA:
            return EVENTO_PERGUNTA;

        case INTENCAO_EMOCIONAL:
            return EVENTO_PERGUNTA;

        case INTENCAO_JOGO:
            return EVENTO_BRINCADEIRA;

        default:
            return EVENTO_NEUTRO;
    }
}