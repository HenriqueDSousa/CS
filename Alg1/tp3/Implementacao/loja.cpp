#include "loja.hpp"
#include <iostream>

//default constructor
Loja::Loja(std::vector<int> vetor)
{

    itens = vetor;
    n = itens.size();

}

void Loja::LIS(int* lis)
{   
    /*
    n = array size
    itens = vetor com os preços dos itens

    altera o vetor 'lis', com o tamanho de cada possivel subsequencia crescente, partindo de i
    */

    for (int i = 0; i < n; i++)
        lis[i] = 1;

    //bottom up
    for (int i = n-1; i >= 0; i--)
    {
        for (int j = i+1; j < n; j++)
        {   
            //teremos uma possivel subsequencia crescente sse itens[i] < itens[j]
            if (itens[i] < itens[j])

                //memoization
                lis[i] = std::max(lis[i], 1 + lis[j]);
            
        }
    }
    
}

void Loja::LDS(int* lds)
{ 
    /*
    n = array size
    itens = vetor com os preços dos itens

    retorna o vetor 'lds',com o tamanho de cada possivel subsequencia decrescente, partindo de i
    */

    for(int i = 0; i < n; i++)
    {
        lds[i] = 1;
    }
    
    //bottom up
    for(int i = n-1; i>=0;i--)
    {
        for (int j = i+1; j < n; j++)
        {
            if (itens[i] > itens[j])
            {
                lds[i] = std::max(lds[i], 1+lds[j]);
            }   
        }
    }

}

int Loja::solution()
{
    int lis[n];
    LIS(lis);

    int lds[n];
    LDS(lds);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = lis[i]+lds[i];
    }
    
    int max = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return (max - 1);
    
}