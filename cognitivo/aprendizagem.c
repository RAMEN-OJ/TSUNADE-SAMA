/*======================================================================
  aprendizagem.c
  Aprendizagem por conversa: extrai e persiste dados de perfil
  e relações semânticas a partir de frases naturais em português.
======================================================================*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#include "aprendizagem.h"
#include "../conhecimento/conceitos.h"
#include "../conhecimento/grafo_inferencia.h"

/* Remove prefixos redundantes (é, e) e espaços do texto aprendido; parâmetro: texto (in/out) */
static void limparTextoAprendido(char *texto)
{
    char *p = texto;

    while(*p == ' ' || *p == '\t')
        p++;

    if(strncmp(p, "é ", 3) == 0 || strncmp(p, "e ", 2) == 0)
    {
        p += (p[1] == ' ' ? 2 : 3);
        while(*p == ' ')
            p++;
    }
    else if((unsigned char)p[0] == 0xC3 && (unsigned char)p[1] == 0xA9)
    {
        p += 2;
        while(*p == ' ')
            p++;
    }
    else if(*p == 'e' && p[1] == ' ')
    {
        p += 2;
        while(*p == ' ')
            p++;
    }

    if(p != texto)
        memmove(texto, p, strlen(p) + 1);

    {
        int fim = (int)strlen(texto) - 1;
        while(fim >= 0 && (texto[fim] == ' ' || texto[fim] == '\t'))
            texto[fim--] = '\0';
    }
}

/* Extrai valor após chave na frase (ex: "meu nome é João"); retorna ponteiro estático ou NULL */
char *extrairValor(const char *frase, const char *chave)
{
    static char valor[256];
    const char *pos;

    pos = strstr(frase, chave);
    if(pos == NULL)
        return NULL;

    pos += strlen(chave);

    while(*pos == ' ')
        pos++;

    if(strncmp(pos, "é ", 3) == 0)
        pos += 3;
    else if(strncmp(pos, "e ", 2) == 0)
        pos += 2;
    else if((unsigned char)pos[0] == 0xC3 && (unsigned char)pos[1] == 0xA9)
        pos += 2;

    while(*pos == ' ')
        pos++;

    strncpy(valor, pos, sizeof(valor) - 1);
    valor[sizeof(valor) - 1] = '\0';
    valor[strcspn(valor, "\n?.!")] = '\0';
    limparTextoAprendido(valor);

    if(valor[0] == '\0')
        return NULL;

    return valor;
}

/* Copia frase em minúsculas para buffer; retorna 1 em sucesso, 0 se parâmetros inválidos */
static int copiaMinuscula(const char *frase, char *copia, size_t tamanho)
{
    size_t i;

    if(frase == NULL || copia == NULL)
        return 0;

    for(i = 0; frase[i] != '\0' && i < tamanho - 1; i++)
        copia[i] = (char)tolower((unsigned char)frase[i]);
    copia[i] = '\0';
    return 1;
}

