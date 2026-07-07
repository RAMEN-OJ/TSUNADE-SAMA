#ifndef JOGOS_DATA_H
#define JOGOS_DATA_H

typedef struct
{
    const char *titulo;
    const char *pergunta;
    const char *respostasCertas;
    const char *feedbackOk;
    const char *feedbackErr;

} JogoInfantil;

const JogoInfantil *obterJogo(int id);
int totalJogos(void);

#endif
