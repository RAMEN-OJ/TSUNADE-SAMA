#include <stdio.h>
#include <stdlib.h>

#include "emocoes.h"

Emocoes *criarEmocoes(void)
{
    Emocoes *e =
        malloc(sizeof(Emocoes));

    if(e==NULL)
    {
        printf("Erro ao criar emoções.\n");
        exit(1);
    }

    e->estado = FELIZ;

    e->energia = 100;

    e->curiosidade = 80;

    e->empatia = 90;

    e->grafo =
        criarGrafoEmocoes();

    return e;
}

void destruirEmocoes(
        Emocoes *e)
{
    if(e==NULL)
        return;

    destruirGrafoEmocoes(
            e->grafo);

    free(e);
}

void mudarEstado(
        Emocoes *e,
        EstadoEmocional novo)
{
    if(e==NULL)
        return;

    e->estado=novo;
}

void avancarEmocao(
        Emocoes *e,
        int escolha)
{
    if(e==NULL)
        return;

    e->estado =
        proximoEstado(
                e->grafo,
                e->estado,
                escolha);
}

const char *nomeEstado(
        EstadoEmocional estado)
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

void mostrarEmocoes(
        Emocoes *e)
{
    if(e==NULL)
        return;

    printf("\n");

    printf("========== EMOÇÕES ==========\n");

    printf("Estado       : %s\n",
           nomeEstado(e->estado));

    printf("Energia      : %d\n",
           e->energia);

    printf("Curiosidade  : %d\n",
           e->curiosidade);

    printf("Empatia      : %d\n",
           e->empatia);

    printf("=============================\n");
}