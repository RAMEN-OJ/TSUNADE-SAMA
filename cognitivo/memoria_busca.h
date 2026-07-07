/*======================================================================
  memoria_busca.h
  Interface de busca na memória episódica e enriquecimento de respostas.
  Recupera episódios passados e complementa respostas com dados do perfil.
======================================================================*/

#ifndef MEMORIA_BUSCA_H
#define MEMORIA_BUSCA_H

#include <stddef.h>

#include "../core/tsunade.h"
#include "../memoria/episodios.h"

/* Busca episódios relevantes na memória episódica; retorna 1 se respondeu */
int buscarMemoria(MemoriaEpisodica *m, const char *frase, char *resposta);

/* Enriquece resposta com dados do perfil quando contextualmente relevante; retorna 1 se adicionou */
int enriquecerComMemoria(Tsunade *t, const char *frase, char *resposta, size_t tamanho);

#endif
