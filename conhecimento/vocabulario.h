/* ==========================================================================
 * vocabulario.h — Léxico de intenções
 *
 * Encapsula a trie de palavras-chave e expõe a API para interpretar
 * tokens de entrada e carregar o vocabulário predefinido da Tsunade.
 * ========================================================================== */

#ifndef VOCABULARIO_H
#define VOCABULARIO_H

#include "../estruturas/trie.h"

/** Contêiner do léxico baseado em trie de intenções. */
typedef struct {

    Trie *trie;

} Vocabulario;

/** Aloca e inicializa um vocabulário vazio. */
Vocabulario *criarVocabulario(void);

/** Liberta a trie e o vocabulário. */
void destruirVocabulario(Vocabulario *v);

/** Carrega palavras predefinidas associadas a cada intenção. */
void carregarVocabularioPadrao(Vocabulario *v);

/** Devolve a intenção associada a uma palavra, ou DESCONHECIDA. */
Intencao interpretarPalavra(Vocabulario *v, const char *palavra);

#endif
