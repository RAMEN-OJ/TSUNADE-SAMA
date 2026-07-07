/* ==========================================================================
 * painel_pais.c — Relatório para encarregados de educação
 *
 * Painel com avaliação qualitativa do estado, preferências aprendidas,
 * métricas diárias e recomendações pedagógicas automáticas.
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

#include "painel_pais.h"
#include "../interface/ui.h"

/**
 * Converte valor de humor numa descrição qualitativa.
 */
static const char *avaliarHumor(int h){
    if(h >= 80) return "Excelente";
    if(h >= 60) return "Bom";
    if(h >= 40) return "Regular";
    return "Baixo";
}

/**
 * Converte valor de energia numa descrição qualitativa.
 */
static const char *avaliarEnergia(int e)
{
    if(e >= 80) return "Muito ativo";
    if(e >= 60) return "Ativo";
    if(e >= 40) return "Moderado";
    return "Cansado";
}

/**
 * Converte valor de fome numa descrição qualitativa de saciedade.
 */
static const char *avaliarFome(int fome)
{
    if(fome <= 20) return "Saciado";
    if(fome <= 50) return "Normal";
    if(fome <= 70) return "Com fome";
    return "Precisa comer";
}

/**
 * Apresenta relatório completo com estado, preferências e recomendações.
 */
void mostrarPainelPais(Tsunade *t)
{
    PerfilCrianca *p = t->perfil;
    int recomendacoes = 0;

    ui_caixa("Relatório para os Pais");

    if(strlen(p->nome) > 0)
        printf("  \033[34m║\033[0m Criança................ %s\n", p->nome);
    else
        printf("  \033[34m║\033[0m Criança................ (sem nome)\n");

    if(p->idade > 0)
        printf("  \033[34m║\033[0m Idade.................. %d anos\n", p->idade);

    printf("  \033[34m║\033[0m\n");
    printf("  \033[34m║\033[0m \033[1mEstado actual\033[0m\n");
    printf("  \033[34m║\033[0m Estado emocional....... %s (%d%%)\n", avaliarHumor(p->humor), p->humor);
    printf("  \033[34m║\033[0m Energia................ %s (%d%%)\n", avaliarEnergia(p->energia), p->energia);
    printf("  \033[34m║\033[0m Fome................... %s (%d%%)\n", avaliarFome(p->fome), p->fome);
    printf("  \033[34m║\033[0m Curiosidade............ %d%%\n", p->curiosidade);
    printf("  \033[34m║\033[0m Atenção................ %d%%\n", p->atencao);

    if(strlen(p->corFavorita) > 0 || strlen(p->animalFavorito) > 0 || strlen(p->comidaFavorita) > 0)
    {
        printf("  \033[34m║\033[0m\n");
        printf("  \033[34m║\033[0m \033[1mPreferências aprendidas\033[0m\n");
        if(strlen(p->corFavorita) > 0)
            printf("  \033[34m║\033[0m Cor favorita........... %s\n", p->corFavorita);
        if(strlen(p->animalFavorito) > 0)
            printf("  \033[34m║\033[0m Animal favorito........ %s\n", p->animalFavorito);
        if(strlen(p->comidaFavorita) > 0)
            printf("  \033[34m║\033[0m Comida favorita........ %s\n", p->comidaFavorita);
    }

    printf("  \033[34m║\033[0m\n");
    printf("  \033[34m║\033[0m \033[1mActividade do dia\033[0m\n");
    ui_linha("Conversas", p->totalConversas);
    ui_linha("Conhecimentos aprendidos", p->conhecimentosAprendidos);
    ui_linha("Histórias ouvidas", p->historiasOuvidas);
    ui_linha("Perguntas respondidas", p->perguntasRespondidas);
    ui_linha("Tempo de estudo (min)", p->tempoEstudo);
    ui_linha("Tempo de brincadeira", p->tempoBrincadeira);
    ui_linha("Tempo de descanso", p->tempoDescanso);

    printf("  \033[34m║\033[0m\n");
    printf("  \033[34m║\033[0m \033[1mRecomendações\033[0m\n");

    if(p->totalConversas == 0)
    {
        printf("  \033[34m║\033[0m  • Ainda não houve conversas registadas hoje.\n");
        recomendacoes++;
    }

    if(p->fome >= 70)
    {
        printf("  \033[34m║\033[0m  • A criança deve fazer uma refeição em breve.\n");
        recomendacoes++;
    }

    if(p->energia < 30)
    {
        printf("  \033[34m║\033[0m  • A criança precisa descansar mais.\n");
        recomendacoes++;
    }

    if(p->humor < 40)
    {
        printf("  \033[34m║\033[0m  • Recomenda-se mais brincadeiras ou conversas de apoio.\n");
        recomendacoes++;
    }

    if(p->curiosidade > 80)
    {
        printf("  \033[34m║\033[0m  • Excelente momento para ensinar conteúdos novos.\n");
        recomendacoes++;
    }

    if(p->atencao < 30)
    {
        printf("  \033[34m║\033[0m  • Fazer pequenas pausas durante os estudos.\n");
        recomendacoes++;
    }

    if(p->tempoEstudo > p->tempoBrincadeira + 20)
    {
        printf("  \033[34m║\033[0m  • Equilibrar estudo e brincadeiras.\n");
        recomendacoes++;
    }

    if(p->conhecimentosAprendidos == 0 && p->totalConversas > 5)
    {
        printf("  \033[34m║\033[0m  • Sugerir actividades de aprendizagem (aulas, exercícios).\n");
        recomendacoes++;
    }

    if(p->energia >= 70 && p->humor >= 70 && p->totalConversas > 0)
    {
        printf("  \033[34m║\033[0m  • A criança apresentou um excelente dia.\n");
        recomendacoes++;
    }

    if(recomendacoes == 0)
        printf("  \033[34m║\033[0m  • Tudo a correr bem. Continue assim!\n");

    ui_caixa_fim();
}
