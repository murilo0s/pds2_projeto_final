#include "Player.hpp"
#include <iostream>

using namespace std;

Player::Player(string _nome, string _apelido){
    this->nome = _nome;
    this->apelido = _apelido;
    this->pontuacao_max = 0;
    this->total_partidas = 0;
};

Player::Player(string _nome, string _apelido, int _pontuacao_max, int _total_partidas){
    this->nome = _nome;
    this->apelido = _apelido;
    this->pontuacao_max = _pontuacao_max;
    this->total_partidas = _total_partidas;
};

int Player::incrementar_partidas(){
    return this->total_partidas ++;
};

void Player::update_pontuacao_max(int pontuacao_atual){
    if(pontuacao_atual > this->pontuacao_max)
        this->pontuacao_max = pontuacao_atual;
};

string Player::getNome(){
    return this->nome;
};

string Player::getApelido(){
    return this->apelido;
};

int Player::getPonto_max(){
    return this->pontuacao_max;
};

int Player::getTotal_partidas(){
    return this->total_partidas;
};

void Player::imprimir_jogador(){
    cout << this->nome << " " << this->apelido << " " << this->total_partidas << " " << this->pontuacao_max << endl;
}