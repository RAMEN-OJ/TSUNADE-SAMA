/*======================================================================
  main.c
  Ponto de entrada da aplicação Tsunade-Sama.
  Inicializa a interface, cria a instância e executa o ciclo principal.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/tsunade.h"
#include "core/motor.h"
#include "interface/ui.h"

/* Função principal: inicializa UI e Tsunade, corre o ciclo de interação até sair; retorna 0 */
int main(void)
{
    Tsunade *t;

    /* --- inicialização --- */
    ui_inicializar();
    srand((unsigned)time(NULL));

    t = criarTsunade();
    apresentarTsunade(t);

    /* --- ciclo principal --- */
    while(t->ativa)
    {
        executarCiclo(t);
    }

    /* --- encerramento --- */
    destruirTsunade(t);

    return 0;
}
