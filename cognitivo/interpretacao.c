#include <string.h>

#include "interpretacao.h"

void limparInterpretacao(Interpretacao *i)
{
    if(i == NULL)
        return;

    i->tipo = ACAO_DESCONHECIDA;

    i->sujeito[0] = '\0';
    i->relacao[0] = '\0';
    i->objeto[0] = '\0';
}