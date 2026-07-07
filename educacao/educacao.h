/* ==========================================================================
 * educacao.h — Módulo educativo
 *
 * Tipos de lição, modos de actividade e estado da sessão educativa
 * conduzida pela Tsunade (aulas, histórias, jogos e exercícios).
 * ========================================================================== */

#ifndef EDUCACAO_H
#define EDUCACAO_H

#define NUM_LICOES 15
#define NUM_HISTORIAS 20
#define NUM_JOGOS 10

/** Tipos de lição educativa disponíveis (15 disciplinas). */
typedef enum
{
    LICAO_NENHUMA,
    LICAO_MATEMATICA,
    LICAO_PORTUGUES,
    LICAO_CIENCIAS,
    LICAO_GEOGRAFIA,
    LICAO_HISTORIA_ESCOLAR,
    LICAO_ANIMAIS,
    LICAO_CORES,
    LICAO_NUMEROS,
    LICAO_LETRAS,
    LICAO_FORMAS,
    LICAO_MUSICA,
    LICAO_INGLES,
    LICAO_AMBIENTE,
    LICAO_SEGURANCA,
    LICAO_ARTE

} TipoLicao;

/** Modo de actividade corrente da sessão educativa. */
typedef enum
{
    MODO_LIVRE,
    MODO_LICAO,
    MODO_HISTORIA,
    MODO_JOGO,
    MODO_EXERCICIO

} ModoAtividade;

/** Estado da sessão educativa com lição, etapa e pontuação. */
typedef struct Educacao
{
    TipoLicao licaoAtual;

    ModoAtividade modo;

    int conteudoId;

    int etapa;

    int pontuacao;

    int ativa;

} Educacao;

/** Cria estado educativo inicial (modo livre, inactivo). */
Educacao *criarEducacao(void);

/** Liberta a estrutura de educação. */
void destruirEducacao(Educacao *e);

/** Inicia uma lição específica e activa o modo aula. */
void iniciarLicao(Educacao *e, TipoLicao tipo);

/** Processa resposta do utilizador durante uma lição activa. */
int responderEducacao(Educacao *e, const char *frase, char *resposta);

#endif
