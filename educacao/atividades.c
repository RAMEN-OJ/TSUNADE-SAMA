/* ==========================================================================
 * atividades.c — Actividades educativas e lúdicas
 * ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "atividades.h"
#include "licoes_data.h"
#include "historias_data.h"
#include "jogos_data.h"

static void copiaMinuscula(const char *frase, char *copia, size_t tamanho)
{
    size_t i;

    if(frase == NULL || copia == NULL)
        return;

    for(i = 0; frase[i] != '\0' && i < tamanho - 1; i++)
        copia[i] = (char)tolower((unsigned char)frase[i]);
    copia[i] = '\0';
}

static int respostaContemLista(const char *frase, const char *lista)
{
    char copiaFrase[256];
    char copiaLista[256];
    char *token;
    size_t i;

    if(frase == NULL || lista == NULL)
        return 0;

    for(i = 0; frase[i] != '\0' && i < sizeof(copiaFrase) - 1; i++)
        copiaFrase[i] = (char)tolower((unsigned char)frase[i]);
    copiaFrase[i] = '\0';

    strncpy(copiaLista, lista, sizeof(copiaLista) - 1);
    copiaLista[sizeof(copiaLista) - 1] = '\0';

    token = strtok(copiaLista, "|");
    while(token != NULL)
    {
        if(strstr(copiaFrase, token) != NULL)
            return 1;
        token = strtok(NULL, "|");
    }

    return 0;
}

static void terminarAtividade(Educacao *e)
{
    e->ativa = 0;
    e->modo = MODO_LIVRE;
    e->etapa = 0;
}

int atividadeAtiva(Educacao *e)
{
    return e != NULL && e->ativa;
}

const char *nomeModoAtividade(Educacao *e)
{
    if(e == NULL || !e->ativa)
        return "Livre";

    switch(e->modo)
    {
        case MODO_LICAO:      return "Aula";
        case MODO_HISTORIA:   return "História";
        case MODO_JOGO:       return "Jogo";
        case MODO_EXERCICIO:  return "Exercício";
        default:              return "Livre";
    }
}

static void iniciarHistoria(Educacao *e, char *resposta, size_t tamanho)
{
    const HistoriaInfantil *h;

    e->modo = MODO_HISTORIA;
    e->conteudoId = rand() % NUM_HISTORIAS;
    e->etapa = 0;
    e->pontuacao = 0;
    e->ativa = 1;

    h = obterHistoria(e->conteudoId);
    if(h == NULL)
    {
        terminarAtividade(e);
        return;
    }

    snprintf(resposta, tamanho,
        "📖 %s\n\n%s\n\n(responde qualquer coisa para ouvires o resto...)",
        h->titulo, h->partes[0]);
    e->etapa = 1;
}

static int continuarHistoria(Educacao *e, const char *frase, char *resposta, size_t tamanho)
{
    const HistoriaInfantil *h;

    (void)frase;

    h = obterHistoria(e->conteudoId);
    if(h == NULL)
    {
        terminarAtividade(e);
        return 0;
    }

    if(e->etapa == 1)
    {
        snprintf(resposta, tamanho, "%s\n\n(continua...)", h->partes[1]);
        e->etapa = 2;
        return 1;
    }

    if(e->etapa == 2)
    {
        snprintf(resposta, tamanho, "%s\n\nFim da história! Queres outra? Diz 'conta-me uma história'.",
                 h->partes[2]);
        terminarAtividade(e);
        return 1;
    }

    terminarAtividade(e);
    return 1;
}

static void iniciarJogo(Educacao *e, char *resposta, size_t tamanho)
{
    const JogoInfantil *j;

    e->modo = MODO_JOGO;
    e->conteudoId = rand() % NUM_JOGOS;
    e->etapa = 0;
    e->pontuacao = 0;
    e->ativa = 1;

    j = obterJogo(e->conteudoId);
    if(j == NULL)
    {
        terminarAtividade(e);
        return;
    }

    snprintf(resposta, tamanho, "🎮 %s\n%s", j->titulo, j->pergunta);
}

static int continuarJogo(Educacao *e, const char *frase, char *resposta, size_t tamanho)
{
    const JogoInfantil *j;

    j = obterJogo(e->conteudoId);
    if(j == NULL)
    {
        terminarAtividade(e);
        return 0;
    }

    if(respostaContemLista(frase, j->respostasCertas))
    {
        e->pontuacao++;
        snprintf(resposta, tamanho, "%s\n\nQueres brincar outra vez? Diz 'vamos brincar'!",
                 j->feedbackOk);
    }
    else
    {
        snprintf(resposta, tamanho, "%s\n\nQueres tentar outro jogo? Diz 'jogar'!",
                 j->feedbackErr);
    }

    terminarAtividade(e);
    return 1;
}

static void iniciarExercicio(Educacao *e, char *resposta, size_t tamanho)
{
    static const char *perguntas[] = {
        "Quanto é 2 + 3?",
        "Quanto é 5 - 2?",
        "Quanto é 3 + 4?",
        "Quanto é 6 - 1?",
        "Quanto é 2 + 2?"
    };

    e->modo = MODO_EXERCICIO;
    e->conteudoId = rand() % 5;
    e->etapa = 0;
    e->pontuacao = 0;
    e->ativa = 1;

    snprintf(resposta, tamanho,
        "✏️ Exercício de matemática!\n%s",
        perguntas[e->conteudoId]);
}

static int continuarExercicio(Educacao *e, const char *frase, char *resposta, size_t tamanho)
{
    static const char *respostas[] = { "5", "3", "7", "5", "4" };
    const char *certa = respostas[e->conteudoId];

    if(strstr(frase, certa))
    {
        e->pontuacao++;
        snprintf(resposta, tamanho,
            "Resposta correta! Muito bem! ⭐\nQueres mais? Diz 'vamos estudar matemática'.");
    }
    else
    {
        snprintf(resposta, tamanho,
            "A resposta certa era %s. Vamos praticar mais!",
            certa);
    }

    terminarAtividade(e);
    return 1;
}

static int pedidoHistoria(const char *copia)
{
    if(strstr(copia, "historia") || strstr(copia, "conto") || strstr(copia, "fabula"))
    {
        if(strstr(copia, "estudar") || strstr(copia, "licao") || strstr(copia, "escola"))
            return 0;

        if(strstr(copia, "conta") || strstr(copia, "contar") || strstr(copia, "narr") ||
           strstr(copia, "historia") || strstr(copia, "conto"))
            return 1;
    }

    return 0;
}

int iniciarAtividadePorPedido(Educacao *e, const char *frase, char *resposta, size_t tamanho)
{
    char copia[256];
    TipoLicao licao;

    if(e == NULL || frase == NULL || resposta == NULL)
        return 0;

    if(e->ativa)
        return 0;

    copiaMinuscula(frase, copia, sizeof(copia));
    resposta[0] = '\0';

    if(pedidoHistoria(copia))
    {
        iniciarHistoria(e, resposta, tamanho);
        return 1;
    }

    if(strstr(copia, "brincar") || strstr(copia, "jogar") || strstr(copia, "jogo") ||
       strstr(copia, "brincadeira") || strstr(copia, "adivinha") || strstr(copia, "diversao"))
    {
        iniciarJogo(e, resposta, tamanho);
        return 1;
    }

    if(strstr(copia, "exercicio") && !strstr(copia, "historia"))
    {
        iniciarExercicio(e, resposta, tamanho);
        return 1;
    }

    licao = detectarLicaoFrase(copia);

    if(licao != LICAO_NENHUMA ||
       strstr(copia, "estudar") || strstr(copia, "aprender") ||
       strstr(copia, "licao") || strstr(copia, "vamos") || strstr(copia, "aula"))
    {
        if(licao == LICAO_NENHUMA)
            licao = escolherLicaoRotativa(e);

        iniciarLicao(e, licao);
        return responderEducacao(e, "", resposta);
    }

    return 0;
}

int iniciarAtividadePorAcao(Educacao *e, const char *nomeAcao, char *resposta, size_t tamanho)
{
    TipoLicao licao;

    if(e == NULL || nomeAcao == NULL || resposta == NULL)
        return 0;

    resposta[0] = '\0';

    if(strcmp(nomeAcao, "Ensinar") == 0)
    {
        licao = escolherLicaoRotativa(e);
        iniciarLicao(e, licao);
        return responderEducacao(e, "", resposta);
    }

    if(strcmp(nomeAcao, "Contar história") == 0)
    {
        iniciarHistoria(e, resposta, tamanho);
        return 1;
    }

    if(strcmp(nomeAcao, "Brincar") == 0)
    {
        iniciarJogo(e, resposta, tamanho);
        return 1;
    }

    if(strcmp(nomeAcao, "Exercício educativo") == 0)
    {
        iniciarExercicio(e, resposta, tamanho);
        return 1;
    }

    return 0;
}

int continuarAtividade(Educacao *e, const char *frase, char *resposta, size_t tamanho)
{
    if(e == NULL || !e->ativa || resposta == NULL)
        return 0;

    resposta[0] = '\0';

    switch(e->modo)
    {
        case MODO_LICAO:
            return responderEducacao(e, frase, resposta);

        case MODO_HISTORIA:
            return continuarHistoria(e, frase, resposta, tamanho);

        case MODO_JOGO:
            if(e->etapa == 0)
                e->etapa = 1;
            return continuarJogo(e, frase, resposta, tamanho);

        case MODO_EXERCICIO:
            if(e->etapa == 0)
                e->etapa = 1;
            return continuarExercicio(e, frase, resposta, tamanho);

        default:
            terminarAtividade(e);
            return 0;
    }
}
