#include "mesa.h"
#include "jogador.h"
#include "carta.h"
#include "msgassert.h"
#include "memlog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void opcoesUso()
{

    fprintf(stderr, "gameop\n");
    fprintf(stderr, "\t-i <arq>\t(arquivo de entrada) \n");
    fprintf(stderr, "\t-o <arq>\t(arquivo de saida) \n");
    fprintf(stderr, "\t-p <arq>\t(registro de desempenho)\n");
    fprintf(stderr, "\t-l \t(padrao de acesso e localidade)\n");
    fprintf(stderr, "\t-h\t(opcoes de uso)\n");
}

int regmem;
char lognome[100];

void parse_args(int argc, char **argv, char *fileIn, char *fileOut)
{
    extern char *optarg;
    extern int optind;
    int c;
    lognome[0] = 0;
    regmem = 0;
    // inicializando o nome dos arquivos de entrada e de saída
    fileIn[0] = 0;
    fileOut[0] = 0;

    while ((c = getopt(argc, argv, "i:o:p:lh")) != EOF)
        switch (c)
        {
        case 'i':
            // arquivo de entrada
            strcpy(fileIn, optarg);
            break;

        case 'o':
            // arquivo de saida
            strcpy(fileOut, optarg);
            break;

        case 'h':
            opcoesUso();
            break;
        case 'p':
            strcpy(lognome, optarg);
            break;

        case 'l':
            regmem = 1;
            break;
        }

    // verifica o nome de saida e de entrada;
    erroAssert(fileIn[0], "Arquivo de entrada nao definido.");
    erroAssert(fileOut[0], "Arquivo de saida nao definido.");
}

