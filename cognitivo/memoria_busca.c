/*======================================================================
  memoria_busca.c
  Busca na memória episódica e enriquecimento contextual de respostas.
  Recupera episódios passados e complementa respostas com dados do perfil.
======================================================================*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "memoria_busca.h"

/* Verifica se frase contém palavra (case-insensitive); retorna 1 se encontrou */
static int contemPalavra(const char *frase, const char *palavra)
{
    char copia[256];
    char alvo[64];
    size_t i;

    if(frase == NULL || palavra == NULL)
        return 0;

    for(i = 0; frase[i] != '\0' && i < sizeof(copia) - 1; i++)
        copia[i] = (char)tolower((unsigned char)frase[i]);
    copia[i] = '\0';

    for(i = 0; palavra[i] != '\0' && i < sizeof(alvo) - 1; i++)
        alvo[i] = (char)tolower((unsigned char)palavra[i]);
    alvo[i] = '\0';

    return strstr(copia, alvo) != NULL;
}

/* Busca episódios na memória episódica conforme padrões da frase; retorna 1 se respondeu */
int buscarMemoria(MemoriaEpisodica *m, const char *frase, char *resposta)
{
    char palavra[100];
    int encontrados = 0;
    int i;

    if(m == NULL || frase == NULL || resposta == NULL)
        return 0;

    /* --- pedido de recordação geral --- */
    if(contemPalavra(frase, "o que te contei") || contemPalavra(frase, "lembra-te") ||
       contemPalavra(frase, "lembras-te") || contemPalavra(frase, "o que disse"))
    {
        if(m->quantidade == 0)
        {
            snprintf(resposta, 512,
                "Ainda não me contaste muita coisa, mas estou atenta a tudo o que dizes.");
            return 1;
        }

        snprintf(resposta, 512, "Lembro-me do que me disseste:\n");

        for(i = m->quantidade - 1; i >= 0 && i >= m->quantidade - 3; i--)
        {
            strncat(resposta, "- ", 512 - strlen(resposta) - 1);
            strncat(resposta, m->lista[i].texto, 512 - strlen(resposta) - 1);
            strncat(resposta, "\n", 512 - strlen(resposta) - 1);
            encontrados++;
        }

        (void)encontrados;
        return 1;
    }

    /* --- busca por palavra-chave --- */
    if(sscanf(frase, "o que sabes sobre %99s", palavra) != 1)
        return 0;

    palavra[strcspn(palavra, "?\n")] = '\0';

    strcpy(resposta, "Lembro-me de:\n");

    for(i = 0; i < m->quantidade; i++)
    {
        if(strstr(m->lista[i].texto, palavra))
        {
            strcat(resposta, "- ");
            strcat(resposta, m->lista[i].texto);
            strcat(resposta, "\n");
            encontrados++;
        }
    }

    if(encontrados == 0)
    {
        snprintf(resposta, 512,
            "Não me lembro de nada sobre '%s' — podes contar-me?", palavra);
    }

    return 1;
}

/* Enriquece resposta com dados do perfil quando contextualmente relevante; retorna 1 se adicionou */
int enriquecerComMemoria(Tsunade *t, const char *frase, char *resposta, size_t tamanho)
{
    PerfilCrianca *p;
    char extra[256];
    size_t len;

    if(t == NULL || t->perfil == NULL || resposta == NULL || frase == NULL)
        return 0;

    p = t->perfil;
    extra[0] = '\0';

    /* --- enriquecimento contextual --- */
    if(strlen(p->animalFavorito) > 0 &&
       (contemPalavra(frase, "animal") || contemPalavra(frase, "brincar")))
    {
        snprintf(extra, sizeof(extra),
            "\n\nLembro que o teu animal favorito é %s!", p->animalFavorito);
    }
    else if(strlen(p->comidaFavorita) > 0 && contemPalavra(frase, "comer"))
    {
        snprintf(extra, sizeof(extra),
            "\n\nSe quiseres, podemos falar da tua comida favorita: %s.", p->comidaFavorita);
    }
    else if(strlen(p->corFavorita) > 0 && contemPalavra(frase, "cor"))
    {
        snprintf(extra, sizeof(extra),
            "\n\nA tua cor favorita é %s, não é?", p->corFavorita);
    }

    if(extra[0] == '\0')
        return 0;

    len = strlen(resposta);
    if(len + strlen(extra) + 1 < tamanho)
        strncat(resposta, extra, tamanho - len - 1);

    return 1;
}
