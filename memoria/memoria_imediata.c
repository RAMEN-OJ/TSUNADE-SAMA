#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoria_imediata.h"

MemoriaImediata *criarMemoriaImediata(void)
{
    MemoriaImediata *m = malloc(sizeof(MemoriaImediata));

    if(m == NULL)
    {
        printf("Erro ao criar memÃÂ³ria.\n");
        exit(1);
    }

    m->inicio = 0;
    m->fim = 0;
    m->total = 0;

    return m;
}

void destruirMemoriaImediata(MemoriaImediata *m)
{
    if(m != NULL)
        free(m);
}

void adicionarMensagem(MemoriaImediata *m, const char *msg)
{
    if(m == NULL)
        return;

    strncpy(
        m->mensagens[m->fim],
        msg,
        TAM_MSG - 1
    );

    m->mensagens[m->fim][TAM_MSG - 1] = '\0';

    m->fim = (m->fim + 1) % TAM_MEMORIA;

    if(m->total < TAM_MEMORIA)
    {
        m->total++;
    }
    else
    {
        m->inicio =
            (m->inicio + 1) % TAM_MEMORIA;
    }
}

void mostrarMemoriaImediata(MemoriaImediata *m)
{
    if(m == NULL)
        return;

    printf("\n");
    printf("=== MEMORIA IMEDIATA ===\n");

    int pos = m->inicio;

    for(int i = 0; i < m->total; i++)
    {
        printf("%d. %s\n",
               i + 1,
               m->mensagens[pos]);

        pos =
            (pos + 1) % TAM_MEMORIA;
    }

    printf("========================\n");
}
