#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <getopt.h>
#include <fstream>
#include "palavra.h"
#include "texto.h"
#include "memlog.h"
#include "msgassert.h"


using namespace std;

int regmem;
char lognome[100];

void opcoesUso()
{

    fprintf(stderr, "gameop\n");
    fprintf(stderr, "\t-i <arq>\t(arquivo de entrada) \n");
    fprintf(stderr, "\t-o <arq>\t(arquivo de saida) \n");
    fprintf(stderr, "\t-p <arq>\t(registro de desempenho)\n");
    fprintf(stderr, "\t-l \t(padrao de acesso e localidade)\n");
    fprintf(stderr, "\t-h\t(opcoes de uso)\n");
}

void parse_args(int argc, char **argv, char *fileIn, char *fileOut, int &m, int &s)
{
    extern char *optarg;
    int c;

    // inicializando o nome dos arquivos de entrada e de saída
    fileIn[0] = 0;
    fileOut[0] = 0;
    lognome[0] = 0;
    regmem = 0;
    m = 0;
    s = 0;

    while ((c = getopt(argc, argv, "i:m:s:o:p:lh")) != EOF)
        switch (c)
        {
        case 'i':
            // arquivo de entrada
            strcpy(fileIn, optarg);
            break;

        case 'm':
            m = atoi(optarg);
            break;
        
        case 's':
            s = atoi(optarg);
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

    int m, s;

    parse_args(argc, argv, fileIn, fileOut, m, s);
    
    ifstream fIn;
    ofstream fOut;

    Texto *text = new Texto();
    
    fIn.open(fileIn);

    fOut.open(fileOut);

    //string para detectar a flag de ORDEM ou TEXTO
    string op;
    string texto;

    //inicializar registro de acesso
    iniciaMemLog(lognome);

    //ativar ou desativar registro de acesso
    if (regmem)
        ativaMemLog();
    
    else
        desativaMemLog();
    
    char ordem[26];

    //fase de alocacao das palavras do texto
    defineFaseMemLog(0);


    fIn >> op;
    
    cout<<(op == "#ORDEM")<<endl;

        //caso #ORDEM apareca primeiro
        if (op == "#ORDEM")
        {   
            ordemLexicografica(ordem, fIn);          
            
            //#TEXTO
            getline(fIn,op,'\n');
            
            text->analisaTexto(fIn);
             
        }

        //caso #TEXTO aparecaprimeiro
        else if(op == "#TEXTO")
        {
            text->analisaTexto(fIn);
            
            ordemLexicografica(ordem, fIn);
   
        }
   

    //fase de ordenacao
    defineFaseMemLog(1);

    text->acessaPalavras();
    //Ordenando com quicksort

    int n = text->num_palavras;
    
    text->quicksort(0, n-1 ,ordem, s, m);
    
    text->imprimePalavras(fOut);

    fOut<<"#FIM";
    text->~Texto();

    fIn.close();
    fOut.close();

    return finalizaMemLog();
}