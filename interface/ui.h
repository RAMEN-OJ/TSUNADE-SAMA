/* ==========================================================================
 * ui.h — Interface de terminal
 *
 * Componentes visuais da consola: título, barras de estado, caixas,
 * falas da Tsunade e indicadores de decisão autónoma.
 * ========================================================================== */

#ifndef UI_H
#define UI_H

#include "../core/tsunade.h"

/** Activa suporte ANSI e UTF-8 no terminal Windows. */
void ui_inicializar(void);

/** Limpa o ecrã do terminal. */
void ui_limpar(void);

/** Desenha o cabeçalho decorativo com nome e subtítulo. */
void ui_titulo(const char *nome, const char *subtitulo);

/** Mostra barra compacta com energia, humor, fome e curiosidade. */
void ui_barra_estado(Tsunade *t);

/** Imprime linha separadora horizontal. */
void ui_separador(void);

/** Mostra comandos disponíveis no rodapé. */
void ui_rodape_comandos(void);

/** Imprime o prompt de entrada do utilizador. */
void ui_prompt_usuario(void);

/** Formata e imprime uma fala da Tsunade com destaque visual. */
void ui_fala_tsunade(const char *mensagem);

/** Imprime mensagem informativa do sistema. */
void ui_fala_sistema(const char *mensagem);

/** Apresenta bloco de decisão autónoma com acção e prioridade. */
void ui_decisao(const char *acao, int peso, const char *mensagem);

/** Abre uma caixa decorativa com título. */
void ui_caixa(const char *titulo);

/** Fecha a caixa decorativa aberta anteriormente. */
void ui_caixa_fim(void);

/** Imprime linha rotulada com valor numérico dentro de caixa. */
void ui_linha(const char *rotulo, int valor);

/** Imprime barra de progresso percentual dentro de caixa. */
void ui_barra(const char *rotulo, int valor);

/** Anuncia início de actividade educativa ou lúdica. */
void ui_atividade(const char *tipo, const char *detalhe);

#endif
