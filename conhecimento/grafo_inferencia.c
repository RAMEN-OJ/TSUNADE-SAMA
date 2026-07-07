/* ==========================================================================
 * grafo_inferencia.c — Inferência sobre o grafo de conhecimento
 *
 * Normalização de texto e conceitos, consulta ao grafo semântico,
 * extracção de entidades de frases e geração de respostas com factos
 * directos e inferidos por herança de tipo ("é").
 * ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "grafo_inferencia.h"

/**
 * Verifica se a palavra é um artigo definido ou indefinido em português.
 */
static int ehArtigo(const char *palavra){
    return strcmp(palavra, "o") == 0 || strcmp(palavra, "a") == 0 ||
           strcmp(palavra, "os") == 0 || strcmp(palavra, "as") == 0 ||
           strcmp(palavra, "um") == 0 || strcmp(palavra, "uma") == 0 ||
           strcmp(palavra, "uns") == 0 || strcmp(palavra, "umas") == 0;
}

/**
 * Remove acentos UTF-8 e converte caracteres para minúsculas in-place.
 */
static void removerAcentos(char *texto)
{
    size_t i;
    size_t j = 0;
    char tmp[256];

    for(i = 0; texto[i] != '\0' && j < sizeof(tmp) - 1; i++)
    {
        unsigned char c = (unsigned char)texto[i];

        switch(c)
        {
            case 0xC3:
                if((unsigned char)texto[i + 1] == 0xA1) { tmp[j++] = 'a'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xA0) { tmp[j++] = 'a'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xA2) { tmp[j++] = 'a'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xA3) { tmp[j++] = 'a'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xA9) { tmp[j++] = 'e'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xA8) { tmp[j++] = 'e'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xAA) { tmp[j++] = 'e'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xAD) { tmp[j++] = 'i'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xB3) { tmp[j++] = 'o'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xB2) { tmp[j++] = 'o'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xB4) { tmp[j++] = 'o'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xB5) { tmp[j++] = 'u'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xBA) { tmp[j++] = 'u'; i++; continue; }
                if((unsigned char)texto[i + 1] == 0xA7) { tmp[j++] = 'c'; i++; continue; }
                break;
            default:
                break;
        }

        tmp[j++] = (char)tolower(c);
    }

    tmp[j] = '\0';
    strcpy(texto, tmp);
}

/**
 * Normaliza texto genérico: minúsculas e remoção de acentos no destino.
 */
void normalizarTexto(char *dest, const char *origem, size_t tamanho)
{
    size_t i = 0;
    size_t j = 0;
    char tmp[256];

    if(dest == NULL || origem == NULL || tamanho == 0)
        return;

    while(origem[i] != '\0' && j < sizeof(tmp) - 1)
    {
        tmp[j++] = (char)tolower((unsigned char)origem[i]);
        i++;
    }
    tmp[j] = '\0';
    removerAcentos(tmp);

    strncpy(dest, tmp, tamanho - 1);
    dest[tamanho - 1] = '\0';
}

/**
 * Normaliza um conceito removendo artigos, plural simples e espaços extra.
 */
void normalizarConceito(char *dest, const char *origem, size_t tamanho)
{
    char tmp[256];
    char *token;
    char resultado[256];
    int primeiro = 1;

    normalizarTexto(tmp, origem, sizeof(tmp));

    if(strchr(tmp, ' ') == NULL)
    {
        size_t len = strlen(tmp);
        if(len > 3 && tmp[len - 1] == 's')
            tmp[len - 1] = '\0';
    }

    resultado[0] = '\0';
    token = strtok(tmp, " ");

    while(token != NULL)
    {
        if(!ehArtigo(token))
        {
            if(!primeiro)
                strncat(resultado, " ", sizeof(resultado) - strlen(resultado) - 1);
            strncat(resultado, token, sizeof(resultado) - strlen(resultado) - 1);
            primeiro = 0;
        }
        token = strtok(NULL, " ");
    }

    if(resultado[0] == '\0')
        normalizarTexto(resultado, origem, sizeof(resultado));

    strncpy(dest, resultado, tamanho - 1);
    dest[tamanho - 1] = '\0';
}

/**
 * Canonicaliza relações linguísticas para formas internas do grafo.
 */
