#ifndef GRAPHH
#define GRAPHH

#include <iostream>
#include <list>
#include <stack>
#include <vector>

class Graph
{
    //num de vertices
    int V;

    //vetor com listas de adjacencia
    std::list<int> *adj; 

    public:
        
        //construtor padrao
        Graph() = default;
        //construtor
        Graph(int V);
        

        //ordem topologica reversa, utilizando DFS
        void revTopolOrder(int v, bool visited[], std::stack<int> &pilha);
        
        //DFS
        std::list<int> DFS(int v, bool visited[]);
        //void DFS(int v, bool visited[]);

        //adiciona aresta de u para v
        void edge(int u, int v);

        //retorna o grafo transposto
        Graph transpose();

        std::vector<std::list<int>> Kosaraju();

        void printAdj();

};




#endif