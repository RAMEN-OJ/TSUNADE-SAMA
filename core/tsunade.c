#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tsunade.h"

Tsunade *criarTsunade(void)
{
    Tsunade *t = malloc(sizeof(Tsunade));

    if(t == NULL)
    {
        printf("Erro ao criar Tsunade.\n");
        exit(1);
    }

    strcpy(t->nome, "Tsunade-Sama");

    t->ativa = 1;

    /* MEMÓRIA */

    t->memoria = criarMemoriaImediata();

    t->episodios = criarMemoriaEpisodica();
    carregarEpisodios(t->episodios);

    t->perfil = criarPerfil();
    carregarPerfil(t->perfil);

    /* CONHECIMENTO */

    t->conhecimento = criarBaseConhecimento();
    carregarConhecimento(t->conhecimento);

    t->vocabulario = criarVocabulario();
    carregarVocabularioPadrao(t->vocabulario);

    /* CONTEXTO */

    t->contexto = criarContexto();

    /* EMOÇÕES */

    t->emocao = criarEmocoes();

    /* EDUCAÇÃO */

    t->educacao = criarEducacao();
printf("educacao criada = %p\n", (void *)t->educacao);
    if(t->educacao == NULL)
    {
        printf("Erro ao criar módulo de educação.\n");
        free(t);
        exit(1);
    }

    t->moduloPais = NULL;
    t->moduloAdministrador = NULL;

    return t;
}

void destruirTsunade(Tsunade *t)
{
    if(t == NULL)
        return;

    salvarPerfil(t->perfil);
    salvarEpisodios(t->episodios);
    salvarConhecimento(t->conhecimento);

    destruirPerfil(t->perfil);
    destruirMemoriaEpisodica(t->episodios);
    destruirMemoriaImediata(t->memoria);

    destruirBaseConhecimento(t->conhecimento);
    destruirVocabulario(t->vocabulario);

    destruirContexto(t->contexto);

    destruirEmocoes(t->emocao);

    destruirEducacao(t->educacao);

    free(t);
}