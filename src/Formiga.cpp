#include "Formiga.h"
#include "FuncoesAuxiliares.h"
#include "FormigaFlyweight.h"
#include "Grid.h"

#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
using namespace std;

#define INTENDISADE_FER 10

Formiga::Formiga(int x, int y, int w, int h,float vel, int angulo_inicial, FormigaFlyweight* formigaFlyweight) : Objeto(x, y, w, h){

    this->velocidade = vel;

    this->dir_x = vel * cos(conv_radianos(angulo_inicial));
    this->dir_y = vel * sin(conv_radianos(angulo_inicial));

    this->pos_xR = x;
    this->pos_yR = y;

    this->angulo = angulo_inicial;
    this->aceleracao_angular = (gerar_random(-1, 1));

    this->type = Type::formiga;

    this->intensidadeFer = INTENDISADE_FER;

    this->formigaFlyweight = formigaFlyweight;
}

void Formiga::girar_vetor(int angulo) {

    if (angulo > 30)
        angulo = 30;
    else if (angulo < -30)
        angulo = -30;

    this->angulo = int(this->angulo + angulo) % 360;

    dir_x = velocidade * cos(conv_radianos(this->angulo));
    dir_y = velocidade * sin(conv_radianos(this->angulo));
}

void Formiga::girar_aleatorio() {

    // Se o número aleatório for 0, a direção da formiga muda;
    if ((gerar_random(0,50)) == 0)
        aceleracao_angular = gerar_random(-1,1);

    girar_vetor(aceleracao_angular);

}

void Formiga::colide(int posEsqType, int posDirType) {

    if (posDirType == posEsqType) {
            angulo *= -1;   
        }
            
    else {

        if (dir_x < 0) {

            if (dir_y < 0) angulo += 90;
            else angulo -= 90;
        }

        else {
            
            if (dir_y < 0) angulo -= 90;
            else angulo += 90;
        }
    }

    girar_vetor(0);

}

void Formiga::mover_dir(Grid* grid) {
    
    int pos_type = grid->get_GridPosType((dir_x*height)+pos_x+height/2, (dir_y*width)+pos_y+width/2);
    
    if (pos_type != -2) {

        // SE VAI COLIDIR COM PAREDE
        if ( (pos_type == 1 || pos_type == -1)) {
            int pos_type_lado_dir = grid->get_GridPosType(((dir_x*height)+pos_x+height/2)+1, ((dir_y*width)+pos_y+width/2));
            int pos_type_lado_esq = grid->get_GridPosType(((dir_x*height)+pos_x+height/2)-1, ((dir_y*width)+pos_y+width/2));
            colide(pos_type_lado_esq, pos_type_lado_dir);
        }
        
        // SE VAI COLIDIR COM COMIDA
        else if (pos_type == 4) {
            angulo += 180;
            girar_vetor(0);
            hasFood = 1;
            intensidadeFer = INTENDISADE_FER;
        }
        
        // SE VAI COLIDIR COM FORMIGUEIRO
        else if (pos_type == Type::formigueiro) {

            angulo += 180;
            girar_vetor(0);

            if (hasFood)
                grid->formigueiro->qtd_comida += 1;

            hasFood = 0;
            intensidadeFer = INTENDISADE_FER;
        }
            
    }

    pos_type = (grid->get_GridPosType(pos_x + dir_x, pos_y + dir_y));

    move_x(dir_x);
    move_y(dir_y);

    // SE ENTRAR NA PAREDE TELEPORTA PRA LONGE
    if (grid->get_GridPosType(pos_x + width/2, pos_y + height/2) == 1) {
        respawn(grid->formigueiro);
    }

}

void Formiga::move_x(float v) {

    //Para quando a formiga anda com alguma angulação, pos_xR é a quantidade de movimento real do eixo x;
    pos_xR += v;
    pos_x = pos_xR;

    //O rect é o objeto do SDL que representa a formiga. É alterado x para alterar na tela;
    rect.x = pos_x;

}

