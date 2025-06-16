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
    Player(string _nome, string _apelido); //construtor para novos cadastros
    Player(string _nome, string _apelido, int _pontuacao_max, int _total_partidas); //construtor para recuperar cadastros do arquivo
    int incrementar_partidas();
    void update_pontuacao_max(int pontuacao_atual);
    string getNome();
    string getApelido();
    int getPonto_max();
    int getTotal_partidas();
    void imprimir_jogador();
};

#endif