#include <stdlib.h>
#include <string.h>

#include "hash.h"

static unsigned hashString(
        const char *s)
{
    unsigned h = 0;

    while(*s)
    {
        h = 31 * h + (unsigned char)*s;
        s++;
    }

    return h % HASH_SIZE;
}

Hash *criarHash(void)
{
    Hash *h = malloc(sizeof(Hash));

    if(h == NULL)
        return NULL;

    for(int i = 0; i < HASH_SIZE; i++)
        h->buckets[i] = NULL;

    return h;
}

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

void inserirHash(
        Hash *h,
        const char *chave,
        void *valor)
{
    unsigned pos = hashString(chave);

    HashNo *n = malloc(sizeof(HashNo));

    strcpy(n->chave,chave);

    n->valor = valor;

    n->proximo = h->buckets[pos];

    h->buckets[pos] = n;
}

void *procurarHash(
        Hash *h,
        const char *chave)
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
   
