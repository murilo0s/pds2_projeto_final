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
    void salvar();//salvando em um arquivo
    void carregar(const string& nomeArquivo);//carregando arquivo
    void ordenarRanking();//
    Player getMelhorJogador() const;
    void exibir();
    const std::vector<Player>& getJogadores() const;
};

#endif 