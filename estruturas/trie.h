/* ==========================================================================
 * trie.h — Árvore de prefixos para intenções
 *
 * Estrutura trie que mapeia palavras normalizadas a intenções do
 * interpretador cognitivo da Tsunade.
 * ========================================================================== */

#ifndef TRIE_H
#define TRIE_H

#include "../cognitivo/interpretador.h"

#define ALFABETO 26

/** Nó interno da trie com filhos alfabéticos e intenção terminal. */
typedef struct TrieNo
{

    struct TrieNo *filhos[ALFABETO];

    int fimPalavra;

    Intencao intencao;

} TrieNo;

/** Contêiner da trie com ponteiro para a raiz. */
typedef struct
{

    TrieNo *raiz;

} Trie;

/** Cria uma trie vazia. */
Trie *criarTrie(void);

/** Liberta todos os nós e a estrutura da trie. */
void destruirTrie(Trie *trie);

/** Insere uma palavra associada a uma intenção na trie. */
void inserirPalavraTrie(Trie *trie, const char *palavra, Intencao intencao);

/** Procura a intenção correspondente a uma palavra na trie. */
Intencao procurarPalavraTrie(Trie *trie, const char *palavra);

#endif
