#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <string>
#include <vector>
#include "Player.hpp"

using namespace std;

class PlayerManager {
private:
    std::vector<Player> jogadores;

public:
    void cadastrar(string _nome, string _apelido);//cadastro de um jogador
    void remover_cadastro(string _apelido);
    void salvar(const std::string& nomeArquivo);//salvando em um arquivo
    void carregar(const string& nomeArquivo);//carregando arquivo
    void ordenarRanking();//ordenando jogares baseando se nos critérios de pontuação
    Player getMelhorJogador() const;//exibindo melhor jogador / trabalha com ordenar ranking
    void exibir();
    const std::vector<Player>& getJogadores() const;
};

#endif 