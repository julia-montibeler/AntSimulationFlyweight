#ifndef FORMIGA_H
#define FORMIGA_H

#include "Objeto.h"
#include "Renderer.h"
#include "Formigueiro.h"
#include "FormigaFlyweight.h"

#include <SDL2/SDL_image.h>

class Grid;

class Formiga : public Objeto {

    private:

        // Vetor que indica Direção da Formiga
        float dir_x;
        float dir_y;

        // Posição Relativa
        float pos_xR;
        float pos_yR;

        // Modulo do Vetor anterior, indica quantos pixels a formiga se move
        float velocidade;

        // Angulo do Vetor de direção da formiga
        int angulo;

        // Mudança que ocorre no angulo
        int aceleracao_angular;

        // Intervalo entre soltar feromonio
        int tempoFer = 10;

        FormigaFlyweight* formigaFlyweight;

    public:

        // Construtor
        Formiga(int x, int y, int w, int h,float vel, int angulo_inicial, FormigaFlyweight* formigaFlyweight);

        // Girar o vetor de direção em um angulo aleatorio
        void girar_vetor(int ang);

        // Gira Formiga em uma direção aleatoria
        void girar_aleatorio();

        // Move formiga, conforme a direção indicada pelo vetor
        void mover_dir(Grid* grid);

        // Funcões para mover o Formiga
        void move_x(float v);
        void move_y(float v);

        // Verifica se houve colisão com outro objeto
        void visao(Grid* grid, Renderer *r);

        // Desenha formiga na tela
        void draw(Renderer *r);

        void update();

        // Retorna 1 se for momento de soltar feromonio ou 0 se não
        bool soltarFeromonio();

        // 0 se está carregando comida ou 1 se está com comida
        bool hasFood = 0;

        // Intensidade do feromonio solto, varia conforme distancia da casa ou comida
        int intensidadeFer;

        void colide(int posEsqType, int posDirType);

        void respawn(Formigueiro *formigueiro);

        
        
};

#endif