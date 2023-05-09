#include "carta.h"

void criaCarta(tipo_carta *c,int numero_, char naipe_)
{
    c->numero = numero_;
    c->naipe = naipe_;
}

int validaCarta(tipo_carta *c)
{
    // string com os naipes
    int cartaValida = 1;
    

    if (c->numero < 1 || c->numero > 13)
        cartaValida = 0;

    else if( !(c->naipe == 'P' || c->naipe == 'E' || c->naipe == 'C' || c->naipe == 'O'))  
        cartaValida = 0;
    
    return cartaValida;
    
}
