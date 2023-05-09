#ifndef BSTH
#define BSTH

#include "mensage.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <fstream>
#include "memlog.h"



class Node
{
    public:
        
        Mensage email;//Mensage
        Node* left;
        Node* right;


        Node(){left = nullptr; right = nullptr; email = Mensage();};
        ~Node();

        Node(Mensage msg);

};

class BST
{

    public:

        Node* root;
        int height;

        BST(){root = nullptr; height = 0;};
        ~BST();

        void insert(Node* &p, Mensage msg);
        void remove(Node* &p, int E, ofstream &fOut);
        string search(Node* &p, int key);
        Node* substituteNode(Node* &p);
        void preOrder(Node* &p);

        void clean();
};










#endif