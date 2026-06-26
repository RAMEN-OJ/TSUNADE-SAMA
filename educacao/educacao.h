#ifndef EDUCACAO_H
#define EDUCACAO_H

typedef enum
{
    LICAO_NENHUMA,
    LICAO_ANIMAIS,
    LICAO_CORES,
    LICAO_NUMEROS,
    LICAO_LETRAS,
    LICAO_FORMAS,
    LICAO_CIENCIAS

} TipoLicao;

typedef struct Educacao
{
    TipoLicao licaoAtual;

    int etapa;

    int pontuacao;

    int ativa;

} Educacao;

Educacao *criarEducacao(void);

void destruirEducacao(Educacao *e);

void iniciarLicao(
        Educacao *e,
        TipoLicao tipo);

int responderEducacao(
        Educacao *e,
        const char *frase,
        char *resposta);

#endif