int main(int argc, char **argv)
{

    int num_rodadas, dinheiro_inicial, aposta;
    char fileIn[20];
    char fileOut[20];

    parse_args(argc, argv, fileIn, fileOut);

    FILE *fp = fopen(fileIn, "r");
    FILE *out = fopen(fileOut, "wt");

    int valor_pote = 0;

    tipo_mesa mesa;
    tipo_mesa mesa_aux;

    // inicializar registro de acesso
    iniciaMemLog(lognome);

    // ativar ou nao o registro de acesso
    if (regmem)
        ativaMemLog();
    else
        desativaMemLog();

    //atribuindo num de rodadas e o dinheiro inicial
    fscanf(fp, "%d %d", &num_rodadas, &dinheiro_inicial);

    int pingo, num_jogadores_rodada, num_total_jogadores;

    for (int rodada = 0; rodada < num_rodadas; rodada++)
    {

        fscanf(fp, "%d %d", &num_jogadores_rodada, &pingo);

        inicializaMesa(&mesa_aux, num_jogadores_rodada, 1);

        // na primeira rodada todos participam
        if (rodada == 0)
        {

            num_total_jogadores = num_jogadores_rodada;

            defineFaseMemLog(0);
            inicializaMesa(&mesa, num_total_jogadores, 0);

            for (int i = 0; i < num_jogadores_rodada; i++)
            {
                char *nome_aux = malloc(1000 * sizeof(char));

                fscanf(fp, "%[^0-9] %d", nome_aux, &aposta);

                nome_aux = nome_aux + 2;

                nome_aux[strlen(nome_aux) - 1] = '\0';

                tipo_jogador aux = criaJogador(nome_aux, aposta, dinheiro_inicial, i, fp);

                insereNaMesa((&mesa), (&aux), i);

                insereNaMesa((&mesa_aux), (&aux), i);
            }

            defineFaseMemLog(1);
            acessaMesa(&mesa);
        }

        else
        {

            for (int i = 0; i < num_jogadores_rodada; i++)
            {
                char *nome_aux = malloc(1000 * sizeof(char));

                fscanf(fp, "%[^0-9] %d", nome_aux, &aposta);

                nome_aux = nome_aux + 2;

                nome_aux[strlen(nome_aux) - 1] = '\0';

                tipo_jogador aux = criaJogador(nome_aux, aposta, 0, i, fp);

                insereNaMesa((&mesa_aux), (&aux), i);
            }

            for (int i = 0; i < mesa_aux.num_jogadores; i++)
            {

                for (int j = 0; i < mesa.num_jogadores; j++)
                {

                    if (strcmp(mesa_aux.jogadores[i].nome_jogador, mesa.jogadores[j].nome_jogador) == 0)
                    {
                        mesa_aux.jogadores[i].dinheiro = mesa.jogadores[j].dinheiro;
                        break;
                    }
                }
            }
        }

        // verificando se todos jogadores têm dinheiro para o pingo
        int rodadaValida = 1;

        for (int i = 0; i < num_total_jogadores; i++)
        {
            if (mesa.jogadores[i].dinheiro < pingo)
                rodadaValida = 0;
        }

        if (rodadaValida)
        {
            // caso a rodada passe no teste de sanidade, prossiga o jogo
            if (sanidadeRodada((&mesa_aux), num_jogadores_rodada, pingo, out))
            {
                // coletando o pingo
                valor_pote = potePingo(&(mesa), pingo);

                for (int i = 0; i < num_jogadores_rodada; i++)
                {
                    for (int k = 0; k < num_total_jogadores; k++)
                    {
                        if (strcmp(mesa_aux.jogadores[i].nome_jogador, mesa.jogadores[k].nome_jogador) == 0)
                        {
                            // atualizando o valor do dinheiro antes de fazer a aposta
                            mesa_aux.jogadores[i].dinheiro = mesa.jogadores[k].dinheiro;
                        }
                    }
                }
                // fazendo as apostas
                valor_pote += poteAposta(&(mesa_aux));

                // achando os vencedores
                tipo_mesa mesa_vencedores = vencedores((&mesa_aux), num_jogadores_rodada);

                imprimeRelatorio((&mesa_vencedores), valor_pote, out);

                int n = mesa_vencedores.num_vencedores_rodada;
                // adicionando dinheiro ao saldo dos jogadores
                for (int i = 0; i < n; i++)
                {
                    for (int k = 0; k < num_jogadores_rodada; k++)
                    {
                        if (strcmp(mesa_vencedores.jogadores[i].nome_jogador, mesa_aux.jogadores[k].nome_jogador) == 0)
                        {
                            mesa_aux.jogadores[k].dinheiro = mesa_aux.jogadores[k].dinheiro + (valor_pote / n);
                        }
                    }
                }

                for (int i = 0; i < num_jogadores_rodada; i++)
                {
                    for (int k = 0; k < num_total_jogadores; k++)
                    {
                        if (strcmp(mesa_aux.jogadores[i].nome_jogador, mesa.jogadores[k].nome_jogador) == 0)
                        {
                            // atualizando o valor do dinheiro dos jogadores apos a rodada
                            mesa.jogadores[k].dinheiro = mesa_aux.jogadores[i].dinheiro;
                        }
                    }
                }
            }

            // caso nao passe no teste de sanidade
            else
            {
                fprintf(out, "0 0 I\n");
            }
        }

        // caso haja algum jogador sem dinheiro para o pingo
        else if (rodadaValida == 0)
        {
            fprintf(out, "0 0 I\n");
        }

        limpaMesa(&mesa_aux);
    }

    ordenaMesa(&mesa);

    fprintf(out, "#######\n");

    for (int i = 0; i < num_total_jogadores; i++)
    {
        if (i == (num_total_jogadores - 1))
            fprintf(out, "%s %d\n", mesa.jogadores[num_total_jogadores - 1].nome_jogador, mesa.jogadores[num_total_jogadores - 1].dinheiro);

        else
            fprintf(out, "%s %d\n", mesa.jogadores[i].nome_jogador, mesa.jogadores[i].dinheiro);
    }

    fclose(fp);
    fclose(out);

    limpaMesa(&mesa);

    return finalizaMemLog();
}