#include <string.h>

#include "executor.h"

#include "inferencia.h"
#include "aprendizagem.h"

#include "consulta.h"

#include "inferencia.h"

#include "memoria_busca.h"

#include "../educacao/educacao.h"

/*=========================================================
                    PERFIL
=========================================================*/

static int executarPerfil(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    if(aprenderPerfil(
            t->perfil,
            frase,
            resposta))
    {
        salvarPerfil(t->perfil);
        return 1;
    }

    return responderConsulta(
            t->perfil,
            frase,
            resposta);
}

/*=========================================================
                CONHECIMENTO
=========================================================*/

static int executarConhecimento(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    if(aprenderConhecimento(
            t->conhecimento,
            frase,
            resposta))
    {
        salvarConhecimento(
                t->conhecimento);

        return 1;
    }

    return executarInferencia(
            t->conhecimento,
            frase,
            resposta);
}

/*=========================================================
                    CONSULTA
=========================================================*/

static int executarConsulta(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    if(pesquisarConhecimento(
            t->conhecimento,
            frase,
            resposta))
        return 1;

    return buscarMemoria(
            t->episodios,
            frase,
            resposta);
}

/*=========================================================
                    MEMÓRIA
=========================================================*/

static int executarMemoria(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    return buscarMemoria(
            t->episodios,
            frase,
            resposta);
}

/*=========================================================
                    EDUCAÇÃO
=========================================================*/

static int executarEstudo(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    return responderEducacao(
            t->educacao,
            frase,
            resposta);
}

int executarInterpretacao(
        Tsunade *t,
        Interpretacao *i,
        const char *frase,
        char *resposta)
{
   switch(i->tipo)
{
    case ACAO_PERFIL:
        return executarPerfil(
                t,
                frase,
                resposta);

    case ACAO_CONHECIMENTO:
        return executarConhecimento(
                t,
                frase,
                resposta);

    case ACAO_CONSULTA:
        return executarConsulta(
                t,
                frase,
                resposta);

    case ACAO_MEMORIA:
        return executarMemoria(
                t,
                frase,
                resposta);

    case ACAO_ESTUDO:
        return executarEstudo(
                t,
                frase,
                resposta);

    case ACAO_INFERENCIA:
        return executarInferencia(
                t->conhecimento,
                i->objeto,
                resposta);

    default:
        return 0;
}
}