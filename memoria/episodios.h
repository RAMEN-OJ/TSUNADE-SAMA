/* ==========================================================================
 * episodios.h — Memória episódica
 *
 * Registo de episódios textuais significativos da interacção, com
 * limite fixo e persistência em ficheiro.
 * ========================================================================== */

#ifndef EPISODIOS_H
#define EPISODIOS_H

#define MAX_EPISODIOS 100

/** Entrada individual de memória episódica (texto descritivo). */
typedef struct
{
    char texto[256];
}
Episodio;

/** Coleção circular/limitada de episódios memorizados. */
typedef struct
{
    Episodio lista[MAX_EPISODIOS];
    int quantidade;
}
MemoriaEpisodica;

/** Cria memória episódica vazia. */
MemoriaEpisodica *criarMemoriaEpisodica(void);

/** Liberta a estrutura de memória episódica. */
void destruirMemoriaEpisodica(MemoriaEpisodica *m);

/** Adiciona um episódio textual se ainda houver capacidade. */
void adicionarEpisodio(MemoriaEpisodica *m, const char *texto);

/** Grava episódios em dados/episodios.dat. */
void salvarEpisodios(MemoriaEpisodica *m);

/** Carrega episódios a partir de dados/episodios.dat. */
void carregarEpisodios(MemoriaEpisodica *m);

#endif
