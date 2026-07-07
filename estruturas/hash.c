/* ==========================================================================
 * hash.c — Tabela hash encadeada
 *
 * Implementação de tabela hash com encadeamento por colisão, função
 * de dispersão polinomial e operações de inserção e procura.
 * ========================================================================== */

#include <stdlib.h>
#include <string.h>

#include "hash.h"

/**
 * Calcula o índice do bucket para uma chave string.
 */
static unsigned hashString(const char *s)
{
    unsigned h = 0;

    while(*s)
    {
        h = 31 * h + (unsigned char)*s;
        s++;
    }

    return h % HASH_SIZE;
}

/**
 * Aloca uma tabela hash com todos os buckets inicializados a NULL.
 */
Hash *criarHash(void)
{
    Hash *h = malloc(sizeof(Hash));

    if(h == NULL)
        return NULL;

    for(int i = 0; i < HASH_SIZE; i++)
        h->buckets[i] = NULL;

    return h;
}

/**
 * Liberta todos os nós encadeados e a estrutura da tabela hash.
 */
void destruirHash(Hash *h)
{
    if(h == NULL)
        return;

    for(int i = 0; i < HASH_SIZE; i++)
    {
        HashNo *atual = h->buckets[i];

        while(atual)
        {
            HashNo *prox = atual->proximo;
            free(atual);
            atual = prox;
        }
    }

    free(h);
}

/**
 * Insere um par chave-valor na cabeça do bucket correspondente.
 */
void inserirHash(Hash *h, const char *chave,void *valor)
{
    unsigned pos = hashString(chave);

    HashNo *n = malloc(sizeof(HashNo));

    strcpy(n->chave,chave);

    n->valor = valor;

    n->proximo = h->buckets[pos];

    h->buckets[pos] = n;
}

/**
 * Procura um valor pela chave percorrendo a lista do bucket.
 */
void *procurarHash(Hash *h, const char *chave)
{
    unsigned pos = hashString(chave);

    HashNo *n = h->buckets[pos];

    while(n)
    {
        if(strcmp(n->chave,chave)==0)
            return n->valor;

        n = n->proximo;
    }

    return NULL;
}
