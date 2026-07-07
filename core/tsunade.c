/*======================================================================
  tsunade.c
  Implementação do ciclo de vida da entidade Tsunade.
  Cria, inicializa e destrói todos os submódulos de memória e conhecimento.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tsunade.h"
#include "dados.h"
#include "../conhecimento/grafo_inferencia.h"

/* Aloca Tsunade e inicializa memória, conhecimento, contexto e emoções; retorna ponteiro */
Tsunade *criarTsunade(void)
{
    Tsunade *t = malloc(sizeof(Tsunade));
       
    if(t == NULL)
    {
        printf("Erro ao criar Tsunade.\n");
        exit(1);
    }

    strcpy(t->nome,"Tsunade-Sama");
    t->ativa = 1;

    garantirDiretorioDados();

    /* --- memória --- */
    t->memoria = criarMemoriaImediata();
    t->episodios = criarMemoriaEpisodica();
    carregarEpisodios(t->episodios);  
    t->perfil = criarPerfil();
    carregarPerfil(t->perfil);

    /* --- conhecimento --- */
    t->conhecimento = criarBaseConhecimento();
    carregarConhecimento(t->conhecimento);
    carregarSinonimosPadrao(t->conhecimento);
    t->vocabulario = criarVocabulario();
    carregarVocabularioPadrao(t->vocabulario);

    /* --- contexto --- */
    t->contexto = criarContexto();

    /* --- emoções e educação --- */
    t->emocao = criarEmocoes();
    t->educacao = criarEducacao();
    t->moduloPais = NULL;
    t->moduloAdministrador = NULL;

    return t;
}

/* Persiste perfil, episódios e conhecimento; liberta todos os recursos; parâmetro: t */
void destruirTsunade(Tsunade *t)       
{
    if(t == NULL)
        return;

    /* --- persistência --- */
    salvarPerfil(t->perfil);
    salvarEpisodios(t->episodios);
    salvarConhecimento(t->conhecimento);

    /* --- libertação de recursos --- */
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
