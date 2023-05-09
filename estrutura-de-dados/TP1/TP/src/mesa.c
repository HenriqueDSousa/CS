#include "mesa.h"

tipo_mesa desempateComb(tipo_jogador *greatest, int num_jogadores, int num_posic)
{
    tipo_mesa aux;
    int comb = 0;
    int qtd_vencedores = num_jogadores;

    aux.jogadores = (tipo_jogador *)malloc(sizeof(tipo_jogador));

    while (comb < num_posic)
    {
        for (int i = 0; i < num_jogadores; i++)
        {
            if (greatest[i].nome_jogador[0] != '\0')
            {
                for (int j = 0; j < num_jogadores; j++)
                {
                    if ((i != j) && (greatest[j].nome_jogador[0] != '\0'))
                    {
                        if (greatest[i].maiores_comb[comb] > greatest[j].maiores_comb[comb])
                        {
                            greatest[j].nome_jogador[0] = '\0';
                            qtd_vencedores--;
                        }
                    }

                    if (qtd_vencedores == 1)
                        break;
                }
            }
        }

        comb++;
        if (qtd_vencedores == 1)
            break;
    }

    aux.jogadores = (tipo_jogador *)realloc(aux.jogadores, qtd_vencedores * sizeof(tipo_jogador));
    int a = 0;
    while (a < qtd_vencedores)
    {
        for (int i = 0; i < num_jogadores; i++)
        {
            if (greatest[i].nome_jogador[0] != '\0')
            {
                aux.jogadores[a] = greatest[i];
                a++;
            }
        }
    }

    aux.num_vencedores_rodada = qtd_vencedores;

    return aux;
}

tipo_mesa desempateSeq(tipo_jogador *greatest, int num_jogadores)
{
    tipo_mesa aux;
    int carta = 0;
    aux.jogadores = (tipo_jogador *)malloc(sizeof(tipo_jogador));

    int qtd_vencedores = num_jogadores;

    while (carta < 5)
    {
        for (int i = 0; i < num_jogadores; i++)
        {
            if (greatest[i].nome_jogador[0] != '\0')
            {
                for (int j = 0; j < num_jogadores; j++)
                {
                    if ((i != j) && (greatest[j].nome_jogador[0] != '\0'))
                    {
                        if (greatest[i].mao[carta].numero > greatest[j].mao[carta].numero)
                        {
                            greatest[j].nome_jogador[0] = '\0';
                            qtd_vencedores--;
                        }
                    }

                    if (qtd_vencedores == 1)
                        break;
                }
            }
        }

        carta++;
        if (qtd_vencedores == 1)
            break;
    }

    aux.jogadores = (tipo_jogador *)realloc(aux.jogadores, qtd_vencedores * sizeof(tipo_jogador));

    int a = 0;
    while (a < qtd_vencedores)
    {
        for (int i = 0; i < num_jogadores; i++)
        {
            if (greatest[i].nome_jogador[0] != '\0')
            {
                aux.jogadores[a] = greatest[i];
                a++;
            }
        }
    }

    aux.num_vencedores_rodada = qtd_vencedores;

    return aux;
}

void insereNaMesa(tipo_mesa *m, tipo_jogador *p, int num_jogador)
{
    m->jogadores[num_jogador] = (*p);

    for (int i = 0; i < 5; i++)
    {
        ESCREVEMEMLOG((long int)(&(m->jogadores[num_jogador])), sizeof(tipo_carta), m->id_);
    }
}

int sanidadeRodada(tipo_mesa *m, int num_jogadores_rodada, int pingo, FILE *out)
{
    int rodadaValida = 1;
    // verifica sanidade

    for (int i = 0; i < num_jogadores_rodada; i++)
    {
        if (m->jogadores[i].aposta < pingo)
        {
            rodadaValida = 0;
            break;
        }
        else if (m->jogadores[i].aposta > m->jogadores[i].dinheiro)
        {

            rodadaValida = 0;
            break;
        }
        else if ((m->jogadores[i].aposta + pingo) > m->jogadores[i].dinheiro)
        {
            fprintf(out, "Rodada invalida: jogador apostou mais do que possui\n");
            rodadaValida = 0;
            break;
        }
    }

    return rodadaValida;
}

int poteAposta(tipo_mesa *m)
{
    int pote = 0;

    for (int i = 0; i < m->num_jogadores; i++)
    {

        pote += (m->jogadores[i].aposta);
        m->jogadores[i].dinheiro = m->jogadores[i].dinheiro - (m->jogadores[i].aposta);
        m->jogadores[i].aposta = 0;
    }

    return pote;
}

int potePingo(tipo_mesa *m, int pingo)
{
    int pote = 0;

    for (int i = 0; i < m->num_jogadores; i++)
    {

        pote += pingo;
        m->jogadores[i].dinheiro = m->jogadores[i].dinheiro - pingo;
    }

    return pote;
}

