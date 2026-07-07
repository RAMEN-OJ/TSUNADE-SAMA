#ifndef HISTORIAS_DATA_H
#define HISTORIAS_DATA_H

#define HISTORIA_PARTES 3

typedef struct
{
    const char *titulo;
    const char *partes[HISTORIA_PARTES];

} HistoriaInfantil;

const HistoriaInfantil *obterHistoria(int id);
int totalHistorias(void);

#endif
