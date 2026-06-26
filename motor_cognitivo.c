#include <stdio.h>
#include <string.h>

#include "motor_cognitivo.h"
#include "decisor.h"
#include "aprendizagem.h"
#include "consulta.h"
#include "aprendizagem_conhecimento.h"
#include "consulta_conhecimento.h"
#include "memoria_busca.h"
#include "analisador.h"

#include "../personalidade/gestor_emocional.h"
#include "../dialogo/respostas.h"

/*======================================================
                MEMÓRIA IMEDIATA
======================================================*/

static void registrarMemoria(
        Tsunade *t,
        const char *frase)
{
    adicionarMensagem(
            t->memoria,
            frase);
}

/*======================================================
                MEMÓRIA EPISÓDICA
======================================================*/

static void registrarEpisodio(
        Tsunade *t,
        const char *frase)
{
    if(strstr(frase,"o que te contei"))
        return;

    if(strstr(frase,"qual é"))
        return;

    if(strstr(frase,"qual e"))
        return;

    adicionarEpisodio(
            t->episodios,
            frase);

    salvarEpisodios(
            t->episodios);
}

/*======================================================
                PERFIL
======================================================*/

static int processarPerfil(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    if(responderConsulta(
            t->perfil,
            frase,
            resposta))
        return 1;

    if(aprenderPerfil(
            t->perfil,
            frase,
            resposta))
    {
        salvarPerfil(
                t->perfil);

        return 1;
    }

    return 0;
}

/*======================================================
                MEMÓRIA
======================================================*/

static int processarMemoria(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    return buscarMemoria(
            t->episodios,
            frase,
            resposta);
}

/*======================================================
                CONHECIMENTO
======================================================*/

static int processarConhecimento(
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

   printf("ANTES consultarConhecimento\n");

int r = consultarConhecimento(
            t->conhecimento,
            frase,
            resposta);

printf("DEPOIS consultarConhecimento\n");

if(r)
{
    return 1;
}

    return 0;
}

/*======================================================
                EDUCAÇÃO
======================================================*/

static int processarEducacao(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
        printf("educacao recebida = %p\n", (void *)e);
    return responderEducacao(
            t->educacao,
            frase,
            resposta);
}

/*======================================================
                DIÁLOGO
======================================================*/

static void gerarRespostaDialogo(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    Intencao i =
        analisarFrase(
                t->vocabulario,
                frase);

    atualizarContexto(
            t->contexto,
            i,
            frase);

    strcpy(
            resposta,
            gerarResposta(
                    i,
                    t->contexto));
}

/*======================================================
                CÉREBRO
======================================================*/

int pensar(
        Tsunade *t,
        const char *frase,
        char *resposta)
{
    registrarMemoria(
            t,
            frase);
printf("DEBUG 1\n");
    registrarEpisodio(
            t,
            frase);
printf("DEBUG 2\n");
    if(processarPerfil(
        t,
        frase,
        resposta))
{
    printf("DEBUG 3\n");
    return 1;
}

if(processarMemoria(
        t,
        frase,
        resposta))
{
    printf("DEBUG 4\n");
    return 1;
}

if(processarConhecimento(
        t,
        frase,
        resposta))
{
    printf("DEBUG 5\n");
    return 1;
}

printf("ANTES EDUCACAO\n");
int r = processarEducacao(
        t,
        frase,
        resposta);

printf("DEPOIS EDUCACAO\n");

if(r)
    return 1;

printf("DEBUG 7\n");

EventoEmocional evento =
    decidirEventoEmocional(
            t,
            frase,
            t->contexto->ultimaIntencao);

printf("DEBUG 8\n");

processarEventoEmocional(
        t->emocao,
        evento);

printf("DEBUG 9\n");

gerarRespostaDialogo(
        t,
        frase,
        resposta);

printf("DEBUG 10\n");
return 1;
    
}