/*======================================================================
  motor_cognitivo.c
  Motor cognitivo central: orquestra interpretação, aprendizagem,
  consulta, inferência, memória e diálogo para gerar respostas.
======================================================================*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "motor_cognitivo.h"
#include "decisor.h"
#include "aprendizagem.h"
#include "consulta.h"
#include "executor.h"
#include "memoria_busca.h"
#include "analisador.h"
#include "interpretador.h"
#include "parser.h"
#include "interpretacao.h"
#include "inferencia.h"

#include "../core/crianca.h"
#include "../crianca/comportamento.h"
#include "../educacao/atividades.h"
#include "../personalidade/gestor_emocional.h"
#include "../dialogo/respostas.h"
#include "../conhecimento/grafo_inferencia.h"
#include "../memoria/perfil.h"
#include "../conhecimento/conceitos.h"

/* Regista frase na memória imediata (curto prazo); parâmetros: t, frase */
static void registrarMemoria(Tsunade *t, const char *frase)
{
    adicionarMensagem(t->memoria, frase);
}

/* Regista frase como episódio, ignorando perguntas reflexivas; parâmetros: t, frase */
static void registrarEpisodio(Tsunade *t, const char *frase)
{
    if(strstr(frase, "o que te contei"))
        return;

    if(strstr(frase, "qual é"))
        return;

    if(strstr(frase, "qual e"))
        return;

    adicionarEpisodio(t->episodios, frase);
    salvarEpisodios(t->episodios);
}

/* Gera resposta dialogal por intenção, atividades e contexto; retorna intenção detectada */
static Intencao gerarRespostaDialogo(Tsunade *t, const char *frase, char *resposta)
{
    Intencao i = analisarFrase(t->vocabulario, frase);

    atualizarContexto(t->contexto, i, frase);

    /* --- início de atividades educativas --- */
    if(!atividadeAtiva(t->educacao))
    {
        if(iniciarAtividadePorPedido(t->educacao, frase, resposta, 1024))
            return analisarFrase(t->vocabulario, frase);

        if(i == INTENCAO_HISTORIA &&
           iniciarAtividadePorAcao(t->educacao, "Contar história", resposta, 1024))
            return i;

        if(i == INTENCAO_ESTUDO &&
           iniciarAtividadePorAcao(t->educacao, "Ensinar", resposta, 1024))
            return i;

        if(i == INTENCAO_JOGO &&
           iniciarAtividadePorAcao(t->educacao, "Brincar", resposta, 1024))
            return i;
    }

    strcpy(resposta, gerarResposta(i, t->contexto, t->perfil));
    enriquecerComMemoria(t, frase, resposta, 1024);

    return i;
}

/* Determina tipo de ação de registo para frases de aprendizagem; retorna TipoAcao */
static TipoAcao acaoDeAprendizagem(const char *frase)
{
    char copia[256];
    int i;

    for(i = 0; frase[i] && i < (int)sizeof(copia) - 1; i++)
        copia[i] = (char)tolower((unsigned char)frase[i]);
    copia[i] = '\0';

    if(strstr(copia, "meu nome") || strstr(copia, "chamo") || strstr(copia, "sou o ") ||
       strstr(copia, "cor favorita") || strstr(copia, "animal favorito") ||
       strstr(copia, "comida favorita") ||
       (strstr(copia, "tenho") && strstr(copia, "anos")))
        return ACAO_PERFIL;

    return ACAO_CONHECIMENTO;
}

/* Processa frase completa: interpreta, aprende, consulta ou dialoga; retorna 1 se tratada */
int pensar(Tsunade *t, const char *frase, char *resposta)
{
    Interpretacao inter;
    Intencao intencao = INTENCAO_DESCONHECIDA;
    TipoAcao acaoRegisto = ACAO_DESCONHECIDA;
    int tratado = 0;

    if(t == NULL || frase == NULL || resposta == NULL)
        return 0;

    resposta[0] = '\0';

    /* --- pedidos directos: estudar, história, brincar --- */
    if(!atividadeAtiva(t->educacao) &&
       iniciarAtividadePorPedido(t->educacao, frase, resposta, 1024))
    {
        registrarInteracao(t->perfil, ACAO_ESTUDO, INTENCAO_ESTUDO);
        salvarPerfil(t->perfil);
        return 1;
    }

    /* --- atividade educativa em curso --- */
    if(atividadeAtiva(t->educacao))
    {
        if(continuarAtividade(t->educacao, frase, resposta, 1024))
        {
            registrarInteracao(t->perfil, ACAO_ESTUDO, INTENCAO_ESTUDO);
            salvarPerfil(t->perfil);
            return 1;
        }
    }

    /* --- interpretação e registo --- */
    interpretarFrase(frase, &inter);
    registrarMemoria(t, frase);
    registrarEpisodio(t, frase);

    /* --- pipeline de processamento --- */
    if(executarInterpretacao(t, &inter, frase, resposta))
    {
        acaoRegisto = inter.tipo;
        tratado = 1;
    }
    else if(tentarAprendizagemConversa(t, frase, resposta))
    {
        acaoRegisto = acaoDeAprendizagem(frase);
        tratado = 1;
    }
    else if(responderConsulta(t->perfil, frase, resposta))
    {
        acaoRegisto = ACAO_CONSULTA;
        tratado = 1;
    }
    else if(executarInferencia(t->conhecimento, frase, resposta))
    {
        acaoRegisto = ACAO_INFERENCIA;
        tratado = 1;
    }
    else if(buscarMemoria(t->episodios, frase, resposta))
    {
        acaoRegisto = ACAO_MEMORIA;
        tratado = 1;
    }
    else if(pesquisarConhecimento(t->conhecimento, frase, resposta))
    {
        acaoRegisto = ACAO_CONSULTA;
        tratado = 1;
    }

    /* --- fallback dialogal --- */
    if(!tratado)
    {
        intencao = gerarRespostaDialogo(t, frase, resposta);
        acaoRegisto = ACAO_DESCONHECIDA;
    }
    else if(acaoRegisto == ACAO_DESCONHECIDA)
    {
        intencao = analisarFrase(t->vocabulario, frase);
    }

    /* --- enriquecimento e registo final --- */
    if(tratado && acaoRegisto != ACAO_DESCONHECIDA)
        enriquecerComMemoria(t, frase, resposta, 1024);

    if(intencao == INTENCAO_DESCONHECIDA)
        intencao = analisarFrase(t->vocabulario, frase);

    {
        EventoEmocional evento = decidirEventoEmocional(t, frase, intencao);
        processarEventoEmocional(t->emocao, evento);
    }

    registrarInteracao(t->perfil, acaoRegisto, intencao);
    salvarPerfil(t->perfil);
    enriquecerComEmocao(t->emocao, resposta, 1024);
    executarComportamentoBaba(t, resposta);

    return tratado;
}
