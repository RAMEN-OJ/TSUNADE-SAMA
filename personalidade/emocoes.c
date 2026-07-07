/* ==========================================================================
 * emocoes.c — Estado emocional da Tsunade
 *
 * Ciclo de vida do estado emocional, transições via grafo e
 * visualização dos traços afectivos da Tsunade.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>

#include "emocoes.h"

/**
 * Aloca estado emocional inicial (feliz) com grafo padrão construído.
 */
Emocoes *criarEmocoes(void)
{
    Emocoes *e = malloc(sizeof(Emocoes));

    if(e==NULL)
    {
        printf("Erro ao criar emoções.\n");
        exit(1);
    }

    e->estado = FELIZ;

    e->energia = 100;

    e->curiosidade = 80;

    e->empatia = 90;

    e->grafo = criarGrafoEmocoes();

    return e;
}

/**
 * Liberta grafo emocional e estrutura de emoções.
 */
void destruirEmocoes(Emocoes *e)
{
    if(e==NULL)
        return;

    destruirGrafoEmocoes(e->grafo);

    free(e);
}

/**
 * Atribui directamente um novo estado emocional.
 */
void mudarEstado(Emocoes *e, EstadoEmocional novo)
{
    if(e==NULL)
        return;

    e->estado=novo;
}

/**
 * Transita para o estado vizinho indicado pelo índice no grafo.
 */
void avancarEmocao(Emocoes *e, int escolha)
{
    if(e==NULL)
        return;

    e->estado = proximoEstado(e->grafo, e->estado, escolha);
}

/**
 * Converte enum EstadoEmocional em string descritiva.
 */
const char *nomeEstado(EstadoEmocional estado)
{
    switch(estado)
    {
        case FELIZ:

            return "Feliz";

        case CURIOSA:

            return "Curiosa";

        case BRINCALHONA:

            return "Brincalhona";

        case ORGULHOSA:

            return "Orgulhosa";

        case PREOCUPADA:

            return "Preocupada";

        default:

            return "Desconhecido";
    }
}

/**
 * Imprime estado, energia, curiosidade e empatia no ecrã.
 */
void mostrarEmocoes(Emocoes *e)
{
    if(e==NULL)
        return;

    printf("\n");

    printf("========== EMOÇÕES ==========\n");

    printf("Estado       : %s\n", nomeEstado(e->estado));

    printf("Energia      : %d\n", e->energia);

    printf("Curiosidade  : %d\n", e->curiosidade);

    printf("Empatia      : %d\n", e->empatia);

    printf("=============================\n");
}
