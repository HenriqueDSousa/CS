#include "graph.h"


Graph::Graph(int V)
{   
    this->V = V;
    adj = new std::list<int>[V];

}


void Graph::edge(int u, int v)
{
    adj[u].push_back(v);
    
}

Graph Graph::transpose()
{   
    
    Graph Gt = Graph(V);
    
    //transposta da lista de adjacencia
    for (int i = 0; i < V; i++)
    {
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            Gt.adj[*j].push_back(i);
        }

    }
    
    return Gt;
}

void Graph::revTopolOrder(int v, bool visited[], std::stack<int> &pilha)
{
    visited[v] = 1;
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if(visited[*i] == 0)
            revTopolOrder(*i, visited, pilha);
    }
    
    pilha.emplace(v);
}


std::list<int> Graph::DFS(int v, bool visited[])
{   
    std::stack<int> stack;
    stack.emplace(v);
    
    std::list<int> result;

    while (!stack.empty())
    {
        int u = stack.top();
        stack.pop();

        if(visited[u] == 0)
        {
            //setando u como explorado
            visited[u] = 1;

            result.push_back(u);

            for (auto i = adj[u].begin(); i != adj[u].end(); i++)
            {
                stack.emplace(*i);
            }
            
        }
    }

    return result;
}

std::vector<std::list<int>> Graph::Kosaraju()
{   
    //vetor de listas
    //cada lista contem um componente fortemente conexo do grafo
    std::vector<std::list<int>> SCC;

    //inicializando stack e vetor para verificar nodes visitados
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }
    std::stack<int> stack;
    
    //completando a pilha com a ordem topologica reversa
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == 0)
        {
            revTopolOrder(i, visited, stack);
        }
    }
    

    Graph Gt = this->transpose();

    //resetando o vetor com os nodes ja visitados
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }
    
    //processando DFS pela ordem topologica reversa
    while (!stack.empty())
    {
        int u = stack.top();
        stack.pop();

        if(!visited[u])
        {   

            std::list<int> aux = Gt.DFS(u, visited);

            //adicionando SCC ao vetor de SCCs
            SCC.push_back(aux);
        }

    }
    
    return SCC;

}   

void Graph::printAdj()
{
    for (int i = 0; i < V; i++)
    {   
        std::cout<<i<<": ";
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            std::cout<<(*j)<<" ";
        }
        std::cout<<std::endl;
        
    }
    

}