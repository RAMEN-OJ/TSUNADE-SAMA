#include <stdio.h>
#include <string.h>
#include "core/tsunade.h"
#include "core/motor.h"
#include "cognitivo/bfs_semantico.h"
#include "cognitivo/inferencia.h"
int main(void)
{
    Tsunade *t = criarTsunade();

    apresentarTsunade(t);
    imprimirGrafo(
        t->conhecimento);

    printf("\n=== TESTE BFS ===\n");

    char caminho[100][100];
int qtd;

if(encontrarCaminho(
        t->conhecimento,
        "Angola",
        "Africa",
        caminho,
        &qtd))
{
    printf("\nCAMINHO:\n");

    for(int i=0;i<qtd;i++)
    {
        printf("%s\n",caminho[i]);
    }
}


    printf("=================\n\n");

    while(t->ativa)
    {
        executarCiclo(t);
    }

    destruirTsunade(t);

    return 0;
}