/* Aprende dados pessoais no perfil (nome, idade, preferências); retorna 1 se aprendeu */
int aprenderPerfil(PerfilCrianca *perfil, const char *frase, char *resposta)
{
    char copia[256];
    char *valor;
    int idade;

    if(perfil == NULL || frase == NULL || resposta == NULL)
        return 0;

    copiaMinuscula(frase, copia, sizeof(copia));

    /* --- nome --- */
    if(strstr(copia, "meu nome") || strstr(copia, "chamo-me") ||
       strstr(copia, "chamo me") || strstr(copia, "sou o ") || strstr(copia, "sou a "))
    {
        if(strstr(copia, "meu nome"))
            valor = extrairValor(frase, "meu nome");
        else if(strstr(copia, "chamo-me"))
            valor = extrairValor(frase, "chamo-me");
        else if(strstr(copia, "chamo me"))
            valor = extrairValor(frase, "chamo me");
        else if(strstr(copia, "sou o "))
            valor = extrairValor(frase, "sou o ");
        else
            valor = extrairValor(frase, "sou a ");

        if(valor)
        {
            strncpy(perfil->nome, valor, sizeof(perfil->nome) - 1);
            perfil->nome[sizeof(perfil->nome) - 1] = '\0';
            limparTextoAprendido(perfil->nome);
            snprintf(resposta, 512,
                "Prazer em conhecer-te, %s! Vou lembrar-me do teu nome.", perfil->nome);
            return 1;
        }
    }

    /* --- idade --- */
    if(strstr(copia, "tenho") && strstr(copia, "anos"))
    {
        if(sscanf(copia, "%*[^0-9]%d", &idade) == 1 && idade > 0 && idade < 18)
        {
            perfil->idade = idade;
            snprintf(resposta, 512, "Entendi! Tens %d anos. Vou guardar isso.", idade);
            return 1;
        }
    }

    /* --- cor favorita --- */
    if(strstr(copia, "cor favorita"))
    {
        valor = extrairValor(frase, "cor favorita");
        if(valor)
        {
            strncpy(perfil->corFavorita, valor, sizeof(perfil->corFavorita) - 1);
            perfil->corFavorita[sizeof(perfil->corFavorita) - 1] = '\0';
            snprintf(resposta, 512,
                "A tua cor favorita é %s. Vou lembrar-me disso!", perfil->corFavorita);
            return 1;
        }
    }

    /* --- animal favorito --- */
    if(strstr(copia, "animal favorito"))
    {
        valor = extrairValor(frase, "animal favorito");
        if(valor)
        {
            strncpy(perfil->animalFavorito, valor, sizeof(perfil->animalFavorito) - 1);
            perfil->animalFavorito[sizeof(perfil->animalFavorito) - 1] = '\0';
            snprintf(resposta, 512,
                "Vou lembrar que o teu animal favorito é %s.", perfil->animalFavorito);
            return 1;
        }
    }

    /* --- comida favorita --- */
    if(strstr(copia, "comida favorita") || strstr(copia, "gosto de comer"))
    {
        if(strstr(copia, "comida favorita"))
            valor = extrairValor(frase, "comida favorita");
        else
            valor = extrairValor(frase, "gosto de comer");

        if(valor)
        {
            strncpy(perfil->comidaFavorita, valor, sizeof(perfil->comidaFavorita) - 1);
            perfil->comidaFavorita[sizeof(perfil->comidaFavorita) - 1] = '\0';
            snprintf(resposta, 512,
                "A tua comida favorita é %s. Obrigada por me contares!", perfil->comidaFavorita);
            return 1;
        }
    }

    return 0;
}

