/*======================================================================
  parser.c
  Analisador sintático de frases em português.
  Tokeniza texto e classifica em tipos de ação (perfil, consulta, conhecimento, etc.).
======================================================================*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "interpretacao.h"
#include "parser.h"

/* --- estrutura interna do parser --- */
#define MAX_TOKENS 20
#define MAX_TOKEN 50

typedef struct
{
    char palavras[MAX_TOKENS][MAX_TOKEN];
    int quantidade;

} Parser;

static void classificar(Parser *p, Interpretacao *i);

/* Tokeniza frase em palavras minúsculas, ignorando pontuação; parâmetros: frase, p (saída) */
static void analisarTexto(const char *frase, Parser *p)
{
    p->quantidade = 0;

    int i = 0;
    int j = 0;

    while(frase[i] != '\0')
    {
        /* --- ignorar espaços --- */
        while(frase[i] == ' ' ||
              frase[i] == '\n' ||
              frase[i] == '\t')
        {
            i++;
        }

        if(frase[i] == '\0')
            break;

        j = 0;

        /* --- extrair token --- */
        while(frase[i] != '\0' &&
              frase[i] != ' ' &&
              frase[i] != '\n' &&
              frase[i] != '\t' &&
              frase[i] != '?' &&
              frase[i] != '.' &&
              frase[i] != ',' &&
              frase[i] != '!')
        {
            p->palavras[p->quantidade][j++] =
                tolower((unsigned char)frase[i]);

            i++;
        }

        p->palavras[p->quantidade][j] = '\0';
        p->quantidade++;

        if(p->quantidade >= MAX_TOKENS)
            break;
    }
}

/* Analisa frase completa: tokeniza e classifica; preenche inter com tipo e entidades */
void interpretarFrase(const char *frase, Interpretacao *inter)      
{
    Parser p;

    analisarTexto(frase, &p);
    classificar(&p, inter);
}

/* Classifica tokens numa Interpretacao com sujeito, relação e objeto; parâmetros: p, i (saída) */
static void classificar(Parser *p, Interpretacao *i)        
{
    memset(i,0,sizeof(*i));

    i->tipo = ACAO_DESCONHECIDA;

    if(p->quantidade==0)
        return;

    /* --- saudação --- */
    if(strcmp(p->palavras[0],"ola")==0 ||
       strcmp(p->palavras[0],"olá")==0 ||
       strcmp(p->palavras[0],"oi")==0)
    {
        i->tipo=ACAO_SAUDACAO;
        return;
    }

    /* --- perfil (nome) --- */
    if(p->quantidade>=4)
    {
        if(strcmp(p->palavras[0],"meu")==0 &&
           strcmp(p->palavras[1],"nome")==0)
        {
            i->tipo=ACAO_PERFIL;

            strcpy(i->sujeito,"eu");
            strcpy(i->relacao,"nome");

            strcpy(i->objeto,p->palavras[3]);

            for(int k=4;k<p->quantidade;k++)
            {
                strcat(i->objeto," ");
                strcat(i->objeto,p->palavras[k]);
            }

            return;
        }
    }

    /* --- consultas diretas --- */
    if(strcmp(p->palavras[0],"quem")==0 ||
       strcmp(p->palavras[0],"qual")==0 ||
       strcmp(p->palavras[0],"onde")==0 ||
       strcmp(p->palavras[0],"o")==0)
    {
        i->tipo=ACAO_CONSULTA;
        return;
    }

    /* --- inferência (fala/conta sobre) --- */
    if(p->quantidade >= 4)
    {
        if((strcmp(p->palavras[0],"o")==0 && strcmp(p->palavras[1],"que")==0 &&
            strcmp(p->palavras[2],"sabes")==0 && strcmp(p->palavras[3],"sobre")==0) ||
           (strcmp(p->palavras[0],"fala")==0 && strcmp(p->palavras[1],"sobre")==0) ||
           (strcmp(p->palavras[0],"fala-me")==0 && strcmp(p->palavras[1],"sobre")==0) ||
           (strcmp(p->palavras[0],"conta-me")==0 && strcmp(p->palavras[1],"sobre")==0) ||
           (strcmp(p->palavras[0],"conta")==0 && strcmp(p->palavras[1],"sobre")==0))
        {
            int inicio = 4;
            int k;

            if(strcmp(p->palavras[0],"fala")==0 || strcmp(p->palavras[0],"conta")==0 ||
               strcmp(p->palavras[0],"fala-me")==0 || strcmp(p->palavras[0],"conta-me")==0)
                inicio = 2;

            i->tipo = ACAO_INFERENCIA;
            i->objeto[0] = '\0';

            for(k = inicio; k < p->quantidade; k++)
            {
                if(k != inicio)
                    strcat(i->objeto, " ");
                strcat(i->objeto, p->palavras[k]);
            }

            return;
        }
    }

    /* --- conhecimento (sujeito é/foi/tem objeto) --- */
    for(int k=1;k<p->quantidade;k++)
    {
        if(strcmp(p->palavras[k],"é")==0 || strcmp(p->palavras[k],"e")==0 ||
           strcmp(p->palavras[k],"fica")==0 || strcmp(p->palavras[k],"tem")==0) 
        {
            i->tipo=ACAO_CONHECIMENTO;

            strcpy(i->sujeito,p->palavras[0]);
            strcpy(i->relacao,p->palavras[k]);

            i->objeto[0]='\0';

            for(int j=k+1;j<p->quantidade;j++)
            {
                if(j!=k+1)
                    strcat(i->objeto," ");

                strcat(i->objeto,p->palavras[j]);
            }

            return;
        }
    }

    /* --- memória --- */
    if(strcmp(p->palavras[0],"lembra")==0 || strcmp(p->palavras[0],"aprendi")==0) 
    {
        i->tipo=ACAO_MEMORIA;
        return;
    }

    /* --- estudo --- */
    if(strcmp(p->palavras[0],"quanto")==0 || strcmp(p->palavras[0],"calcula")==0) 
    {
        i->tipo=ACAO_ESTUDO;
        return;
    }
}