tipo_mesa vencedores(tipo_mesa *m, int num_jogadores)
{
    int rank = 1;
    int j = 0;
    tipo_jogador *greatest = (tipo_jogador *)malloc(sizeof(tipo_jogador));

    // acha o valor da maior mao
    for (int i = 0; i < num_jogadores; i++)
    {
        if (rank < m->jogadores[i].valor_mao)
            rank = m->jogadores[i].valor_mao;
    }

    // inserindo os jogadores mais fortes em um vetor
    for (int i = 0; i < num_jogadores; i++)
    {
        if (m->jogadores[i].valor_mao == rank)
        {
            greatest = (tipo_jogador *)realloc(greatest, (j + 1) * sizeof(tipo_jogador));
            greatest[j] = m->jogadores[i];
            j++;
        }
    }

    tipo_mesa mesa_aux;

    if (j == 1)
    {
        mesa_aux.jogadores = greatest;
        mesa_aux.num_vencedores_rodada = j;
        return (mesa_aux);
    }

    else if (j > 1)
    {
        switch (rank)
        {

        // Caso seja Royal Straight Flush, não ha como desempatar
        case 10:

            mesa_aux.jogadores = greatest;
            mesa_aux.num_vencedores_rodada = j;
            break;

        // Straight Flush
        case 9:

            mesa_aux = desempateSeq(greatest, j);
            break;

        // Four of a kind
        case 8:

            mesa_aux = desempateComb(greatest, j, 2);
            break;

        // Full House
        case 7:

            mesa_aux = desempateComb(greatest, j, 2);
            break;

        // Flush
        case 6:
            (mesa_aux) = desempateSeq(greatest, j);
            break;

        // Straight
        case 5:

            (mesa_aux) = desempateSeq(greatest, j);
            break;

        // Three of a kind
        case 4:

            (mesa_aux) = desempateComb(greatest, j, 3);

            break;
        // Two pairs
        case 3:

            (mesa_aux) = desempateComb(greatest, j, 3);

            break;

        // One pair
        case 2:

            (mesa_aux) = desempateComb(greatest, j, 4);

            break;

        // High Card
        case 1:

            (mesa_aux) = desempateSeq(greatest, j);
            break;

        default:

            break;
        }
    }

    free(greatest);

    return (mesa_aux);
}

void nomeMao(int n, char *rank)
{

    if (n == 10)
        strcpy(rank, "RSF");
    if (n == 9)
        strcpy(rank, "SF");
    if (n == 8)
        strcpy(rank, "FK");
    if (n == 7)
        strcpy(rank, "FH");
    if (n == 6)
        strcpy(rank, "F");
    if (n == 5)
        strcpy(rank, "S");
    if (n == 4)
        strcpy(rank, "TK");
    if (n == 3)
        strcpy(rank, "TP");
    if (n == 2)
        strcpy(rank, "OP");
    if (n == 1)
        strcpy(rank, "HC");
}

void imprimeRelatorio(tipo_mesa *m, int pote, FILE *out)
{
    int n = m->num_vencedores_rodada;
    int rank = m->jogadores[0].valor_mao;

    char nomeRank[3];
    nomeMao(rank, nomeRank);

    fprintf(out, "%d %d %s\n", n, (pote / n), nomeRank);

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            fprintf(out, "%s\n", m->jogadores[i].nome_jogador);

        else
            fprintf(out, "%s, ", m->jogadores[i].nome_jogador);
    }
}

void inicializaMesa(tipo_mesa *m, int num_jogadores_, int id)
{
    m->num_jogadores = num_jogadores_;
    m->id_ = id;
    // alocando vetor de jogadores
    m->jogadores = malloc((m->num_jogadores) * sizeof(tipo_jogador));
}

// ordenando os jogadores de acordo com seu saldo
//  usando insert sort
void ordenaMesa(tipo_mesa *m)
{
    int i, j;
    tipo_jogador aux;

    for (i = 0; i < m->num_jogadores; i++)
    {
        aux = m->jogadores[i];
        j = i - 1;
        while ((j >= 0) && (aux.dinheiro > m->jogadores[j].dinheiro))
        {
            m->jogadores[j + 1] = m->jogadores[j];
            j--;
        }
        m->jogadores[j + 1] = aux;
    }
}

// desaloca vetor de cartas da mesa
void limpaMesa(tipo_mesa *m)
{
    free(m->jogadores);
    m->num_jogadores = 0;
    m->num_vencedores_rodada = 0;
}

// Acessa o vetor de jogadores para fim de registro de acesso
double acessaMesa(tipo_mesa *m)
{
    double aux = 0.0;
    double num = 1.1;

    for (int i = 0; i < m->num_jogadores; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            aux += num;
            num += num;
            LEMEMLOG((long int)(&(m->jogadores[i].mao[j])), sizeof(tipo_carta), m->id_);
        }
    }

    return num;
}