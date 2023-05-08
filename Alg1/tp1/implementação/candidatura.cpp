#include <iostream>
#include "candidatura.h"
#include "graph.h"

Candidatura::Candidatura(int S, int P)
{
    this->S = S;
    this->P = P;

    //o num de vertices é 2 vezes o num de propostas
    this->G = Graph((2*P));
}

void Candidatura::votacao()
{
    for (int i = 0; i < S; i++)
    {   
        //a1 e a2 => votos de aprovacao
        //r1 e r2 => votos de rejeicao
        int a1, a2, r1, r2;
    
        std::cin>>a1>>a2>>r1>>r2;
        //adicionando arestas

        /*caso tenha algum voto de aprov nulo
        adiciona arestas apontando de todos nós,exceto por ele mesmo, 
        para o voto nao nulo*/
        
        if ((a1 == 0) && (a2 != 0))
        {   
            a2--;
            for (int i = 0; i < 2*P; i++)
            {   
                if(i != a2)
                {
                    G.edge(i, a2);
                }
            }
            
        }

        else if ((a1 != 0) && (a2 == 0))
        {   
            a1--;
            for (int i = 0; i < 2*P; i++)
            {   
                if(i != a1)
                    G.edge(i, a1);
            }
            
        }
        

        //caso nao tenha votos de aprov nulos
        else if((a1 != 0) && (a2 != 0))
        {   
            a1--;
            a2--;
            //-x -> y
            G.edge((a1+P), a2);
            //-y ->x
            G.edge((a2+P), a1);
        }

        //fazendo o mesmo para os votos de rejeicao

        //atribuindo r1 e r2 a vertices negativos
        if(r1 != 0) r1 = r1+P;
        if(r2 != 0) r2 = r2 + P;

        
        if ((r1 == 0) && (r2 != 0))
        {   
            r2--;
            for (int i = 0; i < 2*P; i++)
            {   
                if(i != r2)
                    G.edge(i, r2);
            }
            
        }

        else if ((r1 != 0) && (r2 == 0))
        {   
            r1--;
            for (int i = 0; i < 2*P; i++)
            {   
                if(i != r1)
                    G.edge(i, r1);
            }
            
        }
        

        
        else if((r1 != 0) && (r2 != 0))
        {   
            r1--;
            r2--;
            //x -> -y
            G.edge(r1-P, r2);
            //y -> -x
            G.edge(r2-P, r1);
        }
            
    }

    
}

bool Candidatura::avaliaVotacao()
{
    //vetor de listas com os SCCs
    std::vector<std::list<int>> SCCs = G.Kosaraju();
    int N =SCCs.size();
    for (int i = 0; i < N; i++)
    {   
        std::list<int>::iterator j;
        for (j = SCCs[i].begin(); j != SCCs[i].end(); j++)
        {   
            std::list<int>::iterator k;
            for (k = SCCs[i].begin(); k != SCCs[i].end(); k++)
            {   
                if((*j != *k))
                    //se x e -x estiverem no mesmo SCC
                    if (std::abs(P - (*j)) == std::abs(P - (*k)))
                    {   
                        //votacao nao tem solucao
                        return 0;
                    }
                
            }
            
        }
        
    }

    //se x e -x nao estiverem no mesmo SCC
    //a votacao tem solucao
    return 1;
    

}  
