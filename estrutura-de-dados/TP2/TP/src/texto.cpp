
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include "palavra.h"
#include "texto.h"
#include "memlog.h"
#include "msgassert.h"
#include <getopt.h>
#include <fstream>


//converte uma string para sua forma com somente letras minusculas
string lower(string str) 
{   
    for (int i = 0; i < (int)(str.length()); i++)
    {
         if (str[i] >='A' && str[i] <='Z') 
            str[i]+='a'-'A'; 
    }  
    
    return str;
} 


//recebe a ordem lexicografica desejada
void ordemLexicografica(char ordem[26], std::ifstream &fIn)
{   
    string aux;
    getline(fIn,aux,'\n');
    
    cout<<aux<<endl;
    stringstream ss(aux);

    char letra;
    int i = 0;

    while (ss >> letra)
    {   
        
        ordem[i] = tolower(letra);
        i++;

        if (i == 26)
            break;
        
    }
    cout<<endl;

    for (int i = 0; i < 26; i++)
    {
        cout<<ordem[i]<<" ";
    }
    cout<<endl;

}

Texto::Texto()
{
    primeiro = new Palavra();

    ultimo = primeiro;
}

void Texto::limpa()
{
    Palavra *p = primeiro->prox;

    while (p != NULL)
    {
        primeiro->prox = p->prox;
        delete (p);
        p = primeiro->prox;
    }
    
    ultimo = primeiro;
    num_palavras = 0;

}


Texto::~Texto()
{   
    limpa();
    delete primeiro;
}

Palavra* Texto::posiciona(int pos, bool antes)
{
    Palavra* p;
    erroAssert( (pos < num_palavras) || (pos >= 0), "Posição invalida" );

    // Posiciona na célula anterior a desejada
    p = primeiro;

    for(int i=0; i<pos; i++)
    {
        p = p->prox;
    }

    if(antes == 0)
        p = p->prox;

    return p;
}

void Texto::insere(string word)
{
    Palavra *nova;
    nova = new Palavra(word);
    nova->num_ocorr++;
    
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    num_palavras++;

    if(nova->prox == NULL)
        ultimo = nova;
    
    ESCREVEMEMLOG((long int)(nova), sizeof(Palavra), id);
}


//conta o numero de ocorrencias de uma palavra do texto
//retorna o numero de palavras diferentes no texto
void Texto::analisaTexto(std::ifstream &fIn)
{   
    string text;

    while (getline(fIn, text))
    {   

        if (text == "#ORDEM")
            break;
        

        stringstream ss(text);
        
        string word;

        while (ss >> word)
        {   
            
            word = lower(word);

            bool valid_word = 1;

            if (word == "," || word == "." || word == "!" || word == "?" ||
                word == ":" || word == ";" || word == "_") 
                valid_word = 0;
            

            if(valid_word == 1)
            {   

                for (int i = 0; i < (int)(word.length()); i++)
                {
                    if (word[i] == ',' || word[i] == '.' || word[i] == '!' || word[i] == '?' ||
                        word[i] == ':' || word[i] == ';' || word[i] == '_')
                    
                        word.erase(i,1);
                    
                }
                
                //verificar se a palavra ja foi lida anteriormente
                bool jaInserida = 0;

                Palavra *p = primeiro->prox;
                while (p != NULL)
                {
                    if(p->palavra == word)
                    {   
                        p->num_ocorr++;
                        jaInserida = 1;
                        break;
                    }

                    p = p->prox;
                }
                

                if (jaInserida == 0)
                {   
                    
                    this->insere(word);

                }

            }
        }
    }
 
}


void swap(Palavra* a, Palavra* b)
{   
    Palavra *tmp = new Palavra();
    tmp->palavra = a->palavra;
    tmp->num_ocorr = a->num_ocorr;

    a->palavra = b->palavra;
    a->num_ocorr = b-> num_ocorr;
    
    b->palavra = tmp->palavra;
    b->num_ocorr = tmp->num_ocorr;

    delete(tmp);
}

//ORDENACAO

//insertion Sort
void Texto::insertionSort(char ordem[26], int a, int b)
{
    int i, j;
    Palavra *key = new Palavra();

    for (i = a; i < b; i++)
    {
        
        (*key) = (*posiciona(i,0));
        j = i - 1;

        while (j >= 0 && (comparePalavra(posiciona(j, 0), key, ordem)) == 0)
        {   
            swap(posiciona(j+1,0),posiciona(j, 0));

            LEMEMLOG((long int)(posiciona(j+1,0)), sizeof(Palavra), id);
            LEMEMLOG((long int)(posiciona(j, 0)), sizeof(Palavra), id);

            j = j - 1;
        }

        swap(posiciona(j+1, 0), key);

    }

    delete key;
}

//Quicksort

//Funcao para determinar o pivo de acordo com o numero m, que determina
//a mediana de m como otimizacao
Palavra* Texto::find_pivot(int low, int high, int m, int s, char ordem[26])
{   
    if ((high - low)-1 < m)
    {   
        return posiciona((low + high)/2, 0);
    }
    else if(m <= s && (high - low) > m)
    {   
        insertionSort(ordem, (low+high)/2 - (m/2), (low+high)/2 + (m/2));

        return (posiciona((low+high)/2, 0));
    }

    else return (posiciona((low + high)/2, 0));
        
    

}

void Texto::partition(int low, int high, int *i, int* j, char ordem[26], int m, int s)
{   
    Palavra* pivot = new Palavra();
    *i = low;
    *j = high;

    
    (*pivot) = *find_pivot(low, high, m, s, ordem);

    while (*i <= *j)
    {
        while(comparePalavra(posiciona(*i, 0), pivot, ordem) == 1)
            (*i)++;

        while (comparePalavra(posiciona(*j, 0), pivot, ordem) == 0)
            (*j)--;
        
        if (*i <= *j)
        {
            swap(posiciona(*i, 0), posiciona(*j, 0));

            LEMEMLOG((long int)(posiciona(*i, 0)), sizeof(Palavra), id);
            LEMEMLOG((long int)(posiciona(*j, 0)), sizeof(Palavra), id);

            (*i)++;
            (*j)--;
        }      
    }
    
    delete pivot;
}

void Texto::quicksort(int low, int high, char ordem[26], int s, int m)
{   
    int i, j;
    //para particoes menores ou iguais ao parâmetro s   
    
        if(low < high)
        {   
            if ((high - low) < s)
            {   
                insertionSort(ordem, low, high+1);
                return;
            }
            
            else
            {
                partition(low, high, &i, &j, ordem, m, s);

                if(low < j) quicksort(low, j, ordem, s, m);
                if(i < high) quicksort(i, high, ordem, s, m);
            }
        }
}

void Texto::imprimePalavras(std::ofstream &fOut)
{
    Palavra *p = primeiro->prox;
    while (p != NULL)
    {
        fOut<<p->palavra<<" "<<p->num_ocorr<<endl;
        p = p->prox;
    }
}

void Texto::acessaPalavras()
{

    Palavra *p = primeiro->prox;
    while (p != NULL)
    {
        LEMEMLOG((long int)(p), sizeof(Palavra), id);
        p = p->prox;
    }
}