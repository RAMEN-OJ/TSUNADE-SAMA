/* ==========================================================================
 * conceitos.h — Base de conhecimento semântico
 *
 * Define estruturas de relações, nós do grafo semântico e a API pública
 * para criar, consultar e persistir conhecimento factual.
 * ========================================================================== */

#ifndef CONCEITOS_H
#define CONCEITOS_H

#include "../estruturas/hash.h"

#define MAX_CONCEITOS 500

/** Tripla sujeito-relação-objeto armazenada na lista plana da base. */
typedef struct
{
    char sujeito[100];
    char relacao[100];
    char objeto[200];

} Relacao;


/* ---------- Estruturas do grafo semântico ---------- */

/** Aresta rotulada que liga um conceito a outro no grafo. */
typedef struct Vizinho
{
    char relacao[100];

    char destino[200];

    struct Vizinho *proximo;

} Vizinho;


/** Nó do grafo com lista de adjacências e encadeamento global. */
typedef struct NoSemantico
{
    char conceito[100];

    Vizinho *adjacentes;

    struct NoSemantico *proximo;

} NoSemantico;


/* ---------- Base de conhecimento ---------- */

/** Agrega lista de relações, índice hash e cabeça do grafo semântico. */
typedef struct
{
    Relacao lista[MAX_CONCEITOS];

    int quantidade;

    Hash *indice;

    NoSemantico *grafo;

} BaseConhecimento;

/** Cria uma base de conhecimento vazia. */
BaseConhecimento *criarBaseConhecimento(void);

/** Imprime o grafo semântico no ecrã. */
void imprimirGrafo(BaseConhecimento *b);

/** Procura um nó semântico pelo nome do conceito. */
NoSemantico *procurarNoSemantico(BaseConhecimento *, const char *);

/** Liberta recursos da base de conhecimento. */
void destruirBaseConhecimento( BaseConhecimento *b);

/** Adiciona ou actualiza uma relação semântica. */
void adicionarRelacao(BaseConhecimento *b, const char *sujeito, const char *relacao, const char *objeto);

/** Procura a primeira relação associada a um sujeito. */
Relacao *procurarRelacao(BaseConhecimento *b, const char *sujeito);

/** Grava a base de conhecimento em disco. */
void salvarConhecimento(BaseConhecimento *b);

/** Carrega a base de conhecimento a partir de disco. */
void carregarConhecimento(BaseConhecimento *b);

#endif
