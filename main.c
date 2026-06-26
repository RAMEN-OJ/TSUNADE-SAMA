#include "core/tsunade.h"
#include "core/motor.h"

int main(void)
{
    Tsunade *t = criarTsunade();

    apresentarTsunade(t);

    while(t->ativa)
    {
        executarCiclo(t);
    }

    destruirTsunade(t);

    return 0;
}