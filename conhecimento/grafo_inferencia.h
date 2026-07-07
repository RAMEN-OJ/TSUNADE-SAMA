/* ==========================================================================
 * grafo_inferencia.h — Inferência sobre o grafo de conhecimento
 *
 * Normalização textual, consulta de conceitos, extracção de entidades
 * e recolha de factos directos e inferidos a partir do grafo semântico.
 * ========================================================================== */

#ifndef GRAFO_INFERENCIA_H
#define GRAFO_INFERENCIA_H

#include <stddef.h>

#include "conceitos.h"

#define MAX_FATOS_GRAFO 64

/** Facto semântico recolhido do grafo, directo ou por herança de tipo. */
typedef struct
{
    char relacao[100];
    char objeto[200];
    char herancaDe[100];
    int inferido;

} FatoGrafo;

/** Normaliza texto genérico (minúsculas e remoção de acentos). */
void normalizarTexto(char *dest, const char *origem, size_t tamanho);

/** Normaliza um conceito removendo artigos e plural simples. */
void normalizarConceito(char *dest, const char *origem, size_t tamanho);

/** Canonicaliza relações linguísticas para formas internas do grafo. */
void normalizarRelacao(char *dest, const char *origem, size_t tamanho);

/** Procura um nó semântico com normalização e comparação flexível. */
NoSemantico *procurarConceitoGrafo(BaseConhecimento *b, const char *conceito);

/** Extrai o conceito-alvo de frases de consulta do utilizador. */
int extrairConceitoConsulta(const char *frase, char *conceito, size_t tamanho);

/** Recolhe factos directos e inferidos sobre um conceito no grafo. */
int coletarFatosGrafo(BaseConhecimento *b, const char *conceito, FatoGrafo *fatos, int maxFatos);

/** Formata uma resposta textual com factos directos e inferidos. */
int responderConhecimentoGrafo(BaseConhecimento *b, const char *conceito, char *resposta, size_t tamanho);

/** Adiciona uma relação após normalizar sujeito, relação e objecto. */
void adicionarRelacaoNormalizada(BaseConhecimento *b, const char *sujeito,
                                 const char *relacao, const char *objeto);

/** Regista ligação bidireccional de sinónimos entre dois conceitos. */
void adicionarSinonimo(BaseConhecimento *b, const char *a, const char *b_conceito);

/** Carrega sinónimos comuns (cão/dog, gato/cat, etc.). */
void carregarSinonimosPadrao(BaseConhecimento *b);

#endif
