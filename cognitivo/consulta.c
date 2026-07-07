/*======================================================================
  consulta.c
  Respostas a consultas sobre perfil da criança e conhecimento semântico.
  Interpreta perguntas e devolve dados armazenados no perfil ou grafo.
======================================================================*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "consulta.h"

/* Responde perguntas sobre dados pessoais do perfil; retorna 1 se respondeu */
int responderConsulta(PerfilCrianca *perfil, const char *frase, char *resposta)
{
    char copia[256];

    if(perfil == NULL || frase == NULL || resposta == NULL)
        return 0;

    strcpy(copia, frase);

    for(int i = 0; copia[i]; i++)
        copia[i] = (char)tolower((unsigned char)copia[i]);

    /* --- consultas de identidade --- */
    if(strstr(copia, "qual") && (strstr(copia, "nome") || strstr(copia, "me chamo")))
    {
        if(strlen(perfil->nome) > 0)
            snprintf(resposta, 512, "O teu nome é %s.", perfil->nome);
        else
            snprintf(resposta, 512, "Ainda não sei o teu nome. Podes dizer-me?");
        return 1;
    }

    if(strstr(copia, "qual") && strstr(copia, "idade"))
    {
        if(perfil->idade > 0)
            snprintf(resposta, 512, "Tens %d anos.", perfil->idade);
        else
            snprintf(resposta, 512, "Ainda não sei a tua idade.");
        return 1;
    }

    /* --- consultas de preferências --- */
    if(strstr(copia, "qual") && strstr(copia, "cor favorita"))
    {
        if(strlen(perfil->corFavorita) > 0)
            snprintf(resposta, 512, "A tua cor favorita é %s.", perfil->corFavorita);
        else
            snprintf(resposta, 512, "Ainda não sei a tua cor favorita.");
        return 1;
    }

    if(strstr(copia, "qual") && strstr(copia, "animal favorito"))
    {
        if(strlen(perfil->animalFavorito) > 0)
            snprintf(resposta, 512, "O teu animal favorito é %s.", perfil->animalFavorito);
        else
            snprintf(resposta, 512, "Ainda não sei o teu animal favorito.");
        return 1;
    }

    if(strstr(copia, "qual") && strstr(copia, "comida favorita"))
    {
        if(strlen(perfil->comidaFavorita) > 0)
            snprintf(resposta, 512, "A tua comida favorita é %s.", perfil->comidaFavorita);
        else
            snprintf(resposta, 512, "Ainda não sei a tua comida favorita.");
        return 1;
    }

    /* --- resumo do perfil --- */
    if(strstr(copia, "o que sabes sobre mim") || strstr(copia, "o que sabes de mim"))
    {
        if(strlen(perfil->nome) == 0)
        {
            snprintf(resposta, 512, "Ainda estou a conhecer-te. Conta-me mais sobre ti!");
            return 1;
        }

        snprintf(resposta, 512, "Sei que te chamas %s.", perfil->nome);

        if(perfil->idade > 0)
        {
            strncat(resposta, " Tens ", 512 - strlen(resposta) - 1);
            char idade[16];
            snprintf(idade, sizeof(idade), "%d", perfil->idade);
            strncat(resposta, idade, 512 - strlen(resposta) - 1);
            strncat(resposta, " anos.", 512 - strlen(resposta) - 1);
        }
        if(strlen(perfil->animalFavorito) > 0)
        {
            strncat(resposta, " Gostas de ", 512 - strlen(resposta) - 1);
            strncat(resposta, perfil->animalFavorito, 512 - strlen(resposta) - 1);
            strncat(resposta, ".", 512 - strlen(resposta) - 1);
        }
        return 1;
    }

    return 0;
}

/* Lista todas as relações conhecidas sobre um conceito no grafo; retorna 1 se encontrou */
int consultarConhecimento(BaseConhecimento *base, const char *conceito, char *resposta)
{
    resposta[0] = '\0';

    NoSemantico *no = procurarNoSemantico(base, conceito);

    if(no == NULL)
        return 0;

    strcat(resposta, "Sei que:\n");

    /* --- percorrer vizinhos --- */
    Vizinho *v = no->adjacentes;

    while(v)
    {
        strcat(resposta, "- ");
        strcat(resposta, no->conceito);
        strcat(resposta, " ");
        strcat(resposta, v->relacao);
        strcat(resposta, " ");
        strcat(resposta, v->destino);
        strcat(resposta, "\n");

        v = v->proximo;
    }

    return 1;
}

/* Alias para consultarConhecimento; retorna 1 se respondeu */
int responderConsultaSemantica(BaseConhecimento *b, const char *conceito, char *resposta)
{
    return consultarConhecimento(b, conceito, resposta);
}
