/*
Arquivo que desenvolve as funcoes do TAD Jogador

*/

#include "jogador.h"
#include "carta.h"
#include "msgassert.h"
#include "memlog.h"
#include <string.h>
#include <stdlib.h>

// Definindo o valor das combinacoes possiveis de maos
#define RSF 10
#define SF 9
#define FK 8
#define FH 7
#define F 6
#define S 5
#define TK 4
#define TP 3
#define OP 2
#define HC 1

// OBS: o vetor de cartas deve estar ordenado para a execucao das funcoes de ranqueamento de maos

// Testa se e One Pair
int testOP(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    // se houver um par
    if ((a == b) || (b == c) || (c == d) || (d == e))
        return 1;

    else
        return 0;
}

// funcao para testar se ha um par entre tres cartas
int pairBetweenThree(int a, int b, int c)
{
    if (a == b || a == c || a == c)
    {
        return 1;
    }
    else
        return 0;
}

// testa se é Two pairs(TP)
int testTP(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    if ((a == b) && (pairBetweenThree(c, d, e)))
        return 1;

    if ((b == c) && (d == e))
        return 1;

    if ((c == d) && (a == b))
        return 1;

    if ((d == e) && (pairBetweenThree(a, b, c)))
        return 1;

    else
        return 0;
}

// testa se é Three of a kind(TK)
int testTK(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    if ((a == b && b == c) || (b == c && c == d) || (c == d && d == e))
        return 1;

    else
        return 0;
}

int testS(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    if ((a == b + 1) && (b == c + 1) && (c == d + 1) && (d == e + 1))
        return 1;

    else
        return 0;
}

int testF(tipo_carta *mao)
{
    char a, b, c, d, e;

    a = mao[0].naipe;
    b = mao[1].naipe;
    c = mao[2].naipe;
    d = mao[3].naipe;
    e = mao[4].naipe;

    if ((a == b) && (b == c) && (c == d) && (d == e))
        return 1;

    else
        return 0;
}

int testFH(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    if (((a == b && b == c) && (d == e)) || ((c == d && d == e) && (a == b)))
        return 1;

    else
        return 0;
}

int testFK(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    if ((a == b && b == c && c == d) || (b == c && c == d && d == e) || (c == d && d == e && e == a) ||
        (d == e && e == a && a == b) || (e == a && a == b && b == c))
        return 1;

    else
        return 0;
}

int testSF(tipo_carta *mao)
{
    if ((testS(mao) == 1) && (testF(mao) == 1))
        return 1;

    else
        return 0;
}

int testRSF(tipo_carta *mao)
{
    int a, b, c, d, e;

    a = mao[0].numero;
    b = mao[1].numero;
    c = mao[2].numero;
    d = mao[3].numero;
    e = mao[4].numero;

    if ((a == 13) && (b == 12) && (c == 11) && (d == 10) && (e == 1) && (testF(mao) == 1))
        return 1;

    else
        return 0;
}

tipo_jogador criaJogador(char *nome, int aposta_, int dinheiro_, int id_, FILE *fp)
{
    tipo_jogador p;

    strcpy(p.nome_jogador, nome);

    p.aposta = aposta_;
    p.dinheiro = dinheiro_;
    p.id_ = id_;
    p.num_cartas = 0;
    p.valor_mao = 1;

    leInsere(&p, fp);
    ordenaCartas(&p);
    identificaMao(&p);
    maioresComb(&p);

    return p;
}

void insereCarta(tipo_jogador *p, tipo_carta card)
{

    erroAssert((&card != NULL), "Erro ao ler a carta");
    erroAssert((validaCarta((&card)) != 0), "Carta invalida");

    p->mao[p->num_cartas] = card;
    // ESCREVEMEMLOG((long int)(&(p->mao[p->num_cartas])), sizeof(tipo_carta), p->id_);

    p->num_cartas++;
}

void ordenaCartas(tipo_jogador *p)
{
    // Ordenando as cartas pelo número usando insert sort,
    // porem, em ordem decrescente

    int i, j;
    tipo_carta aux;

    for (i = 0; i < p->num_cartas; i++)
    {
        aux = p->mao[i];
        j = i - 1;
        while ((j >= 0) && (aux.numero > p->mao[j].numero))
        {
            p->mao[j + 1] = p->mao[j];
            j--;
        }
        p->mao[j + 1] = aux;
    }
}

void imprimeCartas(tipo_jogador *p)
{
    for (int i = 0; i < p->num_cartas; i++)
    {
        if (i == p->num_cartas - 1)
            printf("%d%c\n", p->mao[i].numero, p->mao[i].naipe);
        else
            printf("%d%c ", p->mao[i].numero, p->mao[i].naipe);
    }
}

