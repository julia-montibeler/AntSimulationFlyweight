#ifndef GRID_H
#define GRID_H

#include <vector>
#include <forward_list>
using namespace std;

#include "Objeto.h"
#include "Feromonio.h"
#include "Renderer.h"
#include "Formiga.h"
#include "Formigueiro.h"
#include "Persistencia.h"

class Grid {
    private:

        //Listas dos itens do Grid
        
        vector<Objeto*> objetos;

        vector<Objeto*> paredes;

        forward_list<Feromonio*> feromonios;

        vector<Formiga*> formigas;

        vector<Objeto*> comidas;

        int linhas;
        int colunas;

        void criarParede(Objeto* obj);

    public:
        
        //Ponteiro que aponta para um array de ponteiros que apontam para arrays de ponteiros de Pontos
        //Ou seja, um ponteiro para uma matriz de Pontos
        Ponto*** grid;

        // Ponteiro para Formigueiro
        Formigueiro* formigueiro;

        // Construtor
        Grid(int linhas, int colunas);
        
        // Funcoes para inserir Objeto e Formigueiro
        void inserir(Objeto* obj);
        void inserir(Formigueiro* formigueiro);
        
        // Funcoes para inserir Comida e Formiga
        void inserirCom(Objeto* obj);
        void inserirFormigas(int qtd, Renderer* r);

        // Funcao Principal e auxiliar para inserir Feromonio
        void inserirFer(int pos_x, int pos_y, bool achouComida, Renderer *r, int qtd);
        void inserir(Feromonio* feromonio);

        // Exibe todos os elementos do Grid
        void exibir(Renderer *r);

        // Verifica se a posicao indicada pertence ao Grid
        bool existPos(int pos_x, int pos_y);

        //Pega o tipo de um ponto do Grid, o tipo é classificado pelo enum Tipo
        int get_GridPosType(int pos_x, int pos_y); 
        
        // Retorna qtd de feromonios do local
        int getQtdFer(int pos_x, int pos_, bool achouComida);

        void removeObjeto(int pos_x, int pos_y);

        void salvarDados();

};

#endif