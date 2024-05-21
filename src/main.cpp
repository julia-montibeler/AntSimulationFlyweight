#include <iostream>
using namespace std;

#include "Janela.h"
#include "Formiga.h"
#include "Objeto.h"

#include <cstdlib>
#include <time.h>

int main(int argc, char const *argv[])
{
    
    //Gera SEED para movimento aleatoria das formigas
    srand(time(NULL));

    const char *title = "TESTE";
    
    Janela *janela = new Janela(title, 800, 600);
    janela->loop();
    
}