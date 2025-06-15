#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <string>
#include <vector>



class PlayerManager {
private:
    std::vector<Player> jogadores;

public:
    void cadastrar(const std::string& nome,const std::string& apelido );//cadastro de um jogador
    void salvar(const std::string& nomeArquivo) const;//salvando em um arquivo
    void carregar(const std::string& nomeArquivo);//carregando arquivo
    void ordenarRanking();//
    Player getMelhorJogador() const;
    void exibir() const;
    const std::vector<Player>& getJogadores() const;
};

#endif //  fim do meu PLAYERMANAGER_HPP...
