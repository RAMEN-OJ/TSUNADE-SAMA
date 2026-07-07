/*======================================================================
  motor.c
  Motor de execução do ciclo de interação com o utilizador.
  Gere apresentação, leitura de frases, comandos de sistema e respostas.
======================================================================*/

#include <stdio.h>
#include <string.h>

#include "motor.h"
#include "../interface/ui.h"
#include "../pais/painel_pais.h"
#include "../crianca/painel_crianca.h"
#include "../crianca/comportamento.h"
#include "../crianca/decisao.h"
#include "../core/crianca.h"
#include "../cognitivo/interpretacao.h"
#include "../educacao/atividades.h"
#include "../admin/admin.h"
#include "../cognitivo/motor_cognitivo.h"
#include "../memoria/memoria_imediata.h"

#define TAM_RESPOSTA 1024

static int executarComandoSistema(Tsunade *t, const char *frase);

/* Apresenta a Tsunade com saudação personalizada e comandos disponíveis; parâmetro: t */
void apresentarTsunade(Tsunade *t)
{
    ui_titulo(t->nome, "A tua companheira de aprendizagem");

    /* --- saudação --- */
    if(strlen(t->perfil->nome) > 0)
    {
        char saudacao[256];
        snprintf(saudacao, sizeof(saudacao),
            "Olá %s! Que bom ver-te novamente.", t->perfil->nome);
        ui_fala_tsunade(saudacao);
    }
    else
    {
        ui_fala_tsunade("Olá! Estou pronta para aprender contigo.");
    }

    ui_rodape_comandos();
    ui_separador();
}

/* Executa um ciclo: estado, decisão autónoma, leitura de frase e geração de resposta; parâmetro: t */
void executarCiclo(Tsunade *t)
{
    char frase[256];
    char resposta[TAM_RESPOSTA];
    char decisao[TAM_RESPOSTA];

    ui_barra_estado(t);

    /* --- evolução temporal da criança --- */
    passarTempoCrianca(t);

    /* --- intervenção autónoma --- */
    if(precisaIntervencaoAutonoma(t))
    {
        decisao[0] = '\0';

        if(executarDecisao(t, decisao))
        {
            ui_separador();
        }
    }

    /* --- leitura da frase do utilizador --- */
    ui_prompt_usuario();

    if(fgets(frase, sizeof(frase), stdin) == NULL)
        return;

    frase[strcspn(frase, "\n")] = '\0';

    /* --- comandos de sistema --- */
    if(executarComandoSistema(t, frase))
    {
        return;
    }

    resposta[0] = '\0';

    /* --- atividade educativa em curso --- */
    if(atividadeAtiva(t->educacao))
    {
        if(continuarAtividade(t->educacao, frase, resposta, TAM_RESPOSTA))
        {
            registrarInteracao(t->perfil, ACAO_ESTUDO, INTENCAO_ESTUDO);
            salvarPerfil(t->perfil);
            ui_fala_tsunade(resposta);
            ui_separador();
            return;
        }
    }

    /* --- processamento cognitivo --- */
    pensar(t, frase, resposta);
    ui_fala_tsunade(resposta);
    ui_separador();
}

/* Verifica e executa comandos especiais (admin, crianca, pais, sair); retorna 1 se tratado */
static int executarComandoSistema(Tsunade *t, const char *frase)
{
    if(strcmp(frase, "admin") == 0)
    {
        painelAdministrador(t);
        return 1;
    }

    if(strcmp(frase, "crianca") == 0)
    {
        mostrarPainelCrianca(t);
        return 1;
    }

    if(strcmp(frase, "pais") == 0)
    {
        mostrarPainelPais(t);
        return 1;
    }

    if(strcmp(frase, "historico") == 0)
    {
        ui_caixa("Histórico de Conversa");
        if(t->memoria->total == 0)
            printf("  \033[34m║\033[0m  (ainda não há mensagens registadas)\n");
        else
            mostrarMemoriaImediata(t->memoria);
        ui_caixa_fim();
        return 1;
    }

    if(strcmp(frase, "sair") == 0 || strcmp(frase, "adeus") == 0)
    {
        ui_fala_tsunade("Até logo! Foi um prazer estar contigo hoje.");
        t->ativa = 0;
        return 1;
    }

    return 0;
}
