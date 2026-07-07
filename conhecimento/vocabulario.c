/* ==========================================================================
 * vocabulario.c — Léxico de intenções
 *
 * Gestão do vocabulário da Tsunade: criação da trie, interpretação de
 * palavras e carregamento do léxico predefinido por categoria de intenção.
 * ========================================================================== */

#include <stdlib.h>

#include "vocabulario.h"

/**
 * Aloca um vocabulário com trie vazia pronta para receber palavras.
 */
Vocabulario *criarVocabulario(void){
    Vocabulario *v = malloc(sizeof(Vocabulario));
    v->trie = criarTrie();
    return v;
}

/**
 * Liberta a trie interna e a estrutura do vocabulário.
 */
void destruirVocabulario(Vocabulario *v)
{
    destruirTrie(v->trie);
    free(v);
}

/**
 * Consulta a trie e devolve a intenção associada à palavra dada.
 */
Intencao interpretarPalavra(Vocabulario *v, const char *palavra)
{
    return procurarPalavraTrie(v->trie, palavra);
}


/**
 * Popula a trie com palavras predefinidas agrupadas por intenção
 * (saudação, emocional, história, estudo, jogo, ajuda e despedida).
 */
void carregarVocabularioPadrao(Vocabulario *v) {

    /* ================= SAUDAÇÃO ================= */
    inserirPalavraTrie(v->trie, "ola", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "oi", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "oie", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "alo", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "opa", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "salve", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "bomdia", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "boatarde", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "boanoite", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "tudobem", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "comovai", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "prazer", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "eae", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "bemvindo", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "seja", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "chegou", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "amiguinho", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "amiguinha", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "colega", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "turma", INTENCAO_SAUDACAO);

    /* ================= EMOCIONAL ================= */
    inserirPalavraTrie(v->trie, "perdi", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "brinquedo", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "chorar", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sozinho", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sozinha", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "medo", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "triste", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "feliz", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "alegre", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "contente", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "animado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "animada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "chateado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "chateada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "bravo", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "brava", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "raiva", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "nervoso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "nervosa", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "assustado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "assustada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "cansado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "cansada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "preocupado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "preocupada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "envergonhado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "timido", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "timida", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "orgulhoso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "orgulhosa", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "amoroso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "carinho", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "abraco", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "beijo", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "saudade", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "amor", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "coracao", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sorriso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "lagrima", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "solidao", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "ciume", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "susto", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "coragem", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "esperanca", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "gratidao", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "paz", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "calma", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "magoa", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "dor", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "doente", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "estou", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sinto", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sentir", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sentimento", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "mal", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "aborrecido", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "aborrecida", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "desanimado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "desanimada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "frustrado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "frustrada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "zangado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "zangada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "irritado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "irritada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "ansioso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "ansiosa", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "inquieto", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "inquieta", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "receio", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "pavor", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "terror", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "panico", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "angustia", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "desapontado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "desapontada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "comovido", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "comovida", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "emocionado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "emocionada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "surpreso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "surpresa", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "confuso", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "confusa", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "entusiasmado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "entusiasmada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "grato", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "grata", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "aborrecimento", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sofrimento", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "desamparado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "desamparada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "abandonado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "abandonada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "excluido", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "excluida", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "rejeitado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "rejeitada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "magoado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "magoada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "ferido", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "ferida", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "exausto", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "exausta", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sono", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sonolento", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "sonolenta", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "radiante", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "euforico", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "euforica", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "encantado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "encantada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "maravilhado", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "maravilhada", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "confiante", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "inseguro", INTENCAO_EMOCIONAL);
    inserirPalavraTrie(v->trie, "insegura", INTENCAO_EMOCIONAL);

    /* ================= HISTÓRIA ================= */
    inserirPalavraTrie(v->trie, "historia", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "conto", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "fabula", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "lenda", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "aventura", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "principe", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "princesa", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "rei", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "rainha", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "castelo", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "dragao", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "fada", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "bruxa", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "mago", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "heroi", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "heroina", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "vilao", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "floresta", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "gigante", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "anao", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "duende", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "sereia", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "pirata", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "tesouro", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "magia", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "feitico", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "personagem", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "narrar", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "contar", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "livro", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "capitulo", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "unicornio", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "estrela", INTENCAO_HISTORIA);
    inserirPalavraTrie(v->trie, "lua", INTENCAO_HISTORIA);

    /* ================= ESTUDO ================= */
    inserirPalavraTrie(v->trie, "matematica", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "estudar", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "estudo", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "vamos", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "aprender", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "ler", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "escrever", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "numero", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "letra", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "somar", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "subtrair", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "multiplicar", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "dividir", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "portugues", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "ciencias", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "geografia", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "escola", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "professor", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "professora", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "licao", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "dever", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "prova", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "caderno", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "lapis", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "borracha", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "alfabeto", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "silaba", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "palavra", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "frase", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "cor", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "forma", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "animal", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "planeta", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "natureza", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "pergunta", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "resposta", INTENCAO_ESTUDO);

    /* ================= JOGO ================= */
    inserirPalavraTrie(v->trie, "jogar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "brincar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "jogo", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "brincadeira", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "diversao", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "bola", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "boneca", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "boneco", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "carrinho", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "pipa", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "corrida", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "esconde", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "pega", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "quebra", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "cabeca", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "adivinha", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "adivinhar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "charada", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "desafio", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "pular", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "correr", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "dancar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "cantar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "desenhar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "pintar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "colorir", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "montar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "blocos", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "peca", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "ganhar", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "vencer", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "rodada", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "brinquedos", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "parquinho", INTENCAO_JOGO);

    /* ================= AJUDA ================= */
    inserirPalavraTrie(v->trie, "ajuda", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "ajudar", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "socorro", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "preciso", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "quero", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "duvida", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "como", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "porque", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "explica", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "ensina", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "mostra", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "favor", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "obrigado", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "obrigada", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "desculpa", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "entendi", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "repete", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "dificil", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "facil", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "resolver", INTENCAO_AJUDA);

    /* ================= DESPEDIDA ================= */
    inserirPalavraTrie(v->trie, "adeus", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "tchau", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "ate", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "logo", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "amanha", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "depois", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "falou", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "volto", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "durma", INTENCAO_DESPEDIDA);
    inserirPalavraTrie(v->trie, "bem", INTENCAO_DESPEDIDA);

    /* ================= SAUDAÇÃO EXTRA ================= */
    inserirPalavraTrie(v->trie, "hey", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "hello", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "hola", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "yo", INTENCAO_SAUDACAO);
    inserirPalavraTrie(v->trie, "comoestas", INTENCAO_SAUDACAO);

    /* ================= ESTUDO EXTRA ================= */
    inserirPalavraTrie(v->trie, "soma", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "tabuada", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "exercicio", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "conhecimento", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "descobrir", INTENCAO_ESTUDO);
    inserirPalavraTrie(v->trie, "explicar", INTENCAO_ESTUDO);

    /* ================= JOGO EXTRA ================= */
    inserirPalavraTrie(v->trie, "enigma", INTENCAO_JOGO);
    inserirPalavraTrie(v->trie, "quiz", INTENCAO_JOGO);

    /* ================= AJUDA EXTRA ================= */
    inserirPalavraTrie(v->trie, "podes", INTENCAO_AJUDA);
    inserirPalavraTrie(v->trie, "pode", INTENCAO_AJUDA);
}


