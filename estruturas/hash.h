/* ==========================================================================
 * hash.h — Tabela hash encadeada
 *
 * Índice genérico chave-valor usado para acesso rápido a nós semânticos
 * e outros recursos indexados por string.
 * ========================================================================== */

#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 211

/** Entrada de bucket com encadeamento para colisões. */
typedef struct HashNo
{
    char chave[100];

    void *valor;

    struct HashNo *proximo;

} HashNo;

/** Tabela hash com array fixo de buckets. */
typedef struct
{
    HashNo *buckets[HASH_SIZE];

} Hash;

/** Cria uma tabela hash vazia. */
Hash *criarHash(void);

/** Liberta todos os nós e a tabela hash. */
void destruirHash(Hash *);

/** Insere ou substitui um par chave-valor na tabela. */
void inserirHash(Hash *, const char *, void *);

/** Procura um valor pela chave; devolve NULL se não existir. */
void *procurarHash(Hash *, const char *);

#endif
