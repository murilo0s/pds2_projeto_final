#include "PlayerManager.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>


// Adicionar Excluircadastro e checar apelidoexiste 


void PlayerManager::cadastrar(const std::string& nome, const std::string& apelido) {
    Player *jogador=new Player(nome,apelido);
}
bool apelidoExiste(const std::string& apelido) const {
    for (const auto& jogador : jogadores) {
        if (jogador.getApelido() == apelido) {
            return true;
        }
    }
    return false;
}
void PlayerManager::salvar(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo para escrita.\n";
        return;
    }

    for (const auto& jogador : jogadores) {
        arquivo << jogador.getNome() << " " << jogador.getPonto_max () << jogador.getTotal_partidas() <<jogador.getApelido() << "\n";
    }

    arquivo.close();
}

void PlayerManager::carregar(const std::string& nomeArquivo) {
    jogadores.clear();
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Arquivo não encontrado. Será criado posteriormente.\n";
        return;
    }

    std::string nome;
    int pontuacao;
    while (arquivo >> nome >> pontuacao) {
        jogadores.push_back(Player(nome, pontuacao));
    }

    arquivo.close();
}

void PlayerManager::ordenarRanking() {
    std::sort(jogadores.begin(), jogadores.end(), [](const Player& a, const Player& b) {
        return a.getPontuacao() > b.getPontuacao();
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

void PlayerManager::exibir() const {
    std::cout << "=== RANKING ===\n";
    int pos = 1;
    for (const auto& jogador : jogadores) {
        std::cout << pos++ << ". " << jogador.getNome() << " - " << jogador.getPontuacao() << "\n";
    }
    std::cout << "===============\n";
}

const std::vector<Player>& PlayerManager::getJogadores() const {
    return jogadores;
}

