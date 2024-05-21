#include "Feromonio.h"
#include <iostream>
#include "Grid.h"

#define DURACAO_FEROMONIO 500

Feromonio::Feromonio(int x, int y, bool achouComida, Renderer* r, Grid* grid, int qtd) : Ponto(x, y){

    //Estabelecer se o feromônio de casa ou de comida
    if (achouComida) {
        this->type = Type::feromonioComida;
        
        durFerCom = DURACAO_FEROMONIO*qtd;
        qtdFerCom = qtd;

        durFerCas = 0;
        qtdFerCas = 0;
    }
        
    else {
        this->type = Type::feromonioCasa;

        durFerCom = 0;
        qtdFerCom = 0;

        durFerCas = DURACAO_FEROMONIO*qtd;
        qtdFerCas = qtd;

    }

    this->r = r;

    this->grid = grid;
}

bool Feromonio::update() {

    // DRAW

    if (this->type == Type::feromonioComida)
        r->changeColor(255, 100, 100, 255);

    else
        r->changeColor(100, 100, 255, 255);

    // if ((qtdFerCas + qtdFerCom) > 1)
        draw(r);

    // DIMINUIR QTD FEROMONIO CASA

    if (durFerCas >= 0)
        durFerCas -= qtdFerCas;

    if (durFerCas <= (qtdFerCas*DURACAO_FEROMONIO)-DURACAO_FEROMONIO)
        qtdFerCas -= 1;

    // DIMINUIR QTD FEROMONIO COMIDA

    if (durFerCom >= 0)
        durFerCom -= qtdFerCom;

    if (durFerCom <= (qtdFerCom*DURACAO_FEROMONIO)-DURACAO_FEROMONIO)
        qtdFerCom -= 1;

    // SE NENHUM TEM DURAÇÃO EXCLUI

    if (durFerCas <= 1 && durFerCom <= 1)
        return 0;

    return 1;
}

int Feromonio::getQtdFer(bool achouComida) {

    if (achouComida)
        return durFerCas;
    return durFerCom;
}

void Feromonio::inserirFer(bool achouComida, int qtd) {

    if (achouComida) {
        qtdFerCom += qtd;
        durFerCom += DURACAO_FEROMONIO*qtd;
    }

    else {
        qtdFerCas += qtd;
        durFerCas += DURACAO_FEROMONIO*qtd;
    }

    if (qtdFerCom > qtdFerCas)
            type = Type::feromonioComida;

}