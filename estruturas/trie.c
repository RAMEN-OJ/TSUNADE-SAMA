/* ==========================================================================
 * trie.c — Árvore de prefixos para intenções
 *
 * Implementação da trie que associa palavras em minúsculas a intenções
 * do interpretador, suportando inserção, procura e libertação recursiva.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "trie.h"

/**
 * Aloca um nó trie vazio com filhos nulos e intenção desconhecida.
 */
static TrieNo *criarNo(void)
{
    TrieNo *novo = malloc(sizeof(TrieNo));

    if(novo == NULL)
    {
        printf("Erro de memÃÂ³ria.\n");
        exit(1);
    }

    novo->fimPalavra = 0;
    novo->intencao = INTENCAO_DESCONHECIDA;
    for(int i = 0; i < ALFABETO; i++)
    {
        novo->filhos[i] = NULL;
    }

    return novo;

}

/**
 * Cria a estrutura trie com nó raiz inicializado.
 */
Trie *criarTrie(void)
{
    Trie *trie = malloc(sizeof(Trie));

    trie->raiz = criarNo();

    return trie;
}

/**
 * Insere uma palavra na trie, ignorando caracteres fora de a-z.
 */
void inserirPalavraTrie(Trie *trie, const char *palavra, Intencao intencao)
{
    TrieNo *atual = trie->raiz;

    for(int i = 0;
        palavra[i] != '\0';
        i++)
    {
        char c = tolower(palavra[i]);

        if(c < 'a' || c > 'z')
            continue;

        int indice = c - 'a';

        if(atual->filhos[indice] == NULL)
        {
            atual->filhos[indice] =
                criarNo();
        }

        atual =
            atual->filhos[indice];
    }

    atual->fimPalavra = 1;
    atual->intencao = intencao;
}

/**
 * Procura a intenção associada a uma palavra percorrendo a trie.
 */
Intencao procurarPalavraTrie(
        Trie *trie,
        const char *palavra)
{
    TrieNo *atual =
        trie->raiz;

    for(int i = 0;
        palavra[i] != '\0';
        i++)
    {
        char c = tolower(palavra[i]);

        if(c < 'a' || c > 'z')
            continue;

        int indice = c - 'a';

        if(atual->filhos[indice] == NULL)
        {
            return INTENCAO_DESCONHECIDA;
        }

        atual =
            atual->filhos[indice];
    }

    if(atual->fimPalavra)
    {
        return atual->intencao;
    }

    return INTENCAO_DESCONHECIDA;
}

/**
 * Liberta recursivamente a sub-árvore a partir de um nó.
 */
static void destruirNos(
        TrieNo *no)
{
    if(no == NULL)
        return;

    for(int i = 0;
        i < ALFABETO;
        i++)
    {
        destruirNos(
            no->filhos[i]);
    }

    free(no);
}

/**
 * Liberta todos os nós da trie e a estrutura contêiner.
 */
void destruirTrie(
        Trie *trie)
{
    destruirNos(
        trie->raiz);

    free(trie);
}
