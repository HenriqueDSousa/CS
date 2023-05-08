#ifndef LOJAH
#define LOJAH

#include <iostream>
#include <vector>

class Loja
{
    public:
        std::vector<int> itens;
        int n;
        //construtor default
        Loja();

        //construtor
        Loja(std::vector<int> vetor);

        //LIS - Longest Increasing Subsequence
        void LIS(int* lis);

        //LDS - Longest Decreasing Subsequence
        void LDS(int* lds);


        int solution();

};




#endif