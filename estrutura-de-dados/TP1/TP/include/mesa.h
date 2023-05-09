#ifndef MESAH
#define MESAH

#include "carta.h"
#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memlog.h"

typedef struct Mesa
{
    tipo_jogador *jogadores;
    int num_jogadores;
    int num_vencedores_rodada;
    int pote;
    int id_;

} tipo_mesa;

void inicializaMesa(tipo_mesa *m, int num_jogadores_, int id);

void insereNaMesa(tipo_mesa *m, tipo_jogador *p, int num_jogador);

// verifica a sanidade da rodada
int sanidadeRodada(tipo_mesa *m, int num_jogadores_rodada, int pingo, FILE *out);

// atribui um valor ao pote, já subtraindo o valor apostado pelos jogadores de seu saldo de dinheiro
int poteAposta(tipo_mesa *m);

// coleta o pingo de todos jogadores
int potePingo(tipo_mesa *m, int pingo);

// acha o vencedor da rodada
tipo_mesa vencedores(tipo_mesa *m, int num_jogadores);

// imprime relatorio da rodada
void imprimeRelatorio(tipo_mesa *m, int pote, FILE *out);

// ordena o vetor de jogadores em ordem decrescente, de acordo com o saldo
void ordenaMesa(tipo_mesa *m);

void limpaMesa(tipo_mesa *m);

double acessaMesa(tipo_mesa *m);

#endif
