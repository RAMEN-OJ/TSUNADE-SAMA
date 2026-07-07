/* ==========================================================================
 * ui.c — Interface de terminal
 *
 * Renderização visual na consola com cores ANSI, caixas, barras de
 * progresso e formatação das falas da Tsunade e do utilizador.
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ui.h"

/* ---------- Códigos de escape ANSI ---------- */

#define UI_RESET   "\033[0m"
#define UI_BOLD    "\033[1m"
#define UI_DIM     "\033[2m"
#define UI_CYAN    "\033[36m"
#define UI_MAGENTA "\033[35m"
#define UI_GREEN   "\033[32m"
#define UI_YELLOW  "\033[33m"
#define UI_BLUE    "\033[34m"
#define UI_WHITE   "\033[37m"
#define UI_RED     "\033[31m"

static int caixa_aberta = 0;

/**
 * Activa processamento de sequências ANSI e codificação UTF-8 no Windows.
 */
void ui_inicializar(void)
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if(hOut != INVALID_HANDLE_VALUE &&
       GetConsoleMode(hOut, &dwMode))
    {
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    SetConsoleOutputCP(65001);
#endif
}

/**
 * Limpa o ecrã e posiciona o cursor no canto superior esquerdo.
 */
void ui_limpar(void)
{
    printf("\033[2J\033[H");
}

/**
 * Desenha o cabeçalho decorativo com nome e subtítulo da aplicação.
 */
void ui_titulo(const char *nome, const char *subtitulo)
{
    printf("\n");
    printf("  " UI_CYAN UI_BOLD "╔══════════════════════════════════════════════╗" UI_RESET "\n");
    printf("  " UI_CYAN UI_BOLD "║" UI_RESET "                                              " UI_CYAN UI_BOLD "║" UI_RESET "\n");
    printf("  " UI_CYAN UI_BOLD "║" UI_RESET "         " UI_MAGENTA UI_BOLD "🌸  %s  🌸" UI_RESET "         " UI_CYAN UI_BOLD "║" UI_RESET "\n",
           nome);
    printf("  " UI_CYAN UI_BOLD "║" UI_RESET "                                              " UI_CYAN UI_BOLD "║" UI_RESET "\n");
    printf("  " UI_CYAN UI_BOLD "║" UI_RESET "      " UI_DIM "%s" UI_RESET "      " UI_CYAN UI_BOLD "║" UI_RESET "\n",
           subtitulo);
    printf("  " UI_CYAN UI_BOLD "║" UI_RESET "                                              " UI_CYAN UI_BOLD "║" UI_RESET "\n");
    printf("  " UI_CYAN UI_BOLD "╚══════════════════════════════════════════════╝" UI_RESET "\n");
    printf("\n");
}

/**
 * Devolve ícone visual proporcional ao valor do indicador (0–100).
 */
static const char *icone_estado(int valor)
{
    if(valor >= 70)
        return "●";
    if(valor >= 40)
        return "◐";
    return "○";
}

/**
 * Selecciona cor ANSI conforme faixa de valor do indicador.
 */
static const char *cor_estado(int valor)
{
    if(valor >= 70)
        return UI_GREEN;
    if(valor >= 40)
        return UI_YELLOW;
    return UI_RED;
}

/**
 * Mostra barra compacta com energia, humor, saciedade e curiosidade.
 */
void ui_barra_estado(Tsunade *t)
{
    PerfilCrianca *p;

    if(t == NULL || t->perfil == NULL)
        return;

    p = t->perfil;

    printf("  " UI_DIM "┌─ Estado ─────────────────────────────────────────────┐" UI_RESET "\n");
    printf("  " UI_DIM "│" UI_RESET " %s%s" UI_RESET " Energia %3d  %s%s" UI_RESET " Humor %3d  "
           "%s%s" UI_RESET " Fome %3d  %s%s" UI_RESET " Curios. %3d " UI_DIM "│" UI_RESET "\n",
           cor_estado(p->energia), icone_estado(p->energia), p->energia,
           cor_estado(p->humor), icone_estado(p->humor), p->humor,
           cor_estado(100 - p->fome), icone_estado(100 - p->fome), p->fome,
           cor_estado(p->curiosidade), icone_estado(p->curiosidade), p->curiosidade);
    printf("  " UI_DIM "└──────────────────────────────────────────────────────┘" UI_RESET "\n");
}

