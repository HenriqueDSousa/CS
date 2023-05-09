#include "hash.h"

Hash::Hash(int m)
{   
    //por padrao, o id da tabela sera o valor de m
    id = 0;
    hashTable = (BST*)malloc(m * sizeof(BST));
    
    for (int i = 0; i < m; i++)
    {
        escreveMemLog((long int)(&(hashTable[m])), sizeof(BST*), id);
    }

}

void Hash::acessaTabela(int m)
{   
    //acessa cada arvore da de cada posicao da tabela hash
    //cada arvore é caminhada por meio do caminhamento pre ordem

    for (int i = 0; i < m; i++)
    {   
        hashTable[m].preOrder(hashTable[m].root);
    }
    

}

Hash::~Hash()
{    
    
    free(hashTable);
}
