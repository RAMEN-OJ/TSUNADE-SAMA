#include <stdlib.h>

#include "vocabulario.h"

Vocabulario *criarVocabulario(void)
{
    Vocabulario *v =
        malloc(sizeof(Vocabulario));

    v->trie =
        criarTrie();

    return v;
}

void destruirVocabulario(
        Vocabulario *v)
{
    destruirTrie(v->trie);

    free(v);
}

Intencao interpretarPalavra(
        Vocabulario *v,
        const char *palavra)
{
    return procurarPalavraTrie(
                v->trie,
                palavra);
}

void carregarVocabularioPadrao(
        Vocabulario *v)
{
    inserirPalavraTrie(
        v->trie,
        "ola",
        INTENCAO_SAUDACAO);

    inserirPalavraTrie(
    v->trie,
    "perdi",
    INTENCAO_EMOCIONAL);

inserirPalavraTrie(
    v->trie,
    "brinquedo",
    INTENCAO_EMOCIONAL);

inserirPalavraTrie(
    v->trie,
    "chorar",
    INTENCAO_EMOCIONAL);

inserirPalavraTrie(
    v->trie,
    "sozinho",
    INTENCAO_EMOCIONAL);

inserirPalavraTrie(
    v->trie,
    "medo",
    INTENCAO_EMOCIONAL);
    inserirPalavraTrie(
        v->trie,
        "oi",
        INTENCAO_SAUDACAO);

    inserirPalavraTrie(
        v->trie,
        "historia",
        INTENCAO_HISTORIA);

    inserirPalavraTrie(
        v->trie,
        "conto",
        INTENCAO_HISTORIA);

    inserirPalavraTrie(
        v->trie,
        "matematica",
        INTENCAO_ESTUDO);

    inserirPalavraTrie(
        v->trie,
        "estudar",
        INTENCAO_ESTUDO);

    inserirPalavraTrie(
        v->trie,
        "jogar",
        INTENCAO_JOGO);

    inserirPalavraTrie(
        v->trie,
        "triste",
        INTENCAO_EMOCIONAL);

    inserirPalavraTrie(
        v->trie,
        "feliz",
        INTENCAO_EMOCIONAL);

    inserirPalavraTrie(
        v->trie,
        "ajuda",
        INTENCAO_AJUDA);

    inserirPalavraTrie(
        v->trie,
        "adeus",
        INTENCAO_DESPEDIDA);
}