void normalizarRelacao(char *dest, const char *origem, size_t tamanho)
{
    char tmp[256];

    normalizarTexto(tmp, origem, sizeof(tmp));

    if(strcmp(tmp, "e") == 0 || strcmp(tmp, "eh") == 0 || strcmp(tmp, "e um") == 0 ||
       strcmp(tmp, "e uma") == 0 || strcmp(tmp, "e un") == 0)
    {
        strcpy(dest, "eh");
        return;
    }

    if(strstr(tmp, "vive na") != NULL || strstr(tmp, "vive no") != NULL ||
       strstr(tmp, "vive em") != NULL || strcmp(tmp, "vive") == 0)
    {
        strcpy(dest, "vive em");
        return;
    }

    if(strstr(tmp, "fica na") != NULL || strstr(tmp, "fica no") != NULL ||
       strstr(tmp, "fica em") != NULL)
    {
        strcpy(dest, "fica em");
        return;
    }

    if(strstr(tmp, "sinonimo") != NULL || strstr(tmp, "igual a") != NULL ||
       strstr(tmp, "same as") != NULL)
    {
        strcpy(dest, "sinonimo");
        return;
    }

    strncpy(dest, tmp, tamanho - 1);
    dest[tamanho - 1] = '\0';
}

/**
 * Procura nó ligado ao alvo por aresta de sinónimo.
 */
static NoSemantico *procurarViaSinonimo(BaseConhecimento *b, const char *alvo)
{
    NoSemantico *no;
    Vizinho *v;
    char destNorm[200];

    for(no = b->grafo; no != NULL; no = no->proximo)
    {
        for(v = no->adjacentes; v != NULL; v = v->proximo)
        {
            char relNorm[100];

            normalizarRelacao(relNorm, v->relacao, sizeof(relNorm));
            if(strcmp(relNorm, "sinonimo") != 0)
                continue;

            normalizarConceito(destNorm, v->destino, sizeof(destNorm));
            if(strcmp(destNorm, alvo) == 0)
                return no;
        }
    }

    return NULL;
}

/**
 * Procura um nó semântico com normalização e comparação flexível.
 */
NoSemantico *procurarConceitoGrafo(BaseConhecimento *b, const char *conceito)
{
    char alvo[100];
    NoSemantico *no;

    if(b == NULL || conceito == NULL)
        return NULL;

    normalizarConceito(alvo, conceito, sizeof(alvo));

    no = procurarNoSemantico(b, alvo);
    if(no != NULL)
        return no;

    for(no = b->grafo; no != NULL; no = no->proximo)
    {
        char norm[100];
        normalizarConceito(norm, no->conceito, sizeof(norm));
        if(strcmp(norm, alvo) == 0)
            return no;
    }

    return procurarViaSinonimo(b, alvo);
}

/**
 * Extrai o conceito-alvo de frases de consulta do utilizador.
 */
int extrairConceitoConsulta(const char *frase, char *conceito, size_t tamanho)
{
    char copia[256];
    const char *padroes[] = {
        "o que sabes sobre ",
        "o que sabes de ",
        "fala-me sobre ",
        "fala me sobre ",
        "fala sobre ",
        "conta-me sobre ",
        "conta me sobre ",
        "conta sobre ",
        "diz-me sobre ",
        "diz me sobre ",
        "informacao sobre ",
        "informacao de "
    };
    size_t i;

    if(frase == NULL || conceito == NULL)
        return 0;

    normalizarTexto(copia, frase, sizeof(copia));

    for(i = 0; i < sizeof(padroes) / sizeof(padroes[0]); i++)
    {
        const char *pos = strstr(copia, padroes[i]);
        if(pos != NULL)
        {
            pos += strlen(padroes[i]);
            while(*pos == ' ')
                pos++;
            normalizarConceito(conceito, pos, tamanho);
            return conceito[0] != '\0';
        }
    }

    if(strncmp(copia, "sobre ", 6) == 0)
    {
        normalizarConceito(conceito, copia + 6, tamanho);
        return conceito[0] != '\0';
    }

    return 0;
}

/**
 * Verifica se um facto normalizado já existe na lista recolhida.
 */
static int fatoExiste(FatoGrafo *fatos, int total, const char *relacao, const char *objeto)
{
    int i;

    for(i = 0; i < total; i++)
    {
        if(strcmp(fatos[i].relacao, relacao) == 0 &&
           strcmp(fatos[i].objeto, objeto) == 0)
            return 1;
    }

    return 0;
}

/**
 * Adiciona um facto à lista evitando duplicados e normalizando campos.
 */
