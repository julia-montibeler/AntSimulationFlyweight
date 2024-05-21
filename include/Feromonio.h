#ifndef FEROMONIO_H
#define FEROMONIO_H

#include "Objeto.h"
#include "Renderer.h"

class Grid;

class Feromonio : public Ponto {

    private:

        int qtdFerCom;
        int durFerCom;

        int qtdFerCas;
        int durFerCas;

        Renderer* r;

    public:

        // Construtor
        Feromonio(int x, int y, bool comida, Renderer* r, Grid* grid, int qtd); 
        
        // Retorna 1 se acabou sua duração
        bool update();

        int getQtdFer(bool achouComida);

        void inserirFer(bool achouComida, int qtd);

        Grid* grid;

};      

#endif