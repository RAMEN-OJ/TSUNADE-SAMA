/* ==========================================================================
 * jogos_data.c — Brincadeiras e mini-jogos infantis
 * ========================================================================== */

#include <stddef.h>

#include "jogos_data.h"
#include "educacao.h"

static const JogoInfantil JOGOS[NUM_JOGOS] = {
    { "Adivinha do animal",
      "Penso num animal que faz 'miau'. Qual é?",
      "gato|cat",
      "Acertaste! 🎉 Era o gato!",
      "Era o gato! 🐱 Tenta outra vez na próxima!" },

    { "Contagem",
      "Quantos dedos tens numa mão? (responde com um número)",
      "5|cinco",
      "Certíssimo! São 5 dedos! 🎉",
      "São 5 dedos! Conta: 1, 2, 3, 4, 5. ✋" },

    { "Adivinha da cor",
      "Penso numa cor do céu num dia limpo. Qual é?",
      "azul",
      "Muito bem! O céu é azul! ☁️",
      "Era azul! Olha para o céu e vê." },

    { "Adivinha da fruta",
      "Sou amarela, macia por dentro e os macacos adoram-me. Que fruta sou?",
      "banana",
      "Parabéns! Era a banana! 🍌",
      "Era a banana! É deliciosa e saudável." },

    { "Rima",
      "Completa: 'Batata, tomate, feijão... no prato come-se com...' (diz uma palavra)",
      "pao|pão|garfo|fome",
      "Boa resposta! Gostas de comer bem! 🍽️",
      "Podias dizer pão, garfo ou mãozinha. Brincar com rimas é divertido!" },

    { "Corpo humano",
      "Com que órgão ouvimos música e conversas?",
      "orelha|ouvid",
      "Excelente! Ouvimos com as orelhas! 👂",
      "Ouvimos com as orelhas!" },

    { "Maior ou menor",
      "O que é maior: 7 ou 3? (responde 7 ou 3)",
      "7|sete",
      "Certo! 7 é maior que 3! 🔢",
      "7 é maior que 3. Muito bem na matemática!" },

    { "Sim ou Não",
      "Um peixe vive na água? (sim ou não)",
      "sim|yes",
      "Sim! Os peixes vivem na água! 🐟",
      "Sim, os peixes vivem na água!" },

    { "Adivinha do objeto",
      "Tenho rodas, motor e levo pessoas. O que sou?",
      "carro|automovel|autocarro|bus",
      "Acertaste! 🚗",
      "Era um carro ou autocarro!" },

    { "Palavra secreta",
      "Estou a pensar numa estação quente, com praia e sol. Qual é?",
      "verao|verão",
      "Isso mesmo! Verão! ☀️",
      "Era o verão — tempo de férias e brincadeiras!" }
};

const JogoInfantil *obterJogo(int id)
{
    if(id < 0 || id >= NUM_JOGOS)
        return NULL;

    return &JOGOS[id];
}

int totalJogos(void)
{
    return NUM_JOGOS;
}