static void adicionarFato(FatoGrafo *fatos, int *total, int max,
                          const char *relacao, const char *objeto,
                          const char *herancaDe, int inferido)
{
    char relNorm[100];
    char objNorm[200];

    if(*total >= max)
        return;

    normalizarRelacao(relNorm, relacao, sizeof(relNorm));
    normalizarConceito(objNorm, objeto, sizeof(objNorm));

    if(fatoExiste(fatos, *total, relNorm, objNorm))
        return;

    strcpy(fatos[*total].relacao, relNorm);
    strcpy(fatos[*total].objeto, objNorm);
    if(herancaDe != NULL)
        normalizarConceito(fatos[*total].herancaDe, herancaDe, sizeof(fatos[*total].herancaDe));
    else
        fatos[*total].herancaDe[0] = '\0';
    fatos[*total].inferido = inferido;
    (*total)++;
}

/**
 * Indica se um conceito já foi visitado durante herança recursiva.
 */
static int jaVisitado(char visitados[][100], int n, const char *conceito)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(strcmp(visitados[i], conceito) == 0)
            return 1;
    }

    return 0;
}

/**
 * Propaga propriedades e tipos ancestrais via cadeias de relações "é".
 */
static void herdarDoTipo(BaseConhecimento *b, const char *tipo,
                         FatoGrafo *fatos, int *total, int max,
                         char visitados[][100], int *nVisit)
{
    NoSemantico *no;
    Vizinho *v;
    char tipoNorm[100];
    char paiNorm[100];

    normalizarConceito(tipoNorm, tipo, sizeof(tipoNorm));

    if(jaVisitado(visitados, *nVisit, tipoNorm))
        return;

    strcpy(visitados[*nVisit], tipoNorm);
    (*nVisit)++;

    no = procurarConceitoGrafo(b, tipoNorm);
    if(no == NULL)
        return;

    for(v = no->adjacentes; v != NULL; v = v->proximo)
    {
        char relNorm[100];

        normalizarRelacao(relNorm, v->relacao, sizeof(relNorm));

        if(strcmp(relNorm, "eh") == 0)
        {
            normalizarConceito(paiNorm, v->destino, sizeof(paiNorm));
            adicionarFato(fatos, total, max, "eh", paiNorm, tipoNorm, 1);
            herdarDoTipo(b, paiNorm, fatos, total, max, visitados, nVisit);
        }
        else if(strcmp(relNorm, "sinonimo") == 0)
        {
            continue;
        }
        else
        {
            adicionarFato(fatos, total, max, relNorm, v->destino, tipoNorm, 1);
        }
    }
}

/**
 * Recolhe factos directos e inferidos sobre um conceito no grafo.
 */
int coletarFatosGrafo(BaseConhecimento *b, const char *conceito, FatoGrafo *fatos, int maxFatos)
{
    NoSemantico *no;
    Vizinho *v;
    char alvo[100];
    char visitados[16][100];
    int nVisit = 0;
    int total = 0;

    if(b == NULL || conceito == NULL || fatos == NULL || maxFatos <= 0)
        return 0;

    normalizarConceito(alvo, conceito, sizeof(alvo));
    no = procurarConceitoGrafo(b, alvo);

    if(no == NULL)
        return 0;

    for(v = no->adjacentes; v != NULL; v = v->proximo)
    {
        char relNorm[100];

        normalizarRelacao(relNorm, v->relacao, sizeof(relNorm));

        if(strcmp(relNorm, "eh") == 0)
        {
            adicionarFato(fatos, &total, maxFatos, relNorm, v->destino, "", 0);
            nVisit = 0;
            herdarDoTipo(b, v->destino, fatos, &total, maxFatos, visitados, &nVisit);
        }
        else
        {
            adicionarFato(fatos, &total, maxFatos, relNorm, v->destino, "", 0);
        }
    }

    return total;
}

/**
 * Converte relação interna para forma legível na resposta ao utilizador.
 */
static const char *formatarRelacao(const char *relacao)
{
    if(strcmp(relacao, "eh") == 0)
        return "é";
    if(strcmp(relacao, "vive em") == 0)
        return "vive em";
    return relacao;
}

/**
 * Formata resposta textual com factos directos e inferidos sobre um conceito.
 */
