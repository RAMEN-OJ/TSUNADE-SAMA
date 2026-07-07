/* ==========================================================================
 * painel_crianca.c — Painel informativo da criança
 *
 * Renderização do painel da criança com identidade, barras de
 * estado, métricas diárias e actividade educativa em curso.
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

#include "painel_crianca.h"
#include "../interface/ui.h"
#include "../educacao/atividades.h"

/**
 * Apresenta painel visual com perfil, indicadores e progresso diário.
 */
void mostrarPainelCrianca(Tsunade *t)
{
    PerfilCrianca *p = t->perfil;

    ui_caixa("Painel da Criança");

    if(strlen(p->nome) > 0)
        printf("  " "\033[34m" "║" "\033[0m" " Nome................. %s\n", p->nome);
    else
        printf("  " "\033[34m" "║" "\033[0m" " Nome................. (sem nome)\n");

    if(p->idade > 0)
        printf("  " "\033[34m" "║" "\033[0m" " Idade................ %d anos\n", p->idade);

    if(strlen(p->corFavorita) > 0)
        printf("  " "\033[34m" "║" "\033[0m" " Cor favorita......... %s\n", p->corFavorita);
    if(strlen(p->animalFavorito) > 0)
        printf("  " "\033[34m" "║" "\033[0m" " Animal favorito...... %s\n", p->animalFavorito);
    if(strlen(p->comidaFavorita) > 0)
        printf("  " "\033[34m" "║" "\033[0m" " Comida favorita...... %s\n", p->comidaFavorita);

    printf("  " "\033[34m" "║" "\033[0m" "\n");

    ui_barra("Energia", p->energia);
    ui_barra("Humor", p->humor);
    ui_barra("Curiosidade", p->curiosidade);
    ui_barra("Atencao", p->atencao);
    ui_barra("Saciada", 100 - p->fome);

    printf("  " "\033[34m" "║" "\033[0m" "\n");
    ui_linha("Conversas", p->totalConversas);
    ui_linha("Conhecimentos", p->conhecimentosAprendidos);
    ui_linha("Historias", p->historiasOuvidas);
    ui_linha("Perguntas", p->perguntasRespondidas);
    ui_linha("Tempo estudo (min)", p->tempoEstudo);
    ui_linha("Tempo brincadeira", p->tempoBrincadeira);
    ui_linha("Tempo descanso", p->tempoDescanso);

    if(atividadeAtiva(t->educacao))
    {
        printf("  " "\033[34m" "║" "\033[0m" "\n");
        printf("  " "\033[34m" "║" "\033[0m" " Atividade actual..... %s\n",
               nomeModoAtividade(t->educacao));
    }

    ui_caixa_fim();
}
