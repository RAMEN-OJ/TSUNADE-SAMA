#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "consulta.h"

int responderConsulta(
        PerfilCrianca *perfil,
        const char *frase,
        char *resposta)
{
    char copia[256];

    strcpy(copia, frase);

    for(int i = 0; copia[i]; i++)
    {
        copia[i] = tolower(copia[i]);
    }

    /* NOME */

    if(strstr(copia, "qual") &&
       strstr(copia, "nome"))
    {
        if(strlen(perfil->nome) > 0)
        {
            sprintf(
                resposta,
                "O teu nome e %s.",
                perfil->nome);
        }
        else
        {
            sprintf(
                resposta,
                "Ainda nÃÂ£o sei o teu nome.");
        }

        return 1;
    }

    /* IDADE */

    if(strstr(copia, "qual") &&
       strstr(copia, "idade"))
    {
        if(perfil->idade > 0)
        {
            sprintf(
                resposta,
                "Tens %d anos.",
                perfil->idade);
        }
        else
        {
            sprintf(
                resposta,
                "Ainda nÃÂ£o sei a tua idade.");
        }

        return 1;
    }

    /* COR FAVORITA */

    if(strstr(copia, "qual") &&
       strstr(copia, "cor favorita"))
    {
        if(strlen(perfil->corFavorita) > 0)
        {
            sprintf(
                resposta,
                "A tua cor favorita e %s.",
                perfil->corFavorita);
        }
        else
        {
            sprintf(
                resposta,
                "Ainda nÃÂ£o sei a tua cor favorita.");
        }

        return 1;
    }

    /* ANIMAL FAVORITO */

    if(strstr(copia, "qual") &&
       strstr(copia, "animal favorito"))
    {
        if(strlen(perfil->animalFavorito) > 0)
        {
            sprintf(
                resposta,
                "O teu animal favorito e %s.",
                perfil->animalFavorito);
        }
        else
        {
            sprintf(
                resposta,
                "Ainda nÃÂ£o sei o teu animal favorito.");
        }

        return 1;
    }

    /* COMIDA FAVORITA */

    if(strstr(copia, "qual") &&
       strstr(copia, "comida favorita"))
    {
        if(strlen(perfil->comidaFavorita) > 0)
        {
            sprintf(
                resposta,
                "A tua comida favorita e %s.",
                perfil->comidaFavorita);
        }
        else
        {
            sprintf(
                resposta,
                "Ainda nao sei a tua comida favorita.Diz me qual e");
        }

        return 1;
    }

    return 0;
}


int consultarConhecimento(
        BaseConhecimento *base,
        const char *conceito,
        char *resposta)
{
    resposta[0]='\0';

    NoSemantico *no =
        procurarNoSemantico(
                base,
                conceito);

    if(no==NULL)
        return 0;

    strcat(resposta,"Sei que:\n");

    Vizinho *v=no->adjacentes;

    while(v)
    {
        strcat(resposta,"- ");
        strcat(resposta,no->conceito);
        strcat(resposta," ");
        strcat(resposta,v->relacao);
        strcat(resposta," ");
        strcat(resposta,v->destino);
        strcat(resposta,"\n");

        v=v->proximo;
    }

    return 1;
}

int responderConsultaSemantica(
        BaseConhecimento *b,
        const char *conceito,
        char *resposta)
{
    return consultarConhecimento(
            b,
            conceito,
            resposta);
}