/* Aprende relação semântica (sujeito-relação-objeto) no grafo; retorna 1 se aprendeu */
int aprenderConhecimento(BaseConhecimento *base, const char *frase, char *resposta)
{
    char copia[256];
    char sujeito[100];
    char objeto[200];
    char relacao[100];
    const char *pos = NULL;
    const char *padrao = NULL;

    if(base == NULL || frase == NULL || resposta == NULL)
        return 0;

    normalizarTexto(copia, frase, sizeof(copia));
    copia[strcspn(copia, "\n")] = '\0';

    /* --- filtros de exclusão --- */
    if(strchr(copia, '?'))
        return 0;

    if(strncmp(copia, "o que", 5) == 0 || strncmp(copia, "quem", 4) == 0 ||
       strncmp(copia, "onde", 4) == 0 || strncmp(copia, "qual", 4) == 0 ||
       strncmp(copia, "fala", 4) == 0 || strncmp(copia, "conta", 5) == 0)
        return 0;

    /* --- deteção de padrões relacionais --- */
    if((pos = strstr(copia, " vive na "))) { strcpy(relacao, "vive em"); padrao = " vive na "; }
    else if((pos = strstr(copia, " vive no "))) { strcpy(relacao, "vive em"); padrao = " vive no "; }
    else if((pos = strstr(copia, " vive em "))) { strcpy(relacao, "vive em"); padrao = " vive em "; }
    else if((pos = strstr(copia, " vive "))) { strcpy(relacao, "vive em"); padrao = " vive "; }
    else if((pos = strstr(copia, " foi criado por "))) { strcpy(relacao, "foi criado por"); padrao = " foi criado por "; }
    else if((pos = strstr(copia, " fica na "))) { strcpy(relacao, "fica em"); padrao = " fica na "; }
    else if((pos = strstr(copia, " fica em "))) { strcpy(relacao, "fica em"); padrao = " fica em "; }
    else if((pos = strstr(copia, " e um "))) { strcpy(relacao, "eh"); padrao = " e um "; }
    else if((pos = strstr(copia, " e uma "))) { strcpy(relacao, "eh"); padrao = " e uma "; }
    else if((pos = strstr(copia, " e "))) { strcpy(relacao, "eh"); padrao = " e "; }
    else if((pos = strstr(copia, " gosta de "))) { strcpy(relacao, "gosta de"); padrao = " gosta de "; }
    else if((pos = strstr(copia, " sinonimo de "))) { strcpy(relacao, "sinonimo"); padrao = " sinonimo de "; }
    else if((pos = strstr(copia, " igual a "))) { strcpy(relacao, "sinonimo"); padrao = " igual a "; }

    if(pos == NULL || padrao == NULL)
        return 0;

    /* --- sinónimos bidireccionais --- */
    if(strcmp(relacao, "sinonimo") == 0)
    {
        strncpy(sujeito, copia, (size_t)(pos - copia));
        sujeito[pos - copia] = '\0';
        limparTextoAprendido(sujeito);

        strcpy(objeto, pos + strlen(padrao));
        limparTextoAprendido(objeto);

        if(strlen(sujeito) == 0 || strlen(objeto) == 0)
            return 0;

        adicionarSinonimo(base, sujeito, objeto);
        snprintf(resposta, 512,
            "Aprendi no grafo: %s e %s são sinónimos.", sujeito, objeto);
        return 1;
    }

    /* --- extração de sujeito e objeto --- */
    strncpy(sujeito, copia, (size_t)(pos - copia));
    sujeito[pos - copia] = '\0';
    limparTextoAprendido(sujeito);

    strcpy(objeto, pos + strlen(padrao));
    limparTextoAprendido(objeto);

    if(strlen(sujeito) == 0 || strlen(objeto) == 0)
        return 0;

    adicionarRelacaoNormalizada(base, sujeito, relacao, objeto);

    if(strcmp(relacao, "eh") == 0)
        snprintf(resposta, 512, "Aprendi no grafo: %s é %s.", sujeito, objeto);
    else if(strcmp(relacao, "vive em") == 0)
        snprintf(resposta, 512, "Aprendi no grafo: %s vive em %s.", sujeito, objeto);
    else
        snprintf(resposta, 512, "Aprendi no grafo: %s %s %s.", sujeito, relacao, objeto);

    return 1;
}

/* Tenta aprender perfil ou conhecimento em conversa livre; retorna 1 se tratou */
int tentarAprendizagemConversa(Tsunade *t, const char *frase, char *resposta)
{
    char copia[256];
    char *valor;

    if(t == NULL || frase == NULL || resposta == NULL)
        return 0;

    if(aprenderPerfil(t->perfil, frase, resposta))
        return 1;

    copiaMinuscula(frase, copia, sizeof(copia));

    /* --- preferências (gosto de) --- */
    if(strstr(copia, "gosto de") && !strstr(copia, "comida favorita"))
    {
        valor = extrairValor(frase, "gosto de");
        if(valor)
        {
            adicionarRelacaoNormalizada(t->conhecimento, "eu", "gosta de", valor);
            salvarConhecimento(t->conhecimento);
            snprintf(resposta, 512,
                "Que fixe! Gostas de %s — vou lembrar-me para falarmos disso outra vez.", valor);
            return 1;
        }
    }

    if(aprenderConhecimento(t->conhecimento, frase, resposta))
    {
        salvarConhecimento(t->conhecimento);
        return 1;
    }

    return 0;
}
