#include "PlayerManager.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.hpp"

using namespace std;

// TODO:

// Testar e corrigir ordenarRanking() e getMelhorJogador() Obs: ja testei as outras, estao funcionando pelo q  parece
// Fazer os casos de testes
// Documentar com Doxygen

void PlayerManager::cadastrar(string _nome, string _apelido)
{
    for (Player &jogador : jogadores)
    {
        if (jogador.getApelido() == _apelido)
        {
            throw std::runtime_error("Apelido já existente");
        }
    }
    jogadores.push_back(Player(_nome, _apelido));
}

void PlayerManager::remover_cadastro(string _apelido){
    int contador = 0;

    for (Player &jogador : jogadores)
    {
        if (jogador.getApelido() == _apelido)
        {
            jogadores.erase(jogadores.begin() + contador);
            
            std::ofstream file("ranking.txt", std::ios::trunc); //exclue informações do arquivo de texto
            
            this->salvar("ranking.txt"); //salva informações novamente, agora sem o jogador que foi excluído

            return;
        }
        contador ++;
    }
    
    throw std::runtime_error("Jogador não encontrado");
};

void PlayerManager::salvar(const std::string& nomeArquivo)
{
    ofstream arquivo;
    arquivo.open(nomeArquivo);

    if (!arquivo.is_open())
    {
        throw std::runtime_error("Erro ao abrir arquivo para escrita: " + nomeArquivo);
    }

    for (Player& jogador : jogadores)
    {
        arquivo << jogador.getNome() << " " << jogador.getApelido() << " "
                << jogador.getPonto_max() << " " << jogador.getTotal_partidas() << endl;
    }

    arquivo.close();
}


void PlayerManager::carregar(const std::string &nomeArquivo)
{
    jogadores.clear(); // limpa jogadores existentes

    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Arquivo não encontrado: " + nomeArquivo);
    }

    string nome, apelido;
    int pontuacao_max, total_partidas;
    while (arquivo >> nome >> apelido >> pontuacao_max >> total_partidas)
    {
        jogadores.push_back(Player(nome, apelido, pontuacao_max, total_partidas));
    }

    arquivo.close();
}

void PlayerManager::ordenarRanking()
{
    std::sort(jogadores.begin(), jogadores.end(), [](const Player &a, const Player &b)
              { return a.getPonto_max() > b.getPonto_max(); });
}

Player PlayerManager::getMelhorJogador() const
{
    if (jogadores.empty())
    {
        std::cerr << "Não há jogadore cadastrados." << std::endl;
        return Player("Nenhum", "Nenhum", 0, 0); // Retorna um jogador vazio se não houver jogadores
    }

    return *std::max_element(jogadores.begin(), jogadores.end(), [](const Player &a, const Player &b)
                             { return a.getPonto_max() < b.getPonto_max(); });
}
                             
void PlayerManager::exibir()
{
    std::cout << "=== RANKING ===\n";
    int pos = 1;

    for (Player &jogador : jogadores)
    {
        cout << pos++ << " ";
        jogador.imprimir_jogador();
    }
}

const std::vector<Player> &PlayerManager::getJogadores() const
{
    return jogadores;
}

std::vector<Player>& PlayerManager::getJogadores() {
    return jogadores;
}
