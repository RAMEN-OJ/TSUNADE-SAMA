#ifndef CONCEITOS_H
#define CONCEITOS_H

#include "../estruturas/hash.h"

#define MAX_CONCEITOS 500

typedef struct
{
    char sujeito[100];
    char relacao[100];
    char objeto[200];

} Relacao;


/* ---------- GRAFO ---------- */

typedef struct Vizinho
{
    char relacao[100];

    char destino[200];

    struct Vizinho *proximo;

} Vizinho;


typedef struct NoSemantico
{
    char conceito[100];

    Vizinho *adjacentes;

    struct NoSemantico *proximo;

} NoSemantico;


/* ---------- BASE ---------- */

typedef struct
{
    Relacao lista[MAX_CONCEITOS];

    int quantidade;

    Hash *indice;

    NoSemantico *grafo;

} BaseConhecimento;


BaseConhecimento *criarBaseConhecimento(void);

void imprimirGrafo(
        BaseConhecimento *b);
        
    NoSemantico *procurarNoSemantico(
        BaseConhecimento *,
        const char *);

void destruirBaseConhecimento(
        BaseConhecimento *b);

void adicionarRelacao(
        BaseConhecimento *b,
        const char *sujeito,
        const char *relacao,
        const char *objeto);

Relacao *procurarRelacao(
        BaseConhecimento *b,
        const char *sujeito);

void salvarConhecimento(
        BaseConhecimento *b);

void carregarConhecimento(
        BaseConhecimento *b);

#endif