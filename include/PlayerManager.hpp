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
    /**
     * @brief Cadastro de um jogador
     * 
     * @param _nome Nome do jogador
     * @param _apelido Nick do jogador
     */
    void cadastrar(string _nome, string _apelido);
    /**
     * @brief Remove o cadastro de um jogador
     * 
     * @param _apelido Referencia o nick do jogador
     */
    void remover_cadastro(string _apelido);
    /**
     * @brief Salva em um arquivo
     * 
     * @param nomeArquivo Nome do arquivo
     */
    void salvar(const std::string& nomeArquivo);
    /**
     * @brief Carrega um arquivo
     * 
     * @param nomeArquivo Referencia o arquivo
     */
    void carregar(const string& nomeArquivo);
    /**
     * @brief Ordena os jogadores com base na pontuação
     * 
     */
    void ordenarRanking();
    /**
     * @brief Exibe o melhor jogador com base no ranking
     * 
     * @return Referencia o jogador 
     */
    Player getMelhorJogador() const;
    void exibir();
    const std::vector<Player>& getJogadores() const;
    std::vector<Player>& getJogadores();
};

#endif 