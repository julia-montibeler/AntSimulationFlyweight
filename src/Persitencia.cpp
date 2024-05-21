#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 

#include "Persistencia.h"

using namespace std;

int* lerDados() {
    fstream arquivo;
    string linha, str;
    arquivo.open("./Dados.txt", ios::in);
    int num = 0, cont = 0;
    
    if (arquivo.is_open()) {
        cont = qtdObj();
        int *dados = new int[cont];
        
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            while (getline(ss, str, ';')) {
                dados[num] = stoi(str);
                num++;
            }  
        }
        
        arquivo.close();
        return dados;
    }

    arquivo.close();
    return nullptr; // Retorna um ponteiro nulo em caso de erro na leitura do arquivo
}

void escreverDados(int *dados, int qtd) {

    fstream arquivo;
    string linha, str;
    arquivo.open("./Dados.txt", ios::out | ios::trunc);

    int i = 0;

    while (i < qtd) {

        arquivo << dados[i]; 
        arquivo << ";";
        i += 1;
        arquivo << dados[i];
        arquivo << "\n";
        i += 1; 

    }
    
    arquivo.close();

}

int qtdObj() {
    fstream arquivo;
    string linha, str;
    arquivo.open("./Dados.txt", ios::in);
    int cont = 0;
    
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            while (getline(ss, str, ';')){
                cont++;
            }
        }
        
        arquivo.close();
    }
    
    return cont;
}

