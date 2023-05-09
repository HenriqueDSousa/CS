#include <iostream>
#include <fstream>
#include "bst.h"
#include "mensage.h"

using namespace std;

void swapNodes(Node* p, Node* q)
{   
    Node *aux = new Node();
    aux->email = p->email;
    p->email = q->email;
    q->email = aux->email;

    delete(aux);
}

Node::Node(Mensage msg)
{   
    left = nullptr;
    right = nullptr;

    email = Mensage(msg.content, msg.key);

}

Node::~Node()
{
    left = nullptr;
    right = nullptr;
    email.~Mensage();
}


void BST::insert(Node* &p, Mensage msg)
{
    if(p == NULL)
    {   

        p = new Node(msg);
        ESCREVEMEMLOG((long int)(p), sizeof(Node*), 0);
        
    }
    
    else
    {
        if( (msg.key) < (p->email).key)
        {   
            insert(p->left, msg);
        }
        else if((msg.key) > (p->email).key)
        {   
            insert(p->right, msg);    
        }
    }

}

string BST::search(Node* &p, int E)
{   
    if(p == nullptr)
    {
        return "MENSAGEM INEXISTENTE";
    }

    if((p->email).key == E)
    {   
        LEMEMLOG((long int)(p), sizeof(Node*), 0);
        return (p->email).content;
    }

    else if (E < (p->email).key )
    {   
        return search(p->left, E);
    }

    else
    {
        return search(p->right, E);
    }
    
}


Node* BST:: substituteNode(Node* &p)
{   

    //Para o funcionamento correto desta funcao, deve-se passar o filho da direita da
    //raiz como parâmetro
    Node* aux = p;
    while ( aux && aux->left != nullptr)
    {
        aux = aux->left;
    }

    return aux;
}

void BST::remove(Node* &p, int E, std::ofstream &fOut)
{   
    if (p == NULL)
    {   
        fOut<<"ERRO: MENSAGEM INEXISTENTE" <<endl;
        return;
    }
    

    if (p->email.key == E)
    {   

        //node sem filhos
        if(p->left == nullptr && p->right == nullptr)
        {   
            LEMEMLOG((long int)(p), sizeof(Node*), 0);
            p = nullptr;
            fOut<<"OK: MENSAGEM APAGADA" <<endl;
            return;
        }

        //node com somenteo filho da direita
        else if( p->left == nullptr && p->right != nullptr)
        {   
            LEMEMLOG((long int)(p), sizeof(Node*), 0);
            LEMEMLOG((long int)(p->right), sizeof(Node*), 0);
            p = p->right;

            fOut<<"OK: MENSAGEM APAGADA" <<endl;

            return;

        }

        //node com somente o filho da esquerda
        else if( p->left != nullptr && p->right == nullptr)
        {   
            
            LEMEMLOG((long int)(p), sizeof(Node*), 0);
            LEMEMLOG((long int)(p->left), sizeof(Node*), 0);
            p = p->left;

            fOut<<"OK: MENSAGEM APAGADA" <<endl;

            return;
        }

        //node com o filho da dirita e o da esquerda
        else if( p->left != nullptr && p->right != nullptr)
        {   
            Node* substitute = substituteNode(p->right);
            swapNodes(p, substitute);

            LEMEMLOG((long int)(p), sizeof(Node*), 0);
            LEMEMLOG((long int)(substitute), sizeof(Node*), 0);

            substitute = nullptr;
            fOut<<"OK: MENSAGEM APAGADA" <<endl;

            return;
        }
    }

    else if (p->email.key < E)
        remove(p->left, E, fOut);


    else if (p->email.key > E)
        remove(p->right, E, fOut);    
    

}

//funcao utilizada para fins de registro de memoria
void BST::preOrder(Node* &p)
{
    if (p == nullptr)
        return;
    
    //o id utilizado no escreve memlog sera o id do email recebido
    LEMEMLOG((long int)(p), sizeof(Node*), 0);
    preOrder(p->left);
    preOrder(p->right);
}