void leInsere(tipo_jogador *p, FILE *fp)
{
    // Lendo as cartas e inserindo na mao
    for (int k = 0; k < 5; k++)
    {
        char carta_aux[3];

        fscanf(fp, "%s", carta_aux);
        tipo_carta aux_card;

        if ((int)(strlen(carta_aux)) == 2)
        {
            aux_card.numero = (carta_aux[0] - '0');
            aux_card.naipe = carta_aux[1];
            insereCarta(p, aux_card);
        }

        else if ((int)(strlen(carta_aux)) == 3)
        {
            char numtmp[3];
            char naipe_aux;

            naipe_aux = carta_aux[2];
            numtmp[0] = carta_aux[0];
            numtmp[1] = carta_aux[1];

            int num_aux = atoi(numtmp);

            aux_card.numero = num_aux;
            aux_card.naipe = naipe_aux;
            insereCarta(p, aux_card);
        }
    }
}

void identificaMao(tipo_jogador *p)
{
    if (testRSF(p->mao) == 1)
    {
        p->valor_mao = 10;
        return;
    }
    if (testSF(p->mao) == 1)
    {
        p->valor_mao = 9;
        return;
    }
    if (testFK(p->mao) == 1)
    {
        p->valor_mao = 8;
        return;
    }
    if (testFH(p->mao) == 1)
    {
        p->valor_mao = 7;
        return;
    }
    if (testF(p->mao) == 1)
    {
        p->valor_mao = 6;
        return;
    }
    if (testS(p->mao) == 1)
    {
        p->valor_mao = 5;
        return;
    }
    if (testTK(p->mao) == 1)
    {
        p->valor_mao = 4;
        return;
    }
    if (testTP(p->mao) == 1)
    {
        p->valor_mao = 3;
        return;
    }
    if (testOP(p->mao) == 1)
    {
        p->valor_mao = 2;
        return;
    }
    else
    {
        p->valor_mao = 1;
        return;
    } // Caso seja High Card
}

//é necessario de um vetor com as cartas ordenadas para o uso dessa funcao
void maioresComb(tipo_jogador *p)
{
    int a, b, c, d, e;
    a = p->mao[0].numero;
    b = p->mao[1].numero;
    c = p->mao[2].numero;
    d = p->mao[3].numero;
    e = p->mao[4].numero;

    int rank = p->valor_mao;
    switch (rank)
    {

    // Four of a kind
    case 8:

        // atribuindo o valor da quadra
        // e à carta fora da quadra
        if (a == b && b == c && c == d) // quadra = abcd
        {
            p->maiores_comb[0] = a;
            p->maiores_comb[1] = e;
        }

        else if (b == c && c == d && d == e)
        {
            p->maiores_comb[0] = b; // quadra = bcde
            p->maiores_comb[1] = a;
        }

        break;

    case 7:

        if (a == b && b == c)
        {
            p->maiores_comb[0] = a; // tripla: abc
            p->maiores_comb[1] = d; // dupla: de
        }

        if (c == d && d == e)
        {
            p->maiores_comb[0] = c; // tripla: cde
            p->maiores_comb[1] = a; // dupla: ab
        }

        break;

    case 4:

        // atribuindo o valor da tripla à posicao 0,
        // a maior carta fora da tripla na posicao 1,
        // a menor carta fora da tripla na posicao 2
        if (a == b && b == c)
        {
            p->maiores_comb[0] = a;
            p->maiores_comb[1] = d;
            p->maiores_comb[2] = e;
        }

        else if (b == c && c == d)
        {
            p->maiores_comb[0] = b;
            p->maiores_comb[1] = a;
            p->maiores_comb[2] = e;
        }

        else if (c == d && d == e)
        {
            p->maiores_comb[0] = c;
            p->maiores_comb[1] = a;
            p->maiores_comb[2] = b;
        }
        break;

    case 3:

        // atribuindo
        // a maior dupla à posicao 0,
        // a menor dupla à posicao 1,
        // a menor carta fora das duplas à posicao 2
        if (a == b && c == d)
        {
            p->maiores_comb[0] = a;
            p->maiores_comb[1] = c;
            p->maiores_comb[2] = e;
        }

        if (b == c && d == e)
        {
            p->maiores_comb[0] = b;
            p->maiores_comb[1] = d;
            p->maiores_comb[2] = a;
        }

        break;

    case 2:

        // atribuindo
        // a maior dupla à posicao 0,
        // a maior carta fora dupla à posicao 1,
        // a segunda maior carta fora das duplas à posicao 2,
        // a menor carta na posicao 3
        if (a == b)
        {
            p->maiores_comb[0] = a;
            p->maiores_comb[1] = c;
            p->maiores_comb[2] = d;
            p->maiores_comb[3] = e;
        }

        if (b == c)
        {
            p->maiores_comb[0] = b;
            p->maiores_comb[1] = a;
            p->maiores_comb[2] = d;
            p->maiores_comb[3] = e;
        }

        if (c == d)
        {
            p->maiores_comb[0] = c;
            p->maiores_comb[1] = a;
            p->maiores_comb[2] = b;
            p->maiores_comb[3] = e;
        }

        if (d == e)
        {
            p->maiores_comb[0] = d;
            p->maiores_comb[1] = a;
            p->maiores_comb[2] = b;
            p->maiores_comb[3] = c;
        }

        break;

    default:
        break;
    }
}
