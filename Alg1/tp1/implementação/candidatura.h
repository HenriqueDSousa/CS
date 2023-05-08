#ifndef CANDIDATURAH
#define CANDIDATURAH

#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include "graph.h"

class Candidatura
{   
    

    public:
        //num de seguidores
        int S;

        //num de propostas
        int P;

        //grafo para representar as relações entre as propostas
        Graph G;

        Candidatura(int S, int P);

        /*adiciona arestas aos vertices 
        de acordo com os votos dos seguidores*/
        void votacao();

        //verifica se ha solucao para a votacao
        bool avaliaVotacao();

    friend class Graph;

};



#endif