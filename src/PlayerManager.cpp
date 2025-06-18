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
            cout << "Apelido já existente";
            return;
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
            
            std::ofstream file("Jogadores_Cadastrados.txt", std::ios::trunc); //exclue informações do arquivo de texto
            
            this->salvar(); //salva informações novamente, agora sem o jogador que foi excluído

            return;
        }
        contador ++;
    }
};

void PlayerManager::salvar()
{
    ofstream arquivo;
    arquivo.open("Jogadores_Cadastrados.txt");

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir arquivo para escrita.\n";
        return;
    }

    for (Player &jogador : jogadores)
    {
        arquivo << jogador.getNome() << " " << jogador.getApelido() << " " << jogador.getTotal_partidas() << " " << jogador.getPonto_max() << endl;
    }

    arquivo.close();
}

void PlayerManager::carregar(const std::string &nomeArquivo)
{
    jogadores.clear(); // limpa jogadores existentes

    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cerr << "Arquivo não encontrado. Será criado posteriormente.\n";
        return;
    }

    string nome, apelido;
    int total_partidas, pontuacao_max;
    while (arquivo >> nome >> apelido >> total_partidas >> pontuacao_max)
    {
        jogadores.push_back(Player(nome, apelido, total_partidas, pontuacao_max));
    }

    arquivo.close();
}

void PlayerManager::ordenarRanking()
{
    std::sort(jogadores.begin(), jogadores.end(), [](const Player &a, const Player &b)
              { return a.pontuacao_max() > b.pontuacao_max(); });
}

Player PlayerManager::getMelhorJogador() const
{
    if (jogadores.empty())
    {
        return Player("Nenhum", 0);
    }

    return *std::max_element(jogadores.begin(), jogadores.end(), [](const Player &a, const Player &b)
                             { return a.getPontuacao() < b.getPontuacao(); });
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
