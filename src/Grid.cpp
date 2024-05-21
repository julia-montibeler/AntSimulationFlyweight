#include "Grid.h"
#include "FuncoesAuxiliares.h"


#include <algorithm>
#include <iostream>
using namespace std;

bool feromonioRemove (Feromonio *f) {

    if(!f->update()) {
        f->grid->grid[f->get_pos_x()][f->get_pos_y()] = nullptr;
        return 1;
    };
    
    return 0;
}

Grid::Grid(int linhas, int colunas) {

    this->linhas = linhas;
    this->colunas = colunas;

    //Preenche a matriz com Pontos
    grid = new Ponto**[linhas];

    for (int i = 0; i < (linhas); i++) {
        grid[i] = new Ponto*[colunas];
        for (int j = 0; j < (colunas); j++)
            grid[i][j] = nullptr;
    }

    // PAREDES
    criarParede(new Objeto(0, 0, linhas, 1));
    criarParede(new Objeto(0, 0, 1, colunas));
    criarParede(new Objeto(linhas-1, 0, 1, colunas));
    criarParede(new Objeto(0, colunas-1, linhas, 1));
    
}

void Grid::criarParede(Objeto* obj) {

    paredes.push_back(obj);

    //Pega a posição do objeto
    int pos_x = obj->get_pos_x();
    int pos_y = obj->get_pos_y();

    int pos_x2 = pos_x + obj->get_width();
    int pos_y2 = pos_y + obj->get_height();

    //Insere na matriz "grid" um Objeto (que herda Ponto), para sinalizar todas as posições que ele ocupa
    for (int i = pos_x; i < pos_x2; i++)
        for (int j = pos_y; j < pos_y2; j++)  
            if (i < linhas && i >= 0 && j < colunas && j >= 0)
                grid[i][j] = obj;
    
}

void Grid::inserir(Objeto* obj) {

    objetos.push_back(obj);

    //Pega a posição do objeto
    int pos_x = obj->get_pos_x();
    int pos_y = obj->get_pos_y();

    int pos_x2 = pos_x + obj->get_width();
    int pos_y2 = pos_y + obj->get_height();

    //Insere na matriz "grid" um Objeto (que herda Ponto), para sinalizar todas as posições que ele ocupa
    for (int i = pos_x; i < pos_x2; i++)
        for (int j = pos_y; j < pos_y2; j++)  
            if (i < linhas && i >= 0 && j < colunas && j >= 0)
                grid[i][j] = obj;
        
}

void Grid::inserir(Feromonio* feromonio) {
    //Pega a posição do ferômonio e insere na matriz
    int pos_x = feromonio->get_pos_x();
    int pos_y = feromonio->get_pos_y();

    this->feromonios.push_front(feromonio);

    grid[pos_x][pos_y] = feromonio;

}

void Grid::inserir(Formigueiro* formigueiro) {

    formigueiro->type = Type::formigueiro;

    this->formigueiro = formigueiro;

    //Pega a posição do objeto
    int pos_x = formigueiro->get_pos_x();
    int pos_y = formigueiro->get_pos_y();

    int pos_x2 = pos_x + formigueiro->get_width();
    int pos_y2 = pos_y + formigueiro->get_height();

    //Insere na matriz "grid" um Objeto (que herda Ponto), para sinalizar todas as posições que ele ocupa
    for (int i = pos_x; i < pos_x2; i++)
        for (int j = pos_y; j < pos_y2; j++)  
            grid[i][j] = formigueiro;

}

void Grid::inserirCom(Objeto* obj) {

    obj->type = Type::comida;
    comidas.push_back(obj);

    //Pega a posição do objeto
    int pos_x = obj->get_pos_x();
    int pos_y = obj->get_pos_y();

    int pos_x2 = pos_x + obj->get_width();
    int pos_y2 = pos_y + obj->get_height();

    //Insere na matriz "grid" um Objeto (que herda Ponto), para sinalizar todas as posições que ele ocupa
    for (int i = pos_x; i < pos_x2; i++)
        for (int j = pos_y; j < pos_y2; j++)  
            grid[i][j] = obj;

}

