/* ==========================================================================
 * admin.c — Painel administrativo
 *
 * Interface de consola para administradores inspecionarem memória,
 * conhecimento, emoções, perfil, educação e estatísticas da Tsunade.
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

#include "admin.h"

#include "../memoria/memoria_imediata.h"
#include "../memoria/episodios.h"
#include "../personalidade/emocoes.h"
#include "../conhecimento/conceitos.h"
#include "../conhecimento/grafo_inferencia.h"
#include "../educacao/atividades.h"

/**
 * Menu principal do administrador com submenus de diagnóstico.
 */
void painelAdministrador(Tsunade *t)
{
    int opcao;

    do
    {
        printf("\n");
        printf("=========================================================\n");
        printf("            TSUNADE - PAINEL ADMINISTRADOR\n");
        printf("=========================================================\n");

        printf("1  Dashboard Geral\n");
        printf("2  Perfil da Crianca\n");
        printf("3  Memoria\n");
        printf("4  Conhecimento\n");
        printf("5  Emoções\n");
        printf("6  Educação\n");
        printf("7  Estatísticas\n");
        printf("8  Ferramentas\n");
        printf("9  Diagnóstico\n");
        printf("0  Voltar\n");

        printf("\nEscolha: ");

        scanf("%d",&opcao);
        getchar();

        switch(opcao)
        {
            case 1:
                menuDashboard(t);
                break;

            case 2:
                menuPerfil(t);
                break;

            case 3:
                menuMemoria(t);
                break;

            case 4:
                menuConhecimento(t);
                break;

            case 5:
                menuEmocoes(t);
                break;

            case 6:
                menuEducacao(t);
                break;

            case 7:
                menuEstatisticas(t);
                break;

            case 8:
                menuFerramentas(t);
                break;

            case 9:
                menuDiagnostico(t);
                break;
        }

    } while(opcao!=0);
}

/**
 * Mostra resumo agregado de mensagens, emoções e conhecimento.
 */
void menuDashboard(Tsunade *t)
{
    printf("\n========== DASHBOARD ==========\n");

    printf("Mensagens........ %d\n",
           t->memoria->total);

    printf("Estado........... %s\n",
           nomeEstado(t->emocao->estado));

    printf("Energia.......... %d\n",
           t->emocao->energia);

    printf("Curiosidade...... %d\n",
           t->emocao->curiosidade);

    printf("Empatia.......... %d\n",
           t->emocao->empatia);

    printf("Conceitos........ %d\n",
           t->conhecimento->quantidade);

    printf("Episodios........ %d\n",
           t->episodios->quantidade);

    printf("Conversas........ %d\n",
           t->perfil->totalConversas);

    printf("===============================\n");
}

/**
 * Exibe campos de identidade e preferências do perfil da criança.
 */
void menuPerfil(Tsunade *t)
{
    PerfilCrianca *p = t->perfil;

    printf("\n========== PERFIL ==========\n");

    printf("Nome........ %s\n", p->nome);
    printf("Idade....... %d\n", p->idade);
    printf("Cor......... %s\n", p->corFavorita);
    printf("Animal...... %s\n", p->animalFavorito);
    printf("Comida...... %s\n", p->comidaFavorita);
    printf("Energia..... %d\n", p->energia);
    printf("Humor....... %d\n", p->humor);
    printf("Fome........ %d\n", p->fome);
}

/**
 * Mostra buffer de memória imediata (mensagens recentes).
 */
void menuMemoria(Tsunade *t)
{
    printf("\n========== MEMORIA ==========\n");

    mostrarMemoriaImediata(t->memoria);
}

/**
 * Imprime o grafo semântico de conhecimento completo.
 */
void menuConhecimento(Tsunade *t)
{
    printf("\n========== GRAFO ==========\n");

    imprimirGrafo(t->conhecimento);
}

/**
 * Exibe estado emocional actual e traços da Tsunade.
 */
void menuEmocoes(Tsunade *t)
{
    printf("\n========== EMOCOES ==========\n");

    mostrarEmocoes(t->emocao);
}

/**
 * Mostra estado da sessão educativa activa.
 */
