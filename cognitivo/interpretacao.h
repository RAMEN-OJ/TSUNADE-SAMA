/*======================================================================
  interpretacao.h
  Definições de tipos de ação e estrutura de interpretação sintática.
  Representa o resultado da análise de uma frase do utilizador.
======================================================================*/

#ifndef INTERPRETACAO_H
#define INTERPRETACAO_H

/* --- tipos de ação reconhecidos --- */
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

/* --- estrutura de interpretação --- */
typedef struct
{
    TipoAcao tipo;
    char sujeito[100];
    char relacao[100];
    char objeto[200];

} Interpretacao;

/* Reinicializa estrutura de interpretação para valores vazios; parâmetro: i */
void limparInterpretacao(Interpretacao *i);

#endif
