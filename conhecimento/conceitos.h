#ifndef CONCEITOS_H
#define CONCEITOS_H

#define MAX_CONCEITOS 500

typedef struct
{
    char sujeito[100];
    char relacao[100];
    char objeto[200];
}
Relacao;

typedef struct
{
    Relacao lista[MAX_CONCEITOS];
    int quantidade;
}
BaseConhecimento;

BaseConhecimento *criarBaseConhecimento(void);

void destruirBaseConhecimento(
        BaseConhecimento *b);

void adicionarRelacao(
        BaseConhecimento *b,
        const char *sujeito,
        const char *relacao,
        const char *objeto);

void salvarConhecimento(
        BaseConhecimento *b);

void carregarConhecimento(
        BaseConhecimento *b);

#endif
