/*
TAD Carta
-TAD que define uma carta
-Atributos: número, naipe

TAD Jogador
-TAD que define a mão de um jogador, seu nome e quanto dinheiro ele tem

-Atributos: nome do jogador, dinheiro, id, para fim de localidade de referencia, numero de cartas e vetor do tipo Carta

*/

#ifndef JOGADORH
#define JOGADORH

#include "carta.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct Jogador
{
    char nome_jogador[1000];
    int dinheiro;
    int aposta;
    int id_;
    tipo_carta mao[6];
    int maiores_comb[5];
    int num_cartas;
    int valor_mao;

    
}tipo_jogador;

tipo_jogador criaJogador(char *nome, int aposta,int dinheiro, int id_, FILE *fp);

//inserir carta na mao
void insereCarta(tipo_jogador *j, tipo_carta card);

//ordena as cartas pelo numero
void ordenaCartas(tipo_jogador *j);

//funcao que realiza a jogada
void jogada(tipo_jogador *j, int aposta, int pingo);

//funcao que tira todas cartas da mao
void destroiCartas();

//imprime a sequencia de cartas da mao
void imprimeCartas(tipo_jogador *j);

//verifica qual a combinacao de maior valor da mao
void identificaMao(tipo_jogador *j);

void leInsere(tipo_jogador *j, FILE *fp);

void maioresComb(tipo_jogador *j);


#endif
