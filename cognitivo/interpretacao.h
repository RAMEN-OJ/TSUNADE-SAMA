#ifndef INTERPRETACAO_H
#define INTERPRETACAO_H

typedef enum
{
    ACAO_DESCONHECIDA,
    ACAO_SAUDACAO,
    ACAO_PERFIL,
    ACAO_CONSULTA,
    ACAO_INFERENCIA,
    ACAO_CONHECIMENTO,
    ACAO_EMOCAO,
    ACAO_ESTUDO,
    ACAO_JOGO,
    ACAO_MEMORIA

} TipoAcao;

typedef struct
{
    TipoAcao tipo;

    char sujeito[100];
    char relacao[100];
    char objeto[200];

} Interpretacao;

void limparInterpretacao(Interpretacao *i);

#endif