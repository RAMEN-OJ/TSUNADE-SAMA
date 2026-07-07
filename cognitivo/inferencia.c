/*======================================================================
  inferencia.c
  Inferência e pesquisa semântica no grafo de conhecimento.
  Navega relações, herda propriedades e responde consultas complexas.
======================================================================*/

#include <string.h>
#include <stdio.h>

#include "inferencia.h"
#include "../conhecimento/grafo_inferencia.h"
#include "bfs_semantico.h"

/* Verifica existência de caminho entre dois conceitos via BFS; retorna 1 se existe */
int inferirRelacao(BaseConhecimento *base, const char *origem, const char *destino)
{
    char caminho[10][100];
    int quantidade = 0;

    if(base == NULL || origem == NULL || destino == NULL)
        return 0;

    return encontrarCaminho(base, origem, destino, caminho, &quantidade);
}

/* Herda propriedade de um conceito a partir das relações do grafo; retorna 1 se encontrou */
int herdaPropriedade(BaseConhecimento *base, const char *conceito, const char *propriedade, char *origem)
{
    FatoGrafo fatos[MAX_FATOS_GRAFO];
    char alvo[100];
    char propNorm[100];
    int i;
    int total;

    if(base == NULL || conceito == NULL || propriedade == NULL || origem == NULL)
        return 0;

    normalizarConceito(alvo, conceito, sizeof(alvo));
    normalizarRelacao(propNorm, propriedade, sizeof(propNorm));

    total = coletarFatosGrafo(base, alvo, fatos, MAX_FATOS_GRAFO);

    for(i = 0; i < total; i++)
    {
        if(strcmp(fatos[i].relacao, propNorm) == 0)
        {
            strcpy(origem, fatos[i].objeto);
            return 1;
        }
    }

    return 0;
}

/* Responde consulta de inferência sobre um conceito no grafo; retorna 1 se respondeu */
int responderInferencia(BaseConhecimento *base, const char *conceito, char *resposta)
{
    if(base == NULL || conceito == NULL || resposta == NULL)
        return 0;

    return responderConhecimentoGrafo(base, conceito, resposta, 1024);
}

/* Pesquisa conhecimento por texto livre ou conceito extraído; retorna 1 se encontrou */
int pesquisarConhecimento(BaseConhecimento *base, const char *texto, char *resposta)
{
    char conceito[100];

    if(base == NULL || texto == NULL || resposta == NULL)
        return 0;

    /* --- tentativa por conceito extraído --- */
    if(extrairConceitoConsulta(texto, conceito, sizeof(conceito)))
        return responderConhecimentoGrafo(base, conceito, resposta, 1024);

    normalizarConceito(conceito, texto, sizeof(conceito));

    if(responderConhecimentoGrafo(base, conceito, resposta, 1024))
        return 1;

    /* --- busca parcial na lista de fatos --- */
    resposta[0] = '\0';

    for(int i = 0; i < base->quantidade; i++)
    {
        char s[100];
        char o[200];
        char linha[512];

        normalizarConceito(s, base->lista[i].sujeito, sizeof(s));
        normalizarConceito(o, base->lista[i].objeto, sizeof(o));

        if(strstr(s, conceito) || strstr(o, conceito) ||
           strstr(base->lista[i].relacao, conceito))
        {
            snprintf(linha, sizeof(linha), "%s %s %s\n",
                     s, base->lista[i].relacao, o);
            strncat(resposta, linha, 1024 - strlen(resposta) - 1);
        }
    }

    return resposta[0] != '\0';
}

/* Executa pipeline completo de inferência a partir de uma frase; retorna 1 se respondeu */
int executarInferencia(BaseConhecimento *base, const char *frase, char *resposta)
{
    char conceito[100];

    if(base == NULL || frase == NULL || resposta == NULL)
        return 0;

    if(extrairConceitoConsulta(frase, conceito, sizeof(conceito)))
        return responderConhecimentoGrafo(base, conceito, resposta, 1024);

    if(responderConhecimentoGrafo(base, frase, resposta, 1024))
        return 1;

    return pesquisarConhecimento(base, frase, resposta);
}
