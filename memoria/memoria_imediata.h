/* ==========================================================================
 * memoria_imediata.h — Memória imediata (buffer circular)
 *
 * Buffer circular de mensagens recentes da conversa para contexto
 * de curto prazo e diagnóstico administrativo.
 * ========================================================================== */

#ifndef MEMORIA_IMEDIATA_H
#define MEMORIA_IMEDIATA_H

#define TAM_MEMORIA 10
#define TAM_MSG 256

/** Buffer circular de mensagens recentes da sessão. */
typedef struct {

    char mensagens[TAM_MEMORIA][TAM_MSG];

    int inicio;

    int fim;

    int total;

} MemoriaImediata;

/** Cria buffer circular de memória imediata vazio. */
MemoriaImediata *criarMemoriaImediata(void);

/** Liberta a estrutura de memória imediata. */
void destruirMemoriaImediata(MemoriaImediata *m);

/** Adiciona mensagem ao buffer, descartando a mais antiga se cheio. */
void adicionarMensagem(MemoriaImediata *m, const char *msg);

/** Imprime mensagens recentes para diagnóstico. */
void mostrarMemoriaImediata(MemoriaImediata *m);

/** Reinicia o buffer circular de memória imediata. */
void limparMemoriaImediata(MemoriaImediata *m);

#endif
