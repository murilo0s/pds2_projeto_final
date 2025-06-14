#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class Player {
private:
    std::string nome;
    int pontuacao;

public:
    Player(std::string nome, int pontuacao)
        : nome(nome), pontuacao(pontuacao) {}

    std::string getNome() const { return nome; }
    int getPontuacao() const { return pontuacao; }

    void setNome(const std::string& n) { nome = n; }
    void setPontuacao(int p) { pontuacao = p; }
};

class PlayerManager {
private:
    std::vector<Player> jogadores;

public:
    // Adiciona um novo jogador
    void cadastrar(const std::string& nome, int pontuacao) {
        jogadores.push_back(Player(nome, pontuacao));
    }

    // Salva a lista de jogadores em um arquivo
    void salvar(const std::string& ranking.txt) const {
        std::ofstream arquivo(ranking.txt);
        if (!arquivo.is_open()) {
            std::cerr << "Erro ao abrir arquivo para escrita.\n";
            return;
        }

        for (const auto& jogador : jogadores) {
            arquivo << jogador.getNome() << " " << jogador.getPontuacao() << "\n";
        }

        arquivo.close();
    }

    // Carrega jogadores de um arquivo
    void carregar(const std::string& ranking.txt) {
        jogadores.clear(); // limpa lista atual
        std::ifstream arquivo(ranking.txt);
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

    // Ordena os jogadores por pontuação decrescente
    void ordenarRanking() {
        std::sort(jogadores.begin(), jogadores.end(), [](const Player& a, const Player& b) {
            return a.getPontuacao() > b.getPontuacao();
        });
    }

    // Retorna o melhor jogador
    Player getMelhorJogador() const {
        if (jogadores.empty()) {
            return Player("Nenhum", 0);
        }

        return *std::max_element(jogadores.begin(), jogadores.end(), [](const Player& a, const Player& b) {
            return a.getPontuacao() < b.getPontuacao();
        });
    }

    // Exibe o ranking no terminal
    void exibir() const {
        std::cout << "=== RANKING ===\n";
        int pos = 1;
        for (const auto& jogador : jogadores) {
            std::cout << pos++ << ". " << jogador.getNome() << " - " << jogador.getPontuacao() << "\n";
        }
        std::cout << "===============\n";
    }

    // Retorna referência para a lista de jogadores (se quiser usar externamente)
    const std::vector<Player>& getJogadores() const {
        return jogadores;
    }
};

#endif // Final do meu header PLAYERMANAGER_HPP
