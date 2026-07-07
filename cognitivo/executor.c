/*======================================================================
  executor.c
  Executor de ações cognitivas por tipo de interpretação.
  Despacha cada TipoAcao para o módulo especializado correspondente.
======================================================================*/

#include <string.h>

#include "executor.h"
#include "inferencia.h"
#include "aprendizagem.h"
#include "consulta.h"
#include "memoria_busca.h"
#include "../educacao/educacao.h"
#include "../conhecimento/conceitos.h"

/* Executa ações de perfil: aprende ou responde consulta; retorna 1 se tratou */
static int executarPerfil(Tsunade *t, const char *frase, char *resposta)
{
    if(aprenderPerfil(t->perfil, frase, resposta))
        return 1;

    return responderConsulta(t->perfil, frase, resposta);
}

/* Executa ações de conhecimento: aprende relação ou infere; retorna 1 se tratou */
static int executarConhecimento(Tsunade *t, const char *frase, char *resposta)
{
    if(aprenderConhecimento(t->conhecimento, frase, resposta))
    {
        salvarConhecimento(t->conhecimento);
        return 1;
    }

    return executarInferencia(t->conhecimento, frase, resposta);
}

/* Executa consultas: perfil, conhecimento ou memória episódica; retorna 1 se respondeu */
static int executarConsulta(Tsunade *t, const char *frase, char *resposta)
{
    if(responderConsulta(t->perfil, frase, resposta))
        return 1;

    if(pesquisarConhecimento(t->conhecimento, frase, resposta))
        return 1;

    return buscarMemoria(t->episodios, frase, resposta);
}

/* Executa busca na memória episódica; retorna 1 se encontrou */
static int executarMemoria(Tsunade *t, const char *frase, char *resposta)
{
    return buscarMemoria(t->episodios, frase, resposta);
}

/* Executa resposta educativa (estudo/cálculo); retorna 1 se respondeu */
static int executarEstudo(Tsunade *t, const char *frase, char *resposta)
{
    return responderEducacao(t->educacao, frase, resposta);
}

/* Despacha interpretação para handler conforme tipo de ação; retorna 1 se executou */
int executarInterpretacao(Tsunade *t, Interpretacao *i, const char *frase, char *resposta)
{
    switch(i->tipo)
    {
        case ACAO_PERFIL:
            return executarPerfil(t, frase, resposta);

        case ACAO_CONHECIMENTO:
            return executarConhecimento(t, frase, resposta);

        case ACAO_CONSULTA:
            return executarConsulta(t, frase, resposta);

        case ACAO_MEMORIA:
            return executarMemoria(t, frase, resposta);

        case ACAO_ESTUDO:
            return executarEstudo(t, frase, resposta);

        case ACAO_INFERENCIA:
            return executarInferencia(t->conhecimento, i->objeto, resposta);

        default:
            return 0;
    }
}
