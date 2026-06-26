#ifndef TRIE_H
#define TRIE_H

#include "../cognitivo/interpretador.h"

#define ALFABETO 26

typedef struct TrieNo {

    struct TrieNo *filhos[ALFABETO];

    int fimPalavra;

    Intencao intencao;

} TrieNo;

typedef struct {

    TrieNo *raiz;

} Trie;

Trie *criarTrie(void);

void destruirTrie(Trie *trie);

void inserirPalavraTrie(
        Trie *trie,
        const char *palavra,
        Intencao intencao);

Intencao procurarPalavraTrie(
        Trie *trie,
        const char *palavra);

#endif
