#ifndef TEXTOH
#define TEXTOH

#include "palavra.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;


class Texto
{   
    public:
    
        Palavra* primeiro;
        Palavra* ultimo;
        int num_palavras;
        int id;

        Texto();
        ~Texto();

        Palavra* posiciona(int pos, bool antes);

        void insere(string word);

        void limpa();

        void analisaTexto(std::ifstream &fIn);

        void insertionSort(char ordem[26], int a, int b);
        
        Palavra* find_pivot(int low, int high, int m, int s, char ordem[26]);

        void partition(int low, int high, int *i, int *j, char ordem[26], int m, int s);

        void quicksort(int low, int high, char ordem[26], int s, int m);

        void imprimePalavras(std::ofstream &fOut);

        void acessaPalavras();

        friend class Palavra;

};

void ordemLexicografica(char ordem[26], ifstream &fIn);

void swap(Palavra *a, Palavra *b);




#endif