void Grid::inserirFer(int pos_x, int pos_y, bool achouComida, Renderer *r, int qtd) {

    if (grid[pos_x][pos_y] == nullptr)
        inserir(new Feromonio(pos_x, pos_y, achouComida, r, this, qtd));

    else if (grid[pos_x][pos_y]->type == Type::feromonioComida || grid[pos_x][pos_y]->type == Type::feromonioCasa)
        static_cast<Feromonio*>(grid[pos_x][pos_y])->inserirFer(achouComida, qtd);

}

void Grid::inserirFormigas(int qtd, Renderer* r) {

    int angulo, pos_x, pos_y;

    FormigaFlyweight* formigaPadrao = new FormigaFlyweight(30, 180, r);

    //Gera a quantidade de formigas especificada, com uma direção aleatória
    for (int i = 0; i < qtd; i++) {

        angulo = gerar_random(0, 360);
        pos_x = formigueiro->get_pos_x() + formigueiro->get_width()/2 + formigueiro->get_width() * cos(conv_radianos(angulo));

        pos_y = formigueiro->get_pos_y() + formigueiro->get_height()/2 + formigueiro->get_height() * sin(conv_radianos(angulo));

        formigas.push_back(new Formiga(pos_x, pos_y, 20, 20, 1, angulo, formigaPadrao));

    }

}


void Grid::exibir(Renderer *r) {

    r->changeColor(255, 255, 255, 255);

    // Exibir Objetos

    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->draw(r);

    // Exibir Paredes
    for (int i = 0; i < paredes.size(); i++)
        paredes[i]->draw(r);

    // Exibir Formigas

    for (int i = 0; i < formigas.size(); i++) {
            
        if (formigas[i]->soltarFeromonio()) {

            int pos_x = formigas[i]->get_pos_x() + formigas[i]->get_width()/2;
            int pos_y = formigas[i]->get_pos_y() + formigas[i]->get_height()/2;

            inserirFer(pos_x, pos_y, formigas[i]->hasFood, r, formigas[i]->intensidadeFer);

        }
        
        formigas[i]->visao(this, r);
        formigas[i]->girar_aleatorio();
        formigas[i]->mover_dir(this);
        
        formigas[i]->draw(r);

    }

    // Exibir Feromonios
    feromonios.remove_if(feromonioRemove);

    // Exibir Formigueiro
    r->changeColor(255, 255, 0, 255);
    formigueiro->draw(r);

    // Exibir Comida
    r->changeColor(100, 255, 100, 255);
    for (int i=0; i < comidas.size(); i++)
        comidas[i]->draw(r);

}

int Grid::get_GridPosType(int pos_x, int pos_y) {
    
    if ( (pos_x >= 0) && (pos_x < linhas) && (pos_y >= 0) && (pos_y < colunas)) {
        if (grid[pos_x][pos_y])
            return grid[pos_x][pos_y]->type;

        return -2;
    }
    
    return -1;

}

int Grid::getQtdFer(int pos_x, int pos_y, bool AchouComida) {

    return static_cast<Feromonio*>(grid[pos_x][pos_y])->getQtdFer(AchouComida);

}

bool Grid::existPos(int pos_x, int pos_y) {

    if ( (pos_x >= 0) && (pos_x < linhas) && (pos_y >= 0) && (pos_y < colunas))
        return 1;

    return 0;

}

void Grid::removeObjeto(int pos_x, int pos_y) {

    if (existPos(pos_x, pos_y))
        if (get_GridPosType(pos_x, pos_y) == 1) {
            Objeto *o = static_cast<Objeto*>(grid[pos_x][pos_y]);

            int o_pos_x1 = o->get_pos_x();
            int o_pos_y1 = o->get_pos_y();
            int o_pos_x2 = o_pos_x1 + o->get_width();
            int o_pos_y2 = o_pos_y1 + o->get_height();

            auto it = find(objetos.begin(), objetos.end(), o);
            objetos.erase(it);
            delete grid[pos_x][pos_y];

            for (int i = o_pos_x1; i <  o_pos_x2; i++)
                for (int j = o_pos_y1; j < o_pos_y2; j++)
                    if (existPos(i, j)) 
                        grid[i][j] = nullptr;

        }
}

void Grid::salvarDados() {

    int* dados = new int[objetos.size()];

    int j = 0;
    for (int i = 0; i < objetos.size(); i++){

        dados[j] = objetos[i]->get_pos_x();
        j++;
        dados[j] = objetos[i]->get_pos_y();
        j++;

    }

    escreverDados(dados, objetos.size()*2);

}