int responderConhecimentoGrafo(BaseConhecimento *b, const char *conceito, char *resposta, size_t tamanho)
{
    FatoGrafo fatos[MAX_FATOS_GRAFO];
    char alvo[100];
    int total;
    int i;
    int directos = 0;
    int inferidos = 0;

    if(b == NULL || conceito == NULL || resposta == NULL)
        return 0;

    normalizarConceito(alvo, conceito, sizeof(alvo));
    total = coletarFatosGrafo(b, alvo, fatos, MAX_FATOS_GRAFO);

    if(total == 0)
        return 0;

    snprintf(resposta, tamanho, "Sei isto sobre %s:\n\n", alvo);

    for(i = 0; i < total; i++)
    {
        if(!fatos[i].inferido)
            directos++;
    }
    inferidos = total - directos;

    if(directos > 0)
    {
        strncat(resposta, "Factos directos:\n", tamanho - strlen(resposta) - 1);
        for(i = 0; i < total; i++)
        {
            char linha[640];
            if(fatos[i].inferido)
                continue;

            snprintf(linha, sizeof(linha), "  • %s %s %s\n",
                     alvo, formatarRelacao(fatos[i].relacao), fatos[i].objeto);
            strncat(resposta, linha, tamanho - strlen(resposta) - 1);
        }
    }

    if(inferidos > 0)
    {
        int tipos = 0;
        int props = 0;

        for(i = 0; i < total; i++)
        {
            if(!fatos[i].inferido)
                continue;
            if(strcmp(fatos[i].relacao, "eh") == 0)
                tipos++;
            else
                props++;
        }

        if(tipos > 0)
        {
            strncat(resposta, "\nTipos inferidos (cadeia de «é»):\n",
                   tamanho - strlen(resposta) - 1);
            for(i = 0; i < total; i++)
            {
                char linha[640];

                if(!fatos[i].inferido || strcmp(fatos[i].relacao, "eh") != 0)
                    continue;

                snprintf(linha, sizeof(linha),
                    "  • %s é %s  (porque %s é %s)\n",
                    alvo, fatos[i].objeto, alvo, fatos[i].herancaDe);
                strncat(resposta, linha, tamanho - strlen(resposta) - 1);
            }
        }

        if(props > 0)
        {
            strncat(resposta, "\nPropriedades inferidas:\n",
                   tamanho - strlen(resposta) - 1);
            for(i = 0; i < total; i++)
            {
                char linha[640];

                if(!fatos[i].inferido || strcmp(fatos[i].relacao, "eh") == 0)
                    continue;

                snprintf(linha, sizeof(linha),
                    "  • %s %s %s  (porque %s é %s)\n",
                    alvo, formatarRelacao(fatos[i].relacao), fatos[i].objeto,
                    alvo, fatos[i].herancaDe);
                strncat(resposta, linha, tamanho - strlen(resposta) - 1);
            }
        }
    }

    return 1;
}

/**
 * Adiciona relação após normalizar sujeito, relação e objecto.
 */
void adicionarRelacaoNormalizada(BaseConhecimento *b, const char *sujeito,
                                 const char *relacao, const char *objeto)
{
    char s[100];
    char r[100];
    char o[200];

    if(b == NULL || sujeito == NULL || relacao == NULL || objeto == NULL)
        return;

    normalizarConceito(s, sujeito, sizeof(s));
    normalizarRelacao(r, relacao, sizeof(r));
    normalizarConceito(o, objeto, sizeof(o));

    adicionarRelacao(b, s, r, o);
}

/**
 * Regista sinónimo bidireccional entre dois conceitos normalizados.
 */
void adicionarSinonimo(BaseConhecimento *b, const char *a, const char *b_conceito)
{
    char ca[100];
    char cb[100];

    if(b == NULL || a == NULL || b_conceito == NULL)
        return;

    normalizarConceito(ca, a, sizeof(ca));
    normalizarConceito(cb, b_conceito, sizeof(cb));

    if(strcmp(ca, cb) == 0)
        return;

    adicionarRelacao(b, ca, "sinonimo", cb);
    adicionarRelacao(b, cb, "sinonimo", ca);
}

/**
 * Carrega sinónimos comuns em português e inglês.
 */
void carregarSinonimosPadrao(BaseConhecimento *b)
{
    if(b == NULL)
        return;

    adicionarSinonimo(b, "cao", "dog");
    adicionarSinonimo(b, "cachorro", "cao");
    adicionarSinonimo(b, "gato", "cat");
    adicionarSinonimo(b, "carro", "automovel");
    adicionarSinonimo(b, "menino", "rapaz");
    adicionarSinonimo(b, "menina", "rapariga");
}
