/* ==========================================================================
 * perfil.h — Perfil da criança
 *
 * Estrutura com identidade, estado afectivo/fisiológico, preferências
 * e métricas de progresso diário da criança virtual.
 * ========================================================================== */

#ifndef PERFIL_H
#define PERFIL_H

/** Perfil persistente da criança com identidade, estado e estatísticas. */
typedef struct
{
    /* ---------- Identidade ---------- */

    char nome[100];

    int idade;

    char corFavorita[50];

    char animalFavorito[50];

    char comidaFavorita[50];

    /* ---------- Estado actual ---------- */

    int energia;

    int humor;

    int curiosidade;

    int atencao;

    int fome;

    /* ---------- Progresso do dia ---------- */

    int tempoEstudo;

    int tempoBrincadeira;

    int tempoDescanso;

    int historiasOuvidas;

    int perguntasRespondidas;

    int conhecimentosAprendidos;

    int totalConversas;

} PerfilCrianca;

/** Cria perfil com valores por omissão. */
PerfilCrianca *criarPerfil(void);

/** Liberta a estrutura do perfil. */
void destruirPerfil(PerfilCrianca *p);

/** Persiste o perfil em dados/perfil.dat. */
void salvarPerfil(PerfilCrianca *p);

/** Carrega o perfil a partir de dados/perfil.dat. */
void carregarPerfil(PerfilCrianca *p);

#endif
