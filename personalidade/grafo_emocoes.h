/* ==========================================================================
 * grafo_emocoes.h — Grafo de transições emocionais
 *
 * Grafo orientado que modela transições entre estados emocionais
 * da Tsunade com pesos associados a cada ligação.
 * ========================================================================== */

#ifndef GRAFO_EMOCOES_H
#define GRAFO_EMOCOES_H

#include "estado_emocional.h"

#define MAX_ESTADOS 10

/** Aresta ponderada entre dois estados emocionais. */
typedef struct
{
    EstadoEmocional destino;

    int peso;

} LigacaoEmocional;

/** Nó do grafo com lista de transições emocionais possíveis. */
typedef struct
{
    EstadoEmocional estado;

    LigacaoEmocional vizinhos[10];

    int quantidade;

} NoEmocional;

/** Grafo completo de estados e transições emocionais. */
typedef struct
{
    NoEmocional nos[MAX_ESTADOS];

    int quantidade;

} GrafoEmocoes;

/** Cria grafo emocional com topologia padrão. */
GrafoEmocoes *criarGrafoEmocoes(void);

/** Liberta estrutura do grafo emocional. */
void destruirGrafoEmocoes(GrafoEmocoes *g);

/** Adiciona ligação ponderada entre estados emocionais. */
void adicionarLigacao(GrafoEmocoes *g, EstadoEmocional origem, EstadoEmocional destino, int peso);

/** Obtém destino da transição pelo índice no nó actual. */
EstadoEmocional proximoEstado(GrafoEmocoes *g, EstadoEmocional atual, int indice);

/** Constrói topologia emocional predefinida da Tsunade. */
void construirGrafoPadrao(GrafoEmocoes *g);

#endif
