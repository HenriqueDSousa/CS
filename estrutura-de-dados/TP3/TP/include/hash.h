#ifndef HASHH
#define HASHH

#include "bst.h"
#include "mensage.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <fstream>
#include "memlog.h"

class Hash
{
    public:
        
        int id;
        BST* hashTable;
        Hash(){hashTable = nullptr; id = 0;};
        ~Hash();

        Hash(int m);
        void acessaTabela(int m);
};



#endif