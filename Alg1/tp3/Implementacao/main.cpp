#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "loja.hpp"

int main() {


  int N, R, preco;
  std::cin>>N;


  for( int testes = 0; testes < N; testes++)
  {
    std::cin>>R;

    std::vector<int> array;

    //inserindo itens
    for (int rolos = 0; rolos < R; rolos++)
    {
        std::cin>>preco;

        array.push_back(preco);
    }

    Loja store = Loja(array);
    
    int resposta = store.solution();

    std::cout<<resposta<<std::endl;

  } 



  return(0);
}
