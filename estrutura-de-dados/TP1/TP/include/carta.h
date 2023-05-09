#ifndef CARTAH
#define CARTAH

#include <stdio.h>
#include <string.h>

typedef struct Carta
{
    int numero;
    char naipe;
}tipo_carta;

//construtor da struct Carta
void criaCarta(tipo_carta *c, int numero, char naipe);

//retorna 1 se a carta estiver no baralho e 0 caso contrario
int validaCarta(tipo_carta *c);

#endif