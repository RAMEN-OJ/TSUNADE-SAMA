/* ==========================================================================
 * gestor_emocional.c — Gestor de eventos emocionais
 *
 * Traduz eventos de interacção em transições de estado emocional
 * usando o grafo de emoções da Tsunade.
 * ========================================================================== */

#include "gestor_emocional.h"
#include <stddef.h>

/**
 * Despacha evento para a transição emocional correspondente no grafo.
 */
void processarEventoEmocional(Emocoes *e, EventoEmocional evento)
{
    if(e == NULL)
        return;

    switch(evento)
    {
        case EVENTO_APRENDEU:
            avancarEmocao(e, ORGULHOSA);
            break;

        case EVENTO_PERGUNTA:
            avancarEmocao(e, CURIOSA);
            break;

        case EVENTO_BRINCADEIRA:
            avancarEmocao(e, BRINCALHONA);
            break;

        case EVENTO_ERRO:
            avancarEmocao(e, PREOCUPADA);
            break;

        case EVENTO_ELOGIO:
            avancarEmocao(e, FELIZ);
            break;

        default:
            avancarEmocao(e, FELIZ);
            break;
    }
}
