/* ==========================================================================
 * decisao.c — Decisão autónoma da criança virtual
 *
 * Constrói grafo de acções a partir do perfil, selecciona a melhor,
 * aplica efeitos no perfil, inicia actividades e apresenta na UI.
 * ========================================================================== */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "decisao.h"
#include "grafo_decisao.h"
#include "../memoria/perfil.h"
#include "../educacao/atividades.h"
#include "../interface/ui.h"

#define TAM_RESPOSTA 1024

/**
 * Popula o grafo de decisão com acções ponderadas conforme o perfil.
 */
static void construirGrafoDecisao(Tsunade *t, GrafoDecisao *g)
{
    PerfilCrianca *p = t->perfil;

    iniciarGrafoDecisao(g);

    if(p->fome >= 80)
        adicionarAcao(g, "Dar comida", 100);
    else if(p->fome >= 50)
        adicionarAcao(g, "Lanche", 70);

    if(p->energia <= 20)
        adicionarAcao(g, "Dormir", 95);
    else if(p->energia <= 50)
        adicionarAcao(g, "Descansar", 60);

    if(p->curiosidade >= 80)
        adicionarAcao(g, "Ensinar", 85);

    if(p->humor >= 70)
        adicionarAcao(g, "Brincar", 65);
    else if(p->humor <= 30)
        adicionarAcao(g, "Contar história", 90);

    if(p->atencao >= 70)
        adicionarAcao(g, "Exercício educativo", 75);

    if(g->total == 0)
        adicionarAcao(g, "Conversar", 30);
}

/**
 * Garante que indicadores do perfil permanecem no intervalo 0–100.
 */
static void limitarPerfil(PerfilCrianca *p)
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

/**
 * Indica se a acção dispara conteúdo educativo interactivo.
 */
static int acaoTemConteudo(const char *nome)
{
    return strcmp(nome, "Ensinar") == 0 ||
           strcmp(nome, "Contar história") == 0 ||
           strcmp(nome, "Brincar") == 0 ||
           strcmp(nome, "Exercício educativo") == 0;
}

/**
 * Devolve mensagem textual para acções sem conteúdo educativo.
 */
static const char *mensagemAcao(const char *nome)
{
    if(strcmp(nome, "Dar comida") == 0)
        return "Preparei uma refeição saudável para ti. Bom apetite!";
    if(strcmp(nome, "Lanche") == 0)
        return "Vamos fazer um pequeno lanche juntos.";
    if(strcmp(nome, "Dormir") == 0)
        return "Está na hora de descansar. Fecha os olhinhos...";
    if(strcmp(nome, "Descansar") == 0)
        return "Vamos descansar um pouco. Respira fundo...";
    if(strcmp(nome, "Conversar") == 0)
        return "Estou aqui contigo. O que queres fazer?";
    return "Vamos passar um bom momento juntos.";
}

/**
 * Aplica efeitos da acção escolhida nos indicadores do perfil.
 */
static void aplicarAcao(PerfilCrianca *p, const char *nome)
{
    if(strcmp(nome, "Dar comida") == 0)
    {
        p->fome -= 50;
        p->humor += 5;
    }
    else if(strcmp(nome, "Lanche") == 0)
    {
        p->fome -= 20;
    }
    else if(strcmp(nome, "Dormir") == 0)
    {
        p->energia = 100;
        p->tempoDescanso += 30;
    }
    else if(strcmp(nome, "Descansar") == 0)
    {
        p->energia += 25;
        p->tempoDescanso += 15;
    }
    else if(strcmp(nome, "Ensinar") == 0)
    {
        p->tempoEstudo += 20;
        p->conhecimentosAprendidos++;
        p->curiosidade -= 20;
    }
    else if(strcmp(nome, "Brincar") == 0)
    {
        p->tempoBrincadeira += 20;
        p->energia -= 10;
        p->humor += 10;
    }
    else if(strcmp(nome, "Contar história") == 0)
    {
        p->historiasOuvidas++;
        p->humor += 15;
    }
    else if(strcmp(nome, "Exercício educativo") == 0)
    {
        p->tempoEstudo += 15;
        p->perguntasRespondidas++;
    }

    limitarPerfil(p);
}

/**
 * Avalia se o perfil exige intervenção autónoma (fome, energia, humor, etc.).
 */
int precisaIntervencaoAutonoma(Tsunade *t)
{
    PerfilCrianca *p;

    if(t == NULL || t->perfil == NULL)
        return 0;

    if(atividadeAtiva(t->educacao))
        return 0;

    p = t->perfil;

    if(p->fome >= 70)
        return 1;
    if(p->energia <= 30)
        return 1;
    if(p->humor <= 30)
        return 1;
    if(p->curiosidade >= 80 && p->atencao >= 50)
        return 1;
    if(p->atencao >= 80 && p->energia >= 40)
        return 1;

    return 0;
}

/**
 * Executa decisão autónoma completa: escolhe acção, aplica e responde.
 */
int executarDecisao(Tsunade *t, char *resposta)
{
    GrafoDecisao g;
    Acao *acao;
    char conteudo[TAM_RESPOSTA];

    if(t == NULL || t->perfil == NULL || resposta == NULL)
        return 0;

    construirGrafoDecisao(t, &g);
    acao = melhorAcao(&g);

    if(acao == NULL)
        return 0;

    aplicarAcao(t->perfil, acao->nome);

    conteudo[0] = '\0';

    if(acaoTemConteudo(acao->nome) &&
       iniciarAtividadePorAcao(t->educacao, acao->nome, conteudo, TAM_RESPOSTA))
    {
        ui_atividade(nomeModoAtividade(t->educacao), acao->nome);
        snprintf(resposta, TAM_RESPOSTA, "%s", conteudo);
    }
    else
    {
        snprintf(resposta, TAM_RESPOSTA, "%s", mensagemAcao(acao->nome));
    }

    ui_decisao(acao->nome, acao->peso, resposta);
    salvarPerfil(t->perfil);
    return 1;
}

/**
 * Acrescenta sugestão de acção autónoma à resposta se condições forem satisfeitas.
 */
void sugerirAcao(Tsunade *t, char *resposta)
{
    GrafoDecisao g;
    Acao *acao;
    const char *mensagem;
    size_t len;

    if(t == NULL || t->perfil == NULL || resposta == NULL)
        return;

    if(atividadeAtiva(t->educacao))
        return;

    if(!precisaIntervencaoAutonoma(t))
        return;

    construirGrafoDecisao(t, &g);
    acao = melhorAcao(&g);

    if(acao == NULL)
        return;

    mensagem = mensagemAcao(acao->nome);
    len = strlen(resposta);

    if(len > 0)
        strncat(resposta, "\n\n", 1024 - len - 1);

    len = strlen(resposta);
    strncat(resposta, mensagem, 1024 - len - 1);
}
