#ifndef MENSAGEH
#define MENSAGEH

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

class Mensage
{   
    public:

        int key;//E
        string content;
        Mensage(){content[0] = 0; key = 0;};
        Mensage(string text, int E);

        ~Mensage();
};





#endif