#include <stdio.h>

#include "admin.h"

#include "../memoria/memoria_imediata.h"
#include "../personalidade/emocoes.h"
#include "../conhecimento/conceitos.h"

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

    printf("===============================\n");
}

void menuPerfil(Tsunade *t)
{
    printf("\n========== PERFIL ==========\n");

    printf("Nome........ %s\n",t->perfil->nome);
    printf("Idade....... %d\n",t->perfil->idade);
    printf("Cor......... %s\n",t->perfil->corFavorita);
    printf("Animal...... %s\n",t->perfil->animalFavorito);
    printf("Comida...... %s\n",t->perfil->comidaFavorita);
}

void menuMemoria(Tsunade *t)
{
    printf("\n========== MEMORIA ==========\n");

    mostrarMemoriaImediata(t->memoria);
}

void menuConhecimento(Tsunade *t)
{
    printf("\n========== GRAFO ==========\n");

    imprimirGrafo(t->conhecimento);
}

void menuEmocoes(Tsunade *t)
{
    printf("\n========== EMOCOES ==========\n");

    mostrarEmocoes(t->emocao);
}

void menuEducacao(Tsunade *t)
{
    printf("\nModulo em desenvolvimento.\n");
}

void menuEstatisticas(Tsunade *t)
{
    (void)t;

    printf("\nModulo em desenvolvimento.\n");
}

void menuFerramentas(Tsunade *t)
{
    (void)t;

    printf("\nModulo em desenvolvimento.\n");
}

void menuDiagnostico(Tsunade *t)
{
    printf("\n========== DIAGNOSTICO ==========\n");

    printf("Trie............... OK\n");
    printf("Hash............... OK\n");
    printf("Grafo.............. OK\n");
    printf("Parser............. OK\n");
    printf("Executor........... OK\n");
    printf("Motor Cognitivo.... OK\n");
}