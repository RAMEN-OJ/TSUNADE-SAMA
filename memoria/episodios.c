#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "episodios.h"

MemoriaEpisodica *criarMemoriaEpisodica(void)
{
    MemoriaEpisodica *m =
        malloc(sizeof(MemoriaEpisodica));

    m->quantidade = 0;

    return m;
}

void destruirMemoriaEpisodica(
        MemoriaEpisodica *m)
{
    free(m);
}

void adicionarEpisodio(
        MemoriaEpisodica *m,
        const char *texto)
{
    if(m->quantidade >= MAX_EPISODIOS)
        return;

    strcpy(
        m->lista[m->quantidade].texto,
        texto);

    m->quantidade++;
}

void salvarEpisodios(
        MemoriaEpisodica *m)
{
    FILE *f =
        fopen(
            "dados/episodios.dat",
            "w");

    if(!f)
        return;

    fprintf(
        f,
        "%d\n",
        m->quantidade);

    for(int i = 0;
        i < m->quantidade;
        i++)
    {
        fprintf(
            f,
            "%s",
            m->lista[i].texto);
    }

    fclose(f);
}

void carregarEpisodios(
        MemoriaEpisodica *m)
{
    FILE *f =
        fopen(
            "dados/episodios.dat",
            "r");

    if(!f)
        return;

    fscanf(
        f,
        "%d\n",
        &m->quantidade);

    for(int i = 0;
        i < m->quantidade;
        i++)
    {
        fgets(
            m->lista[i].texto,
            sizeof(m->lista[i].texto),
            f);
    }

    fclose(f);
}
