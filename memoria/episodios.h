#ifndef EPISODIOS_H
#define EPISODIOS_H

#define MAX_EPISODIOS 100

typedef struct
{
    char texto[256];
}
Episodio;

typedef struct
{
    Episodio lista[MAX_EPISODIOS];
    int quantidade;
}
MemoriaEpisodica;

MemoriaEpisodica *criarMemoriaEpisodica(void);

void destruirMemoriaEpisodica(
        MemoriaEpisodica *m);

void adicionarEpisodio(
        MemoriaEpisodica *m,
        const char *texto);

void salvarEpisodios(
        MemoriaEpisodica *m);

void carregarEpisodios(
        MemoriaEpisodica *m);

#endif
