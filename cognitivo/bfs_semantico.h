/*======================================================================
  bfs_semantico.h
  Interface de busca em largura (BFS) no grafo semântico.
  Verifica caminhos e reconstrói rotas entre conceitos.
======================================================================*/

#ifndef BFS_SEMANTICO_H
#define BFS_SEMANTICO_H

#include "../conhecimento/conceitos.h"

/* Verifica se existe caminho entre origem e destino no grafo; retorna 1 se existe */
int existeCaminho(BaseConhecimento *base, const char *origem, const char *destino);

/* Encontra caminho BFS entre conceitos e preenche array de caminho; retorna 1 se encontrou */
int encontrarCaminho(BaseConhecimento *b, const char *origem, const char *destino, char caminho[][100], int *quantidade);
  
#endif