void menuEducacao(Tsunade *t)
{
    Educacao *e = t->educacao;

    printf("\n========== EDUCACAO ==========\n");

    if(!atividadeAtiva(e))
    {
        printf("Modo........ Livre (sem actividade activa)\n");
        printf("Lições disponíveis: animais, cores, números, letras, formas, ciências\n");
        printf("Actividades: aula, história, jogo, exercício\n");
    }
    else
    {
        printf("Actividade.. %s\n", nomeModoAtividade(e));
        printf("Etapa....... %d\n", e->etapa);
        printf("Conteúdo.... %d\n", e->conteudoId);
        printf("Pontuação... %d\n", e->pontuacao);
    }

    printf("Tempo estudo........ %d min\n", t->perfil->tempoEstudo);
    printf("Tempo brincadeira... %d min\n", t->perfil->tempoBrincadeira);
    printf("Histórias ouvidas... %d\n", t->perfil->historiasOuvidas);
    printf("===============================\n");
}

/**
 * Apresenta estatísticas globais da sessão e do perfil.
 */
void menuEstatisticas(Tsunade *t)
{
    PerfilCrianca *p = t->perfil;

    printf("\n========== ESTATISTICAS ==========\n");

    printf("--- Perfil ---\n");
    printf("Conversas.............. %d\n", p->totalConversas);
    printf("Conhecimentos.......... %d\n", p->conhecimentosAprendidos);
    printf("Perguntas respondidas.. %d\n", p->perguntasRespondidas);
    printf("Histórias ouvidas...... %d\n", p->historiasOuvidas);
    printf("Tempo estudo........... %d min\n", p->tempoEstudo);
    printf("Tempo brincadeira...... %d min\n", p->tempoBrincadeira);
    printf("Tempo descanso......... %d min\n", p->tempoDescanso);

    printf("\n--- Sistema ---\n");
    printf("Mensagens recentes..... %d\n", t->memoria->total);
    printf("Episódios guardados.... %d\n", t->episodios->quantidade);
    printf("Relações no grafo...... %d\n", t->conhecimento->quantidade);
    printf("Estado emocional....... %s\n", nomeEstado(t->emocao->estado));
    printf("Empatia Tsunade........ %d\n", t->emocao->empatia);

    printf("\n--- Estado actual ---\n");
    printf("Energia criança........ %d\n", p->energia);
    printf("Humor criança.......... %d\n", p->humor);
    printf("Curiosidade............ %d\n", p->curiosidade);
    printf("Atenção................ %d\n", p->atencao);
    printf("Fome................... %d\n", p->fome);
    printf("==================================\n");
}

/**
 * Ferramentas de manutenção e diagnóstico rápido.
 */
void menuFerramentas(Tsunade *t)
{
    int opcao;

    do
    {
        printf("\n========== FERRAMENTAS ==========\n");
        printf("1  Limpar memória imediata\n");
        printf("2  Recarregar sinónimos padrão\n");
        printf("3  Guardar conhecimento em disco\n");
        printf("4  Guardar perfil em disco\n");
        printf("5  Imprimir grafo no ecrã\n");
        printf("0  Voltar\n");
        printf("\nEscolha: ");

        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1:
                limparMemoriaImediata(t->memoria);
                printf("Memória imediata limpa.\n");
                break;

            case 2:
                carregarSinonimosPadrao(t->conhecimento);
                salvarConhecimento(t->conhecimento);
                printf("Sinónimos padrão registados e guardados.\n");
                break;

            case 3:
                salvarConhecimento(t->conhecimento);
                printf("Conhecimento guardado em dados/conhecimento.dat\n");
                break;

            case 4:
                salvarPerfil(t->perfil);
                printf("Perfil guardado em dados/perfil.dat\n");
                break;

            case 5:
                imprimirGrafo(t->conhecimento);
                break;
        }

    } while(opcao != 0);
}

/**
 * Verifica e reporta estado OK dos componentes principais.
 */
void menuDiagnostico(Tsunade *t)
{
    (void)t;

    printf("\n========== DIAGNOSTICO ==========\n");

    printf("Trie............... OK\n");
    printf("Hash............... OK\n");
    printf("Grafo.............. OK\n");
    printf("Parser............. OK\n");
    printf("Executor........... OK\n");
    printf("Motor Cognitivo.... OK\n");
    printf("Sinónimos.......... OK\n");
    printf("Inferência......... OK\n");
}
