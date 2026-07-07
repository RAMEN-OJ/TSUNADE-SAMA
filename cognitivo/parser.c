#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "interpretacao.h"
#include "parser.h"

/*=========================================
    ESTRUTURA PRIVADA DO PARSER
=========================================*/

#define MAX_TOKENS 20
#define MAX_TOKEN 50

typedef struct
{
    char palavras[MAX_TOKENS][MAX_TOKEN];

    int quantidade;

} Parser;

static void classificar(
        Parser *p,
        Interpretacao *i);
        
static void analisarTexto(
        const char *frase,
        Parser *p)
{
    p->quantidade = 0;

    int i = 0;
    int j = 0;

    while(frase[i] != '\0')
    {
        while(frase[i] == ' ' ||
              frase[i] == '\n' ||
              frase[i] == '\t')
        {
            i++;
        }

        if(frase[i] == '\0')
            break;

        j = 0;

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
void interpretarFrase(
        const char *frase,
        Interpretacao *inter)
{
    Parser p;

    analisarTexto(frase, &p);

    classificar(&p, inter);
}

static void classificar(
        Parser *p,
        Interpretacao *i)
{
    memset(i,0,sizeof(*i));

    i->tipo = ACAO_DESCONHECIDA;

    if(p->quantidade==0)
        return;

    /*======================
        SAUDAÇÃO
    ======================*/

    if(strcmp(p->palavras[0],"ola")==0 ||
       strcmp(p->palavras[0],"olá")==0 ||
       strcmp(p->palavras[0],"oi")==0)
    {
        i->tipo=ACAO_SAUDACAO;
        return;
    }

    /*======================
        PERFIL
    ======================*/

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

    /*======================
        CONSULTAS
    ======================*/

    if(strcmp(p->palavras[0],"quem")==0 ||
       strcmp(p->palavras[0],"qual")==0 ||
       strcmp(p->palavras[0],"onde")==0 ||
       strcmp(p->palavras[0],"o")==0)
    {
        i->tipo=ACAO_CONSULTA;
        return;
    }

    /* o que sabes sobre */

if(p->quantidade >= 5)
{
    if(strcmp(p->palavras[0],"o")==0 &&
       strcmp(p->palavras[1],"que")==0 &&
       strcmp(p->palavras[2],"sabes")==0 &&
       strcmp(p->palavras[3],"sobre")==0)
    {
        i->tipo = ACAO_INFERENCIA;

        strcpy(
            i->objeto,
            p->palavras[4]);

        return;
    }
}
    /*======================
        CONHECIMENTO
    ======================*/

    for(int k=1;k<p->quantidade;k++)
    {
        if(strcmp(p->palavras[k],"é")==0 ||
           strcmp(p->palavras[k],"e")==0 ||
           strcmp(p->palavras[k],"fica")==0 ||
           strcmp(p->palavras[k],"tem")==0)
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

    /*======================
        MEMÓRIA
    ======================*/

    if(strcmp(p->palavras[0],"lembra")==0 ||
       strcmp(p->palavras[0],"aprendi")==0)
    {
        i->tipo=ACAO_MEMORIA;
        return;
    }

    /*======================
        ESTUDO
    ======================*/

    if(strcmp(p->palavras[0],"quanto")==0 ||
       strcmp(p->palavras[0],"calcula")==0)
    {
        i->tipo=ACAO_ESTUDO;
        return;
    }
}