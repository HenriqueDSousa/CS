#include "mensage.h"

Mensage::Mensage(string text, int E)
{   
    key = E;
    content = text;
}

Mensage::~Mensage()
{
    content[0] = 0;
}
