/* ==========================================================================
 * licoes_data.c — Conteúdo das 15 lições escolares
 * ========================================================================== */

#include <string.h>
#include <ctype.h>

#include "licoes_data.h"

static const DadosLicao LICOES[NUM_LICOES] = {
    { LICAO_MATEMATICA, "Matemática",
      "Vamos estudar Matemática!",
      "Quanto é 2 + 2?",
      "4|quatro",
      "Excelente! 2 + 2 = 4. És um campeão de matemática!",
      "A resposta era 4. Vamos praticar mais!" },

    { LICAO_PORTUGUES, "Português",
      "Aula de Português!",
      "Qual é a primeira letra do alfabeto?",
      "a",
      "Muito bem! A letra A é a primeira do alfabeto!",
      "A primeira letra é A, como em Amigo ou Abelha." },

    { LICAO_CIENCIAS, "Ciências",
      "Ciências divertidas!",
      "As plantas precisam de sol e água. O que bebemos quando temos sede?",
      "agua|água",
      "Sim! A água é essencial para viver. Muito bem!",
      "Quando temos sede, bebemos água." },

    { LICAO_GEOGRAFIA, "Geografia",
      "Vamos explorar a Geografia!",
      "Qual é a capital de Portugal?",
      "lisboa",
      "Certíssimo! Lisboa é a capital de Portugal!",
      "A capital de Portugal é Lisboa, junto ao rio Tejo." },

    { LICAO_HISTORIA_ESCOLAR, "História",
      "Aula de História!",
      "Portugal é um país com muitos séculos de história. Que navegador descobriu o caminho marítimo para a Índia?",
      "vasco|gama",
      "Muito bem! Vasco da Gama foi um grande navegador português!",
      "Foi Vasco da Gama, um herói da História de Portugal." },

    { LICAO_ANIMAIS, "Animais",
      "Hoje vamos aprender os animais!",
      "O leão é o rei da selva. Que animal faz 'miau'?",
      "gato|cat",
      "Muito bem! O gato é um animal doméstico adorável!",
      "A resposta era gato. Os gatos são muito carinhosos." },

    { LICAO_CORES, "Cores",
      "Vamos aprender cores!",
      "O céu é azul e o sol é amarelo. Qual é a cor da grama?",
      "verde",
      "Excelente! A grama é verde!",
      "A grama é verde, como as árvores no parque." },

    { LICAO_NUMEROS, "Números",
      "Aula de números!",
      "1, 2, 3... Quantos dedos tens numa mão?",
      "5|cinco",
      "Certíssimo! Uma mão tem 5 dedos!",
      "Uma mão tem 5 dedos. Conta: 1, 2, 3, 4, 5!" },

    { LICAO_LETRAS, "Letras",
      "Vamos aprender letras!",
      "A letra B vem depois da A. Diz uma palavra que começa por B.",
      "b|bola|bebe|banana|barco|bala",
      "Ótimo! Boa palavra!",
      "Por exemplo: Bola, Bebé, Barco... todas começam por B!" },

    { LICAO_FORMAS, "Formas",
      "Formas geométricas!",
      "Uma bola é redonda — isso é um círculo. Quantos lados tem um triângulo?",
      "3|tres|três",
      "Perfeito! O triângulo tem 3 lados!",
      "Um triângulo tem 3 lados e 3 cantos." },

    { LICAO_MUSICA, "Música",
      "Vamos ouvir Música!",
      "Na música usamos notas e ritmo. Que instrumento tem teclas pretas e brancas?",
      "piano",
      "Muito bem! O piano é um instrumento lindo!",
      "Era o piano. Também podes tocar viola, flauta ou guitarra!" },

    { LICAO_INGLES, "Inglês",
      "Pequena aula de Inglês!",
      "Em inglês, 'Hello' significa uma saudação. Como se diz 'Hello' em português?",
      "ola|olá",
      "Great! Hello = Olá!",
      "Hello significa Olá. Goodbye significa Adeus!" },

    { LICAO_AMBIENTE, "Ambiente",
      "Cuidar do planeta!",
      "Reciclar ajuda a Terra. Onde devemos pôr uma garrafa de plástico vazia?",
      "ecoponto|lixo azul|reciclar|recicl",
      "Muito bem! Reciclar protege a natureza!",
      "Garrafas de plástico vão para a reciclagem (lixo azul)." },

    { LICAO_SEGURANCA, "Segurança",
      "Segurança é importante!",
      "Em emergência na Europa, há um número especial. Qual é o número europeu de emergência?",
      "112",
      "Excelente! O 112 liga para ajuda em emergência!",
      "O número de emergência na Europa é 112." },

    { LICAO_ARTE, "Arte",
      "Vamos criar Arte!",
      "Ao misturar azul com amarelo na pintura, aparece que cor?",
      "verde",
      "Lindo! Azul + amarelo = verde!",
      "Misturando azul e amarelo obtemos verde." }
};

