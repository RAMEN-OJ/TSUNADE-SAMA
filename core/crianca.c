/*======================================================================
  crianca.c
  Registo de interações no perfil da criança.
  Atualiza atributos (energia, humor, curiosidade) conforme ações e intenções.
======================================================================*/

#include <stddef.h>
#include <string.h>

#include "crianca.h"

/* Garante que todos os atributos numéricos do perfil ficam entre 0 e 100; parâmetro: p */
static void limitarValores(PerfilCrianca *p)
{
    if(p->energia < 0)
        p->energia = 0;
    if(p->energia > 100)
        p->energia = 100;
    if(p->humor < 0)
        p->humor = 0;
    if(p->humor > 100)
        p->humor = 100;
    if(p->curiosidade < 0)
        p->curiosidade = 0;
    if(p->curiosidade > 100)
        p->curiosidade = 100;
    if(p->atencao < 0)
        p->atencao = 0;
    if(p->atencao > 100)
        p->atencao = 100;
    if(p->fome < 0)
        p->fome = 0;
    if(p->fome > 100)
        p->fome = 100;
}

/* Regista interação no perfil, ajustando contadores e atributos; parâmetros: p, acao, intencao */
void registrarInteracao(PerfilCrianca *p, TipoAcao acao, Intencao intencao)
{
    if(p == NULL)
        return;

    p->totalConversas++;

    /* --- efeitos por tipo de ação --- */
    switch(acao)
    {
        case ACAO_ESTUDO:
            p->energia -= 5;
            p->curiosidade += 4;
            p->atencao += 2;
            p->tempoEstudo++;
            break;

        case ACAO_JOGO:
            p->energia -= 3;
            p->humor += 8;
            p->tempoBrincadeira++;
            break;

        case ACAO_CONSULTA:
            p->curiosidade += 2;
            p->perguntasRespondidas++;
            break;

        case ACAO_CONHECIMENTO:
            p->conhecimentosAprendidos++;
            p->curiosidade += 3;
            break;

        case ACAO_INFERENCIA:
            p->perguntasRespondidas++;
            p->curiosidade += 2;
            break;

        case ACAO_PERFIL:
            p->curiosidade += 1;
            break;

        case ACAO_MEMORIA:
            p->perguntasRespondidas++;
            break;

        /* --- efeitos por intenção (ação desconhecida) --- */
        default:
            switch(intencao)
            {
                case INTENCAO_SAUDACAO:
                    p->humor += 2;
                    break;

                case INTENCAO_EMOCIONAL:
                    p->atencao += 1;
                    break;

                case INTENCAO_ESTUDO:
                    p->tempoEstudo++;
                    p->curiosidade += 2;
                    p->atencao += 1;
                    break;

                case INTENCAO_JOGO:
                    p->tempoBrincadeira++;
                    p->humor += 5;
                    p->energia -= 2;
                    break;

                case INTENCAO_HISTORIA:
                    break;

                case INTENCAO_AJUDA:
                    p->perguntasRespondidas++;
                    break;

                default:
                    break;
            }
            break;
    }

    limitarValores(p);
}
