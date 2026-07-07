/*======================================================================
  decisor.c
  Decisor de eventos emocionais a partir de frases e intenções.
  Mapeia padrões textuais para eventos do gestor emocional.
======================================================================*/

#include <string.h>
#include <ctype.h>
#include <stddef.h>

#include "decisor.h"

/* Verifica se frase contém palavra (case-insensitive); retorna 1 se encontrou */
static int contem(const char *frase, const char *palavra)
{
    char copia[256];
    char alvo[64];
    size_t i;

    if(frase == NULL || palavra == NULL)
        return 0;

    for(i = 0; frase[i] != '\0' && i < sizeof(copia) - 1; i++)
        copia[i] = (char)tolower((unsigned char)frase[i]);
    copia[i] = '\0';

    for(i = 0; palavra[i] != '\0' && i < sizeof(alvo) - 1; i++)
        alvo[i] = (char)tolower((unsigned char)palavra[i]);
    alvo[i] = '\0';

    return strstr(copia, alvo) != NULL;
}

/* Decide evento emocional com base na frase e intenção; retorna EventoEmocional */
EventoEmocional decidirEventoEmocional(Tsunade *t, const char *frase, Intencao intencao)
{
    (void)t;

    if(frase == NULL)
        return EVENTO_NEUTRO;

    /* --- elogios e parabéns --- */
    if(contem(frase, "obrigad") || contem(frase, "parabens") || contem(frase, "parabéns"))
        return EVENTO_ELOGIO;

    /* --- brincadeira --- */
    if(contem(frase, "brincar") || contem(frase, "jogar"))
        return EVENTO_BRINCADEIRA;

    /* --- emoções expressas --- */
    if(intencao == INTENCAO_EMOCIONAL)
    {
        if(contem(frase, "feliz") || contem(frase, "alegre") || contem(frase, "orgulhos"))
            return EVENTO_ELOGIO;

        return EVENTO_PERGUNTA;
    }

    /* --- mapeamento por intenção --- */
    switch(intencao)
    {
        case INTENCAO_ESTUDO:
            return EVENTO_APRENDEU;

        case INTENCAO_AJUDA:
            return EVENTO_PERGUNTA;

        case INTENCAO_JOGO:
            return EVENTO_BRINCADEIRA;

        default:
            return EVENTO_NEUTRO;
    }
}