/**
 * Imprime linha separadora horizontal estilizada.
 */
void ui_separador(void)
{
    printf("  " UI_DIM "────────────────────────────────────────────────────────" UI_RESET "\n");
}

/**
 * Mostra comandos de navegação disponíveis no rodapé.
 */
void ui_rodape_comandos(void)
{
    printf("\n  " UI_DIM "Comandos:" UI_RESET " "
           UI_CYAN "historico" UI_RESET " · "
           UI_CYAN "crianca" UI_RESET " · "
           UI_CYAN "pais" UI_RESET " · "
           UI_CYAN "admin" UI_RESET " · "
           UI_CYAN "sair" UI_RESET "\n");
}

/**
 * Imprime o prompt de entrada do utilizador.
 */
void ui_prompt_usuario(void)
{
    printf("\n  " UI_GREEN UI_BOLD "Tu" UI_RESET UI_DIM " › " UI_RESET);
    fflush(stdout);
}

/**
 * Formata e imprime fala da Tsunade com prefixo em cada linha.
 */
void ui_fala_tsunade(const char *mensagem)
{
    const char *p;
    int primeira = 1;

    if(mensagem == NULL || mensagem[0] == '\0')
        return;

    printf("\n");

    for(p = mensagem; *p != '\0'; p++)
    {
        if(primeira)
        {
            printf("  " UI_MAGENTA UI_BOLD "Tsunade" UI_RESET UI_DIM " › " UI_RESET);
            primeira = 0;
        }

        if(*p == '\n')
        {
            printf("\n");
            primeira = 1;
        }
        else
        {
            putchar(*p);
        }
    }

    if(!primeira)
        printf("\n");
}

/**
 * Imprime mensagem informativa do sistema com ícone.
 */
void ui_fala_sistema(const char *mensagem)
{
    printf("\n  " UI_BLUE UI_DIM "ℹ " UI_RESET "%s\n", mensagem);
}

/**
 * Apresenta bloco de decisão autónoma com acção, peso e mensagem.
 */
void ui_decisao(const char *acao, int peso, const char *mensagem)
{
    printf("\n  " UI_YELLOW "┌─ Decisão autónoma ──────────────────────────────────┐" UI_RESET "\n");
    printf("  " UI_YELLOW "│" UI_RESET " " UI_BOLD "%s" UI_RESET UI_DIM "  (prioridade %d)" UI_RESET "\n", acao, peso);
    printf("  " UI_YELLOW "└──────────────────────────────────────────────────────┘" UI_RESET "\n");
    ui_fala_tsunade(mensagem);
}

/**
 * Abre caixa decorativa com título (estado global caixa_aberta).
 */
void ui_caixa(const char *titulo)
{
    caixa_aberta = 1;
    printf("\n  " UI_BLUE "╔═ " UI_BOLD "%s" UI_RESET UI_BLUE " ═════════════════════════════" UI_RESET "\n", titulo);
}

/**
 * Fecha a caixa decorativa aberta anteriormente.
 */
void ui_caixa_fim(void)
{
    if(!caixa_aberta)
        return;

    printf("  " UI_BLUE "╚══════════════════════════════════════════════════════" UI_RESET "\n\n");
    caixa_aberta = 0;
}

/**
 * Imprime linha rotulada com valor numérico dentro de caixa aberta.
 */
void ui_linha(const char *rotulo, int valor)
{
    printf("  " UI_BLUE "║" UI_RESET " %-22s %d\n", rotulo, valor);
}

/**
 * Imprime barra de progresso percentual com blocos preenchidos.
 */
void ui_barra(const char *rotulo, int valor)
{
    int blocos = valor / 10;
    int i;

    printf("  " UI_BLUE "║" UI_RESET " %-12s ", rotulo);
    printf("[");
    for(i = 0; i < 10; i++)
    {
        if(i < blocos)
            printf(UI_GREEN "█" UI_RESET);
        else
            printf(UI_DIM "░" UI_RESET);
    }
    printf("] %3d%%\n", valor);
}

/**
 * Anuncia início de actividade educativa ou lúdica.
 */
void ui_atividade(const char *tipo, const char *detalhe)
{
    printf("\n  " UI_CYAN "▶ Atividade:" UI_RESET " " UI_BOLD "%s" UI_RESET UI_DIM " — %s" UI_RESET "\n",
           tipo, detalhe);
}
