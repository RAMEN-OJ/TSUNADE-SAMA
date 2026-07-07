/* ==========================================================================
 * conceitos.c — Base de conhecimento semântico
 *
 * Implementa a gestão de relações sujeito-relação-objeto, o índice hash
 * para acesso rápido e o grafo de nós semânticos com vizinhos rotulados.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conceitos.h"
#include "../core/dados.h"
#include "grafo_inferencia.h"

/**
 * Procura um nó semântico no índice hash da base de conhecimento.
 */
static NoSemantico *buscarNoSemantico(BaseConhecimento *b, const char *conceito)
{
    return (NoSemantico *)
            procurarHash(b->indice, conceito);
}

/**
 * Cria um novo nó semântico, insere-o no grafo e regista-o no índice hash.
 */
static NoSemantico *criarNoSemantico(BaseConhecimento *b, const char *conceito)
{
    NoSemantico *novo = malloc(sizeof(NoSemantico));

    if(novo==NULL)
        return NULL;

    strcpy(novo->conceito, conceito);

    novo->adjacentes = NULL;

    novo->proximo = b->grafo;

    b->grafo = novo;

    inserirHash(b->indice, conceito, novo);

    return novo;
}

/**
 * Adiciona uma aresta rotulada entre um nó de origem e um conceito destino.
 */
static void adicionarVizinho(NoSemantico *origem, const char *relacao, const char *destino)
{
    Vizinho *v = malloc(sizeof(Vizinho));

    if(v==NULL)
        return;

    strcpy(v->relacao,relacao);

    strcpy(v->destino,destino);

    v->proximo = origem->adjacentes;

    origem->adjacentes = v;
}

/**
 * Aloca e inicializa uma base de conhecimento vazia com índice hash.
 */
BaseConhecimento *criarBaseConhecimento(void)
{
    BaseConhecimento *b = malloc(sizeof(BaseConhecimento));

    if(b == NULL)
        return NULL;

    b->quantidade = 0;

    b->indice = criarHash();
    b->grafo = NULL;
    return b;
}

/**
 * Liberta todos os nós semânticos e arestas do grafo.
 */
static void liberarGrafoSemantico(NoSemantico *no)
{
    while(no != NULL)
    {
        Vizinho *v = no->adjacentes;

        while(v != NULL)
        {
            Vizinho *proxV = v->proximo;
            free(v);
            v = proxV;
        }

        {
            NoSemantico *proxN = no->proximo;
            free(no);
            no = proxN;
        }
    }
}

/**
 * Liberta o índice hash, o grafo semântico e a estrutura da base.
 */
void destruirBaseConhecimento(BaseConhecimento *b)
{
    if(b == NULL)
        return;

    liberarGrafoSemantico(b->grafo);
    b->grafo = NULL;
    destruirHash(b->indice);
    free(b);
}

/**
 * Regista ou actualiza uma relação semântica e reflecte-a no grafo.
 */
void adicionarRelacao(BaseConhecimento *b, const char *sujeito,const char *relacao, const char *objeto)
{
    int i;
    NoSemantico *origem;
    Vizinho *v;

    for(i = 0; i < b->quantidade; i++)
    {
        if(strcmp(b->lista[i].sujeito, sujeito) == 0 &&
           strcmp(b->lista[i].relacao, relacao) == 0)
        {
            strcpy(b->lista[i].objeto, objeto);

            origem = buscarNoSemantico(b, sujeito);
            if(origem != NULL)
            {
                for(v = origem->adjacentes; v != NULL; v = v->proximo)
                {
                    if(strcmp(v->relacao, relacao) == 0)
                    {
                        strcpy(v->destino, objeto);
                        return;
                    }
                }
                adicionarVizinho(origem, relacao, objeto);
            }
            return;
        }
    }

    if(b->quantidade >= MAX_CONCEITOS)
        return;

    strcpy(b->lista[b->quantidade].sujeito, sujeito);
    strcpy(b->lista[b->quantidade].relacao, relacao);
    strcpy(b->lista[b->quantidade].objeto, objeto);
    b->quantidade++;

    origem = buscarNoSemantico(b, sujeito);
    if(origem == NULL)
        origem = criarNoSemantico(b, sujeito);

    adicionarVizinho(origem, relacao, objeto);
}

/**
 * Procura a primeira relação registada para um dado sujeito na lista plana.
 */
Relacao *procurarRelacao(BaseConhecimento *b, const char *sujeito)
{
    NoSemantico *no = procurarHash(b->indice, sujeito);

    if(no == NULL)
        return NULL;

    for(int i = 0; i < b->quantidade; i++)
    {
        if(strcmp(b->lista[i].sujeito, sujeito) == 0)
        {
            return &b->lista[i];
        }
    }
    return NULL;
}

/**
 * Persiste todas as relações da base no ficheiro dados/conhecimento.dat.
 */
void salvarConhecimento(BaseConhecimento *b)
{
    FILE *f;
    int i;

    if(b == NULL)
        return;

    if(!garantirDiretorioDados())
        return;

    f = fopen("dados/conhecimento.dat", "w");

    if(f == NULL)
        return;

    for(i = 0; i < b->quantidade; i++)
    {
        fprintf(f, "%s|%s|%s\n",
                b->lista[i].sujeito,
                b->lista[i].relacao,
                b->lista[i].objeto);
    }
    fclose(f);
}

/**
 * Carrega relações persistidas e reconstrói o grafo semântico.
 */
void carregarConhecimento(BaseConhecimento *b)
{
    FILE *f;
    char linha[500];

    if(b == NULL)
        return;

    f = fopen("dados/conhecimento.dat", "r");

    if(f == NULL)
        return;

    while(fgets(linha, sizeof(linha), f))
    {
        char *sujeito;
        char *relacao;
        char *objeto;

        linha[strcspn(linha, "\n")] = '\0';

        sujeito = strtok(linha, "|");
        relacao = strtok(NULL, "|");
        objeto = strtok(NULL, "|");

        if(sujeito && relacao && objeto)
            adicionarRelacaoNormalizada(b, sujeito, relacao, objeto);
    }

    fclose(f);
}

/**
 * Imprime o grafo semântico completo no ecrã para diagnóstico.
 */
void imprimirGrafo(BaseConhecimento *b)
{
    printf("\n========== GRAFO ==========\n");

    NoSemantico *n = b->grafo;

    while(n)
    {
        printf("%s\n", n->conceito);

        Vizinho *v = n->adjacentes;

        while(v)
        {
            printf("   |--%s--> %s\n",
                   v->relacao,
                   v->destino);

            v = v->proximo;
        }

        printf("\n");

        n = n->proximo;
    }

    printf("===========================\n");
}

/**
 * Expõe a procura de nó semântico via índice hash (interface pública).
 */
NoSemantico *procurarNoSemantico(BaseConhecimento *b, const char *conceito)
{
    return (NoSemantico *)
            procurarHash(b->indice, conceito);
}
