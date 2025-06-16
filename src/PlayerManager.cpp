#include "PlayerManager.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.hpp"

using namespace std;

// O QUE FALTA:

// Adicionar Excluircadastro 
// Melhorar tratamento de exceções
// Testar e corrigir ordenarRanking() e getMelhorJogador() Obs: ja testei as outras, estao funcionando 
// Fazer os casos de testes 
// Documentar com Doxygen
// Ajuste fino no visual do arquivo de texto e exibição do ranking (allegro)


void PlayerManager::cadastrar(string _nome, string _apelido) {
    try {
        for (Player& jogador : jogadores) {
            if (jogador.getApelido() == _apelido) {
                throw "Apelido já existe";
            }
        }
        jogadores.push_back(Player(_nome, _apelido));
    } catch (const char* e) {
        cout << "Erro: " << e << endl;
    }
}

void PlayerManager::salvar(){
    ofstream arquivo;
    arquivo.open("Jogadores_Cadastrados.txt");

    try{
       if (!arquivo.is_open());
    }catch(exception& arquivoIndisponivel){
        std::cerr << "Erro ao abrir arquivo para escrita.\n";
    }

    for (Player& jogador : jogadores) {
        arquivo << jogador.getNome() << " " << jogador.getApelido() << " " << jogador.getTotal_partidas() << " " << jogador.getPonto_max() << endl;;

    }

    arquivo.close();
}

void PlayerManager::carregar(const std::string& nomeArquivo) {
    jogadores.clear();  // limpa jogadores existentes

    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Arquivo não encontrado. Será criado posteriormente.\n"; //lançar exceção
        return;
    }

    string nome, apelido;
    int total_partidas, pontuacao_max;
    while (arquivo >> nome >> apelido >> total_partidas >> pontuacao_max) {
        jogadores.push_back(Player(nome, apelido, total_partidas, pontuacao_max));
    }

    arquivo.close();
}


void PlayerManager::ordenarRanking() {
    std::sort(jogadores.begin(), jogadores.end(), [](const Player& a, const Player& b) {
        return a.pontuacao_max() > b.pontuacao_max();
    });
}

Player PlayerManager::getMelhorJogador() const {
    if (jogadores.empty()) {
        return Player("Nenhum", 0);
    }

    return *std::max_element(jogadores.begin(), jogadores.end(), [](const Player& a, const Player& b) {
        return a.getPontuacao() < b.getPontuacao();
    });
}

void PlayerManager::exibir() {
    std::cout << "=== RANKING ===\n";
    int pos = 1;

    for(Player& jogador: jogadores){
        cout << pos++ << " "; 
        jogador.imprimir_jogador();
    }

}

const std::vector<Player>& PlayerManager::getJogadores() const {
    return jogadores;
}
