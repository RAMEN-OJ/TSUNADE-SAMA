/*======================================================================
  interpretacao.c
  Funções utilitárias para a estrutura de interpretação sintática.
  Reinicializa campos da Interpretacao para valores vazios.
======================================================================*/

#include <string.h>

#include "interpretacao.h"

/* Reinicializa estrutura de interpretação com tipo desconhecido e strings vazias; parâmetro: i */
void limparInterpretacao(Interpretacao *i)
{
    if(i == NULL)
        return;

    i->tipo = ACAO_DESCONHECIDA;

    i->sujeito[0] = '\0';
    i->relacao[0] = '\0';
    i->objeto[0] = '\0';
}