void Formiga::move_y(float v) {
    
    //Para quando a formiga anda com alguma angulação, pos_yR é a quantidade de movimento real do eixo y;
    pos_yR += v;
    pos_y = pos_yR;

    //O rect é o objeto do SDL que representa a formiga. É alterado y para alterar na tela;
    rect.y = pos_y;

}

void Formiga::draw(Renderer *r){

    // if (hasFood)
    //     r->changeColor(100,255,100,255);
    
    // else
    //     r->changeColor(255,255,255,255);

    SDL_RenderCopy(r->get_sdlRenderer(), formigaFlyweight->getFormigaTexture(), NULL, &rect);
    
    // r->drawRect(&rect);
    // r->drawLine(pos_x + width/2, pos_y + height/2, pos_x + width/2 + dir_x * width , pos_y + height/2 + dir_y * height);

}

bool Formiga::soltarFeromonio() {

    //Executa toda vez que a formiga anda, quando tempoFer chegar a 0, solta o ferômonio,
    //e restabelece o tempoFer para 10. Retorna 1 se soltar o ferômonio, 0 se não

    tempoFer -= 1;

    if (intensidadeFer > 1)
        intensidadeFer -= 1;

    if (tempoFer == 0) {
        
        tempoFer = 10;
        return 1;
    }

    return 0;
}

void Formiga::visao(Grid* grid, Renderer *r) {

    int vis_x;
    int vis_y; 

    int qtdFer = 0;
    int qtdMaxFer = 0;
    int angMax = -formigaFlyweight->getAngVisao()/2 + formigaFlyweight->getAngVisao()/3;

    for (int ini = -formigaFlyweight->getAngVisao()/2; ini < formigaFlyweight->getAngVisao()/2; ini+= formigaFlyweight->getAngVisao()/3) {
        for (int ang = ini; ang < ini+formigaFlyweight->getAngVisao()/3; ang++) {
            
            vis_x = (formigaFlyweight->getDistVisao() * cos(conv_radianos(ang + this->angulo))) + pos_x + width/2;
            vis_y = (formigaFlyweight->getDistVisao() * sin(conv_radianos(ang + this->angulo))) + pos_y + height/2;

            int pos_type = grid->get_GridPosType(vis_x, vis_y);

            // SE ENXERGA FEROMONIO
            if (pos_type == Type::feromonioComida || pos_type == Type::feromonioCasa)
                qtdFer += grid->getQtdFer(vis_x, vis_y, hasFood);
            
            // SE ENXERGA COMIDA
            if (pos_type == Type::comida && !hasFood)
                qtdFer += 1000000;

            // SE ENXERGA FORMIGUEIRO
            else if (pos_type == Type::formigueiro && hasFood)
                qtdFer += 1000000;

            // SE ENXERGA OBSTACULO
            else if (pos_type == 1 || pos_type == -1)
                qtdFer -= 100000;
        }

        if (qtdFer > qtdMaxFer) {
            qtdMaxFer = qtdFer;
            angMax = ini;
        }
        
        else if (qtdFer == qtdMaxFer && angMax != -formigaFlyweight->getAngVisao()/6)
            if (gerar_random(0,1)) {
                angMax = ini;
            } 

        qtdFer = 0;
            
    }

    girar_vetor((angMax + formigaFlyweight->getAngVisao()/6));
}

void Formiga::respawn(Formigueiro *formigueiro) {

    angulo = gerar_random(0, 360);
    pos_x = formigueiro->get_pos_x() + formigueiro->get_width()/2 + formigueiro->get_width() * cos(conv_radianos(angulo));
    pos_xR = pos_x;

    pos_y = formigueiro->get_pos_y() + formigueiro->get_height()/2 + formigueiro->get_height() * sin(conv_radianos(angulo));
    pos_yR = pos_y;
    
}