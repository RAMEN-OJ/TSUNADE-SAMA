/* ==========================================================================
 * comportamento.c — Comportamento temporal da criança
 *
 * Efeitos da passagem de tempo no perfil e integração com o módulo
 * de decisão autónoma para sugestões proactivas.
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

#include "comportamento.h"
#include "decisao.h"

/**
 * Simula passagem de tempo: reduz energia e aumenta fome gradualmente.
 */
void passarTempoCrianca(Tsunade *t)
{
    if(t == NULL || t->perfil == NULL)
        return;

    if(t->perfil->energia > 0)
        t->perfil->energia--;

    if(t->perfil->fome < 100)
        t->perfil->fome++;
}

/**
 * Executa comportamento proactivo da babá anexando sugestão à resposta.
 */
void executarComportamentoBaba(Tsunade *t, char *resposta)
{
    if(t == NULL || resposta == NULL)
        return;

    sugerirAcao(t, resposta);
}
