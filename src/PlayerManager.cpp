#include "PlayerManager.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>





void PlayerManager::cadastrar(const std::string& nome, int pontuacao) {
    jogadores.push_back(Player(nome, pontuacao));
}

void PlayerManager::salvar(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo para escrita.\n";
        return;
    }

    for (const auto& jogador : jogadores) {
        arquivo << jogador.getNome() << " " << jogador.getPontuacao() << "\n";
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

