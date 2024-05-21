#ifndef FORMIGUEIRO_H
#define FORMIGUEIRO_H

#include "Objeto.h"

class Formigueiro : public Objeto{

    public:

        Formigueiro(int x, int y, int w, int h);
        int qtd_comida;
        
};

#endif