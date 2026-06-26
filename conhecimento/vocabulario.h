#ifndef VOCABULARIO_H
#define VOCABULARIO_H

#include "../estruturas/trie.h"

typedef struct {

    Trie *trie;

} Vocabulario;

Vocabulario *criarVocabulario(void);

void destruirVocabulario(
        Vocabulario *v);

void carregarVocabularioPadrao(
        Vocabulario *v);

Intencao interpretarPalavra(
        Vocabulario *v,
        const char *palavra);

#endif
