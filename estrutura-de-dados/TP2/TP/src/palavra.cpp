
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include "palavra.h"

using namespace std;

// construtor para Palavra
Palavra::Palavra(string word)
{
    this->palavra = word;
    this->num_ocorr = 0;
    this->prox = nullptr;
}

//retorna 1 se a palavra da esquerda vier antes do que a da direita
// extende para lhs < rhs
int comparePalavra(Palavra *lhs, Palavra *rhs, char ordem[26])
{
    string aux1 = lhs->palavra;
    string aux2 = rhs->palavra;

    int smallerLength = min(aux1.length(), aux2.length());

    if (aux1 == aux2)
    {
        return -1;
    }

    // compara as palavras e retorna a que vier primeiro de acordo com a
    // ordem lexicografica predefinida
    for (int i = 0; i < smallerLength; i++)
    {
        if (aux1[i] != aux2[i])
        {
            int index1, index2;

            // verificando com a tabela ASCII, primeiramente
            if (((int)(aux1[i]) >= 33 && (int)aux1[i] <= 64) || ((int)aux2[i] >= 33 && (int)aux2[i] <= 64))
            {
            
                return ((int)aux1[i] < (int)aux2[i]);
                
            }

            for (int j = 0; j < 26; j++)
            {
                if (ordem[j] == aux1[i])
                {
                    index1 = j;
                    break;
                }
            }

            for (int j = 0; j < 26; j++)
            {
                if (ordem[j] == aux2[i])
                {
                    index2 = j;
                    break;
                }
            }

            return index1 < index2;
        
        }
    }

    // caso não tenha encontrado uma palavra que antecede a outra
    // retorna a palavra com menor comprimento

    return (aux1.length() < aux2.length());

    
}

