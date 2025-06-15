#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>

using namespace std;

//definir classe jogador
class Player{
    private:

    string nome;
    string apelido;
    int pontuacao_max;
    int total_partidas;

    public:            
    Player(string _nome, string _apelido);
    //~Player();


    int incrementar_partidas();
    void update_pontuacao_max(int pontuacao_atual);
    string getNome();
    string getApelido();
    int getPonto_max();
    int getTotal_partidas();
};

#endif