#include "Player.hpp"
#include <iostream>

using namespace std;

Player::Player(string _nome, string _apelido){
    this->nome = _nome;
    this->apelido = _apelido;
    this->pontuacao_max = 0;
    this->total_partidas = 0;
};

int Player::incrementar_partidas(){
    this->total_partidas ++;
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