#include <stdio.h>
#include <string.h>

#include "motor_cognitivo.h"
#include "decisor.h"
#include "aprendizagem.h"
#include "consulta.h"
#include "executor.h"
#include "aprendizagem.h"
#include "memoria_busca.h"
#include "analisador.h"
#include "parser.h"
#include "interpretacao.h"

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
   Interpretacao inter;

interpretarFrase(
        frase,
        &inter);

    printf("\nTIPO = %d\n", inter.tipo);
    printf("SUJEITO = %s\n", inter.sujeito);
    printf("RELACAO = %s\n", inter.relacao);
    printf("OBJETO = %s\n\n", inter.objeto);

    registrarMemoria(
            t,
            frase);

    registrarEpisodio(
            t,
            frase);

    if(executarInterpretacao(
            t,
            &inter,
            frase,
            resposta))
    {
        return 1;
    }

    EventoEmocional evento =
        decidirEventoEmocional(
                t,
                frase,
                t->contexto->ultimaIntencao);

    processarEventoEmocional(
            t->emocao,
            evento);

    gerarRespostaDialogo(
            t,
            frase,
            resposta);

    return 1;
}
