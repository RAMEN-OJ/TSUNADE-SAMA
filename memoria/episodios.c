/* ==========================================================================
 * episodios.c — Memória episódica
 *
 * Gestão de episódios memorizados e persistência em ficheiro de texto.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "episodios.h"
#include "../core/dados.h"

/**
 * Aloca estrutura de memória episódica sem episódios registados.
 */
MemoriaEpisodica *criarMemoriaEpisodica(void)
{
    MemoriaEpisodica *m = malloc(sizeof(MemoriaEpisodica));

    m->quantidade = 0;

    return m;
}

/**
 * Liberta a memória episódica.
 */
void destruirMemoriaEpisodica(MemoriaEpisodica *m)
{
    free(m);
}

/**
 * Regista um novo episódio até ao limite MAX_EPISODIOS.
 */
void adicionarEpisodio(MemoriaEpisodica *m, const char *texto)
{
    if(m->quantidade >= MAX_EPISODIOS)
        return;

    strcpy(m->lista[m->quantidade].texto, texto);

    m->quantidade++;
}

/**
 * Persiste a quantidade e textos dos episódios em disco.
 */
void salvarEpisodios(MemoriaEpisodica *m)
{
    FILE *f;
    int i;

    if(m == NULL)
        return;

    if(!garantirDiretorioDados())
        return;

    f = fopen("dados/episodios.dat", "w");

    if(f == NULL)
        return;

    fprintf(f, "%d\n", m->quantidade);

    for(i = 0; i < m->quantidade; i++)
        fprintf(f, "%s", m->lista[i].texto);

    fclose(f);
}

/**
 * Restaura episódios previamente gravados a partir de disco.
 */
void carregarEpisodios(MemoriaEpisodica *m)
{
    FILE *f = fopen("dados/episodios.dat", "r");

    if(!f)
        return;

    fscanf(f, "%d\n", &m->quantidade);

    for(int i = 0; i < m->quantidade; i++)
    {
        fgets(m->lista[i].texto, sizeof(m->lista[i].texto), f);
    }

    fclose(f);
}
