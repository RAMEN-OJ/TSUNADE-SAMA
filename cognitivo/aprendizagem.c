#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "aprendizagem.h"

char *extrairValor(
        const char *frase,
        const char *chave)
{
    static char valor[256];

    char *pos = strstr(frase, chave);

    if(pos == NULL)
        return NULL;

    pos += strlen(chave);

    while(*pos == ' ')
        pos++;

    /* remove "ÃÂ©" */
    if(strncmp(pos, "ÃÂ© ", 3) == 0)
        pos += 3;

    /* remove "e" */
    else if(strncmp(pos, "e ", 2) == 0)
        pos += 2;

    while(*pos == ' ')
        pos++;

    strcpy(valor, pos);

    valor[strcspn(valor, "\n?")] = '\0';

    /* remove espaÃÂ§os finais */
    int fim = strlen(valor) - 1;

    while(fim >= 0 &&
         (valor[fim] == ' ' ||
          valor[fim] == '\t'))
    {
        valor[fim] = '\0';
        fim--;
    }
printf("\n[DEBUG] valor extraido = '%s'\n", valor);
    return valor;
}

int aprenderPerfil(
        PerfilCrianca *perfil,
        const char *frase,
        char *resposta)
{
    char copia[256];

    strncpy(
        copia,
        frase,
        sizeof(copia) - 1);

    copia[sizeof(copia) - 1] = '\0';

    for(int i = 0; copia[i]; i++)
    {
        copia[i] = tolower(copia[i]);
    }

    /* ================= NOME ================= */

    if(strstr(copia, "meu nome"))
    {
        char *valor =
            extrairValor(frase, "meu nome");

        if(valor)
        {
            strcpy(
                perfil->nome,
                valor);

            sprintf(
                resposta,
                "Prazer em conhecer-te, %s!",
                perfil->nome);

            return 1;
        }
    }

    /* ================= IDADE ================= */

    int idade;

    if(sscanf(
        copia,
        "%*[^0-9]%d",
        &idade) == 1)
    {
        perfil->idade = idade;

        sprintf(
            resposta,
            "Entendi! Tens %d anos.",
            idade);

        return 1;
    }

    /* ================= COR FAVORITA ================= */

    if(strstr(copia, "cor favorita"))
    {
        char *valor =
            extrairValor(frase, "cor favorita");

        if(valor)
        {
            strcpy(
                perfil->corFavorita,
                valor);

            sprintf(
                resposta,
                "A tua cor favorita e %s. Vou guardar isso.",
                perfil->corFavorita);

            return 1;
        }
    }

    /* ================= ANIMAL FAVORITO ================= */

    if(strstr(copia, "animal favorito"))
    {
        char *valor =
            extrairValor(frase, "animal favorito");

        if(valor)
        {
            strcpy(
                perfil->animalFavorito,
                valor);

            sprintf(
                resposta,
                "Vou lembrar que o teu animal favorito e %s.",
                perfil->animalFavorito);

            return 1;
        }
    }

    /* ================= COMIDA FAVORITA ================= */

    if(strstr(copia, "comida favorita"))
    {
        char *valor =
            extrairValor(frase, "comida favorita");

        if(valor)
        {
            strcpy(
                perfil->comidaFavorita,
                valor);

            sprintf(
                resposta,
                "Vou lembrar que a tua comida favorita e %s.",
                perfil->comidaFavorita);

            return 1;
        }
    }

    return 0;
}
