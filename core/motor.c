#include <stdio.h>
#include <string.h>

#include "motor.h"

#include "../cognitivo/motor_cognitivo.h"

void apresentarTsunade(Tsunade *t)
{
    printf("\n");
    printf("=================================\n");
    printf("        %s\n", t->nome);
    printf("=================================\n\n");

    if(strlen(t->perfil->nome) > 0)
    {
        printf("Tsunade: Olá %s!\n", t->perfil->nome);
        printf("Tsunade: Que bom ver-te novamente.\n");
    }
    else
    {
        printf("Tsunade: Olá!\n");
        printf("Tsunade: Estou pronta para aprender contigo.\n");
    }
}

void executarCiclo(Tsunade *t)
{
    char frase[256];
    char resposta[512];

    printf("\nTu: ");

    if(fgets(frase, sizeof(frase), stdin) == NULL)
        return;

    pensar(
        t,
        frase,
        resposta);

    printf("\nTsunade: %s\n", resposta);
}