#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 211

typedef struct HashNo
{
    char chave[100];

    void *valor;

    struct HashNo *proximo;

} HashNo;

typedef struct
{
    HashNo *buckets[HASH_SIZE];

} Hash;

Hash *criarHash(void);

void destruirHash(Hash *);

void inserirHash(
        Hash *,
        const char *,
        void *);

void *procurarHash(
        Hash *,
        const char *);

#endif