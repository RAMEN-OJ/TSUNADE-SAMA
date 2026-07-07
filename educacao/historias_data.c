/* ==========================================================================
 * historias_data.c — 20 histórias infantis populares (curtas)
 * ========================================================================== */

#include <stddef.h>

#include "historias_data.h"
#include "educacao.h"

static const HistoriaInfantil HISTORIAS[NUM_HISTORIAS] = {
    { "Chapeuzinho Vermelho",
      { "Era uma vez uma menina chamada Chapeuzinho Vermelho que ia levar comida à avó.",
        "No caminho pela floresta, encontrou um lobo mau, mas continuou corajosa.",
        "Fim — a avó foi salva e Chapeuzinho aprendeu a não falar com estranhos. 🧺" } },

    { "Os Três Porquinhos",
      { "Três porquinhos construíram casas: uma de palha, outra de madeira e outra de tijolo.",
        "O lobo soprou a casa de palha e a de madeira, mas não derrubou a de tijolo.",
        "Fim — os três irmãos ficaram juntos na casa forte. Trabalhar bem compensa! 🐷" } },

    { "Cinderela",
      { "Cinderela vivia com as madrastas mas sonhava em ir ao baile do castelo.",
        "A fada madrinha transformou uma abóbora numa carruagem e deu-lhe um vestido mágico.",
        "Fim — o príncipe encontrou Cinderela e viveram felizes. A bondade vence! 👠" } },

    { "Branca de Neve",
      { "Branca de Neve era gentil e os sete anões acolheram-na na floresta.",
        "A rainha má deu-lhe uma maçã envenenada, mas o beijo sincero salvou-a.",
        "Fim — a bondade triunfou sobre a inveja. 🍎" } },

    { "Pinóquio",
      { "Pinóquio era um boneco de madeira que sonhava em ser menino de verdade.",
        "Mentiu e o nariz cresceu, mas aprendeu a ser honesto e corajoso.",
        "Fim — tornou-se um menino real. Sempre diga a verdade! 🤥➡️😊" } },

    { "Peter Pan",
      { "Peter Pan vivia na Terra do Nunca e não queria crescer.",
        "Voou com Wendy e os irmãos para aventuras mágicas contra o Capitão Gancho.",
        "Fim — a imaginação e a amizade iluminam a infância. 🧚" } },

    { "Alice no País das Maravilhas",
      { "Alice seguiu um coelho branco e caiu num mundo cheio de surpresas.",
        "Conheceu o Gato de Cheshire e uma rainha muito estranha.",
        "Fim — acordou e guardou a aventura no coração. Curiosidade abre portas! 🐇" } },

    { "O Patinho Feio",
      { "Um patinho diferente foi rejeitado pelos outros, mas nunca desistiu.",
        "Quando cresceu, descobriu que era um belo cisne.",
        "Fim — ser diferente também é especial. 🦢" } },

    { "A Pequena Sereia",
      { "Uma sereia sonhava conhecer o mundo humano e fez um grande sacrifício.",
        "Aprendeu que o amor verdadeiro pede coragem e respeito.",
        "Fim — a sua voz e o seu coração ficaram para sempre na memória do mar. 🌊" } },

    { "Aladdin",
      { "Aladdin era um rapaz pobre que encontrou uma lâmpada mágica.",
        "Com um génio amigo, defendeu a cidade de um feiticeiro ganancioso.",
        "Fim — a honestidade vale mais que qualquer tesouro. 🪔" } },

    { "A Bela Adormecida",
      { "Uma princesa adormeceu por um feitiço até chegar um gesto de amor verdadeiro.",
        "O reino inteiro dormiu à sua espera durante muitos anos.",
        "Fim — acordou e o reino voltou a sorrir. A paciência também é magia. 💤" } },

    { "Rapunzel",
      { "Rapunzel vivia numa torre com cabelos muito longos e sonhava com liberdade.",
        "Um viajante ouviu-a cantar e ajudou-a a descobrir o mundo.",
        "Fim — a liberdade e a música abriram-lhe novos caminhos. 🎶" } },

    { "João e o Pé de Feijão",
      { "João trocou a vaca por feijões mágicos que cresceram até às nuvens.",
        "Lá em cima encontrou um castelo e um ovo de ouro.",
        "Fim — João e a mãe nunca mais passaram fome. Coragem e sorte! 🌱" } },

    { "João e Maria",
      { "Perdidos na floresta, João e Maria encontraram uma casa de doces.",
        "Enganaram a bruxa e encontraram o caminho de casa com migalhas.",
        "Fim — a esperteza e o amor fraterno salvaram-nos. 🍬" } },

    { "A Raposa e as Uvas",
      { "Uma raposa viu uvas bonitas mas não as alcançou.",
        "Disse que não queria porque estavam verdes, mas aprendeu uma lição.",
        "Fim — não desprezes o que não consegues ter; tenta com honestidade. 🍇" } },

    { "A Cigarra e a Formiga",
      { "A cigarra cantou o verão inteiro enquanto a formiga guardava comida.",
        "No inverno, a cigarra precisou de ajuda.",
        "Fim — trabalhar a tempo evita problemas depois. 🐜" } },

    { "O Leão e o Rato",
      { "Um rato acordou um leão, que o pouparia da morte.",
        "Mais tarde, o rato libertou o leão preso numa rede.",
        "Fim — até os pequenos podem ajudar os grandes. 🦁" } },

    { "O Galo de Barcelos",
      { "Um peregrino foi acusado injustamente de roubar prata em Barcelos.",
        "Disse que um galo assado provaria a sua inocência — e o galo levantou-se!",
        "Fim — a verdade aparece quando menos se espera. 🇵🇹" } },

    { "O Elefantinho Cor-de-Rosa",
      { "Um elefante cor-de-rosa era diferente, mas tinha um coração enorme.",
        "Com a ajuda dos amigos, mostrou que a cor não define o valor de ninguém.",
        "Fim — aceitar as diferenças torna o mundo mais bonito. 🐘" } },

    { "O Mágico de Oz",
      { "Dorothy seguiu a estrada amarela com o Espantalho, o Homem de Lata e o Leão.",
        "Descobriram que coragem, inteligência e coração já estavam dentro deles.",
        "Fim — não há lugar como o lar, mas a viagem ensina muito. 🌈" } }
};

const HistoriaInfantil *obterHistoria(int id)
{
    if(id < 0 || id >= NUM_HISTORIAS)
        return NULL;

    return &HISTORIAS[id];
}

int totalHistorias(void)
{
    return NUM_HISTORIAS;
}