static void minuscula(char *dest, const char *origem, size_t tam)
{
    size_t i;

    for(i = 0; origem[i] != '\0' && i < tam - 1; i++)
        dest[i] = (char)tolower((unsigned char)origem[i]);
    dest[i] = '\0';
}

const DadosLicao *obterDadosLicao(TipoLicao tipo)
{
    int i;

    for(i = 0; i < NUM_LICOES; i++)
    {
        if(LICOES[i].tipo == tipo)
            return &LICOES[i];
    }

    return NULL;
}

TipoLicao detectarLicaoFrase(const char *frase)
{
    char copia[256];

    if(frase == NULL)
        return LICAO_NENHUMA;

    minuscula(copia, frase, sizeof(copia));

    if(strstr(copia, "matematica") || strstr(copia, "somar") || strstr(copia, "subtrair") ||
       strstr(copia, "multiplicar") || strstr(copia, "dividir"))
        return LICAO_MATEMATICA;

    if(strstr(copia, "portugues") || strstr(copia, "alfabeto") || strstr(copia, "silaba"))
        return LICAO_PORTUGUES;

    if(strstr(copia, "geografia") || strstr(copia, "mapa") || strstr(copia, "capital"))
        return LICAO_GEOGRAFIA;

    if(strstr(copia, "historia") && (strstr(copia, "estudar") || strstr(copia, "licao") ||
       strstr(copia, "escola") || strstr(copia, "aula")))
        return LICAO_HISTORIA_ESCOLAR;

    if(strstr(copia, "ciencias") || strstr(copia, "planeta") || strstr(copia, "experien"))
        return LICAO_CIENCIAS;

    if(strstr(copia, "animal") || strstr(copia, "animais") || strstr(copia, "selva"))
        return LICAO_ANIMAIS;

    if(strstr(copia, "cor") || strstr(copia, "cores"))
        return LICAO_CORES;

    if(strstr(copia, "numero") || strstr(copia, "numeros") || strstr(copia, "contar"))
        return LICAO_NUMEROS;

    if(strstr(copia, "letra") || strstr(copia, "letras"))
        return LICAO_LETRAS;

    if(strstr(copia, "forma") || strstr(copia, "formas") || strstr(copia, "geometr"))
        return LICAO_FORMAS;

    if(strstr(copia, "musica") || strstr(copia, "cantar") || strstr(copia, "canção") ||
       strstr(copia, "cancao"))
        return LICAO_MUSICA;

    if(strstr(copia, "ingles") || strstr(copia, "english"))
        return LICAO_INGLES;

    if(strstr(copia, "ambiente") || strstr(copia, "reciclar") || strstr(copia, "planeta terra"))
        return LICAO_AMBIENTE;

    if(strstr(copia, "seguranca") || strstr(copia, "emergencia") || strstr(copia, "transito"))
        return LICAO_SEGURANCA;

    if(strstr(copia, "arte") || strstr(copia, "pintar") || strstr(copia, "desenhar"))
        return LICAO_ARTE;

    return LICAO_NENHUMA;
}

TipoLicao escolherLicaoRotativa(Educacao *e)
{
    static const TipoLicao ordem[NUM_LICOES] = {
        LICAO_MATEMATICA, LICAO_PORTUGUES, LICAO_CIENCIAS, LICAO_GEOGRAFIA,
        LICAO_HISTORIA_ESCOLAR, LICAO_ANIMAIS, LICAO_CORES, LICAO_NUMEROS,
        LICAO_LETRAS, LICAO_FORMAS, LICAO_MUSICA, LICAO_INGLES,
        LICAO_AMBIENTE, LICAO_SEGURANCA, LICAO_ARTE
    };

    if(e == NULL)
        return LICAO_MATEMATICA;

    e->conteudoId = (e->conteudoId + 1) % NUM_LICOES;
    return ordem[e->conteudoId];
}
