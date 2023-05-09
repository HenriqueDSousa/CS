#ifndef PALAVRAH
#define PALAVRAH

#include "palavra.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;


//Celula
class Palavra
{   
    public:
        std::string palavra; 
        int num_ocorr;
        Palavra *prox;

        Palavra(){palavra = "0"; num_ocorr = 0; prox = nullptr;};

        Palavra(string word);

};

int comparePalavra(Palavra *lhs, Palavra *rhs, char ordem[26]);


#endif