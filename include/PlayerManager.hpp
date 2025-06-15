#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <string>
#include <vector>

class Player {
private:
    std::string nome;
    int pontuacao;

public:
    Player(std::string nome, int pontuacao);

    std::string getNome() const;
    int getPontuacao() const;
    void setNome(const std::string& n);
    void setPontuacao(int p);
};

class PlayerManager {
private:
    std::vector<Player> jogadores;

public:
    void cadastrar(const std::string& nome, int pontuacao);
    void salvar(const std::string& nomeArquivo) const;
    void carregar(const std::string& nomeArquivo);
    void ordenarRanking();
    Player getMelhorJogador() const;
    void exibir() const;
    const std::vector<Player>& getJogadores() const;
};

#endif // PLAYERMANAGER_HPP
