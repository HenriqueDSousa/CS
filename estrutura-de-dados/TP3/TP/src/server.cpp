#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <getopt.h>
#include <fstream>
#include "msgassert.h"
#include "mensage.h"
#include "bst.h"
#include "hash.h"
#include "memlog.h"


using namespace std;

int regmem;
char lognome[100];

void opcoesUso()
{

    fprintf(stderr, "server\n");
    fprintf(stderr, "\t-i <arq>\t(arquivo de entrada) \n");
    fprintf(stderr, "\t-o <arq>\t(arquivo de saida) \n");
    fprintf(stderr, "\t-p <arq>\t(registro de desempenho)\n");
    fprintf(stderr, "\t-l \t(padrao de acesso e localidade)\n");
    fprintf(stderr, "\t-h\t(opcoes de uso)\n");
}

void parse_args(int argc, char **argv, char *fileIn, char *fileOut)
{
    extern char *optarg;
    int c;

    // inicializando o nome dos arquivos de entrada e de saída
    fileIn[0] = 0;
    fileOut[0] = 0;
    lognome[0] = 0;
    regmem = 0;


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

        case 'p':
            
            strcpy(lognome, optarg);
            break;
        
        case 'l':
            
            regmem = 1;
            break;

        case 'h':
            opcoesUso();
            break;

        }

    // verifica o nome de saida e de entrada;
    erroAssert(fileIn[0], "Arquivo de entrada nao definido.");
    erroAssert(fileOut[0], "Arquivo de saida nao definido.");
}


int main(int argc, char **argv)
{   
    
    char fileIn[20];
    char fileOut[20];

    parse_args(argc, argv, fileIn, fileOut);

    ifstream fIn;
    ofstream fOut;

    //abrindo arquivos
    fIn.open(fileIn);
    fOut.open(fileOut);

    //inicializar registro de acesso
    iniciaMemLog(lognome);

    //ativar ou desativar registro de acesso
    if (regmem)
        ativaMemLog();
    
    else
        desativaMemLog();


    int m;
    fIn >> m;

    //Como é uma aplicacao de uso continuo, a analise do memlog tera apenas 1 fase
    defineFaseMemLog(0);

    //Hash table
    Hash hash = Hash(m);


    //string com o input
    string input;

    while (getline(fIn, input, '\n'))
    {
        stringstream ss(input);

        string opt;

        
        int U, E, N;
        string u;
        string e;
        string n;

        //Lendo opcao(ENTREGA/CONSULTA/APAGA)
        ss>>opt;

        if (opt == "ENTREGA")
        {
            ss>>u>>e>>n;
            U = stoi(u);
            E = stoi(e);
            N = stoi(n);


            string msg, word;
            msg[0] = 0;

            //lendo mensagem
            for (int i = 0; i < N; i++)
            {
                ss >> word;
                
                if (i == 0)
                    msg = word;
                else
                    msg = msg + " " + word;
            }
            
            Mensage email = Mensage(msg, E); 

            
            hash.hashTable[U % m].insert(hash.hashTable[U % m].root, email);

            fOut<<"OK: MENSAGEM "<< E <<" PARA "<< U <<" ARMAZENADA EM "<<(U % m)<<endl;


        }

        else if( opt == "CONSULTA")
        {
            ss >> u >> e;
            U = stoi(u);
            E = stoi(e); 
            
            fOut<<"CONSULTA "<<U<<" "<<E<<": "<< hash.hashTable[U % m].search(hash.hashTable[U % m].root, E)<<endl;
            
        }
        
        else if( opt == "APAGA")
        {
            ss>> u >> e;
            U = stoi(u);
            E = stoi(e);

            hash.hashTable[U % m].remove(hash.hashTable[U % m].root, E, fOut);

        }
        

    }

    hash.acessaTabela(m);
    
    fIn.close();
    fOut.close();
    
    return finalizaMemLog();
}