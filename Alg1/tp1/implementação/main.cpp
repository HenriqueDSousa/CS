#include <iostream>
#include "graph.h"
#include "candidatura.h"

int main()
{
    int S, P;

    while (std::cin>>S>>P)
    {
        if (S == 0 && P == 0)
            break;
        
        Candidatura c = Candidatura(S,P);
        c.votacao();
        bool valido = c.avaliaVotacao();

        if (valido == 0)
        {
            std::cout<<"nao"<<std::endl;
        }
        if (valido == 1)
        {
            std::cout<<"sim"<<std::endl;
        }

    }
    
    
    return 0;
}