#include <cassert>
#include <iostream>
#include "PlayerManager.hpp"
#include <string>

using namespace std;


int main() {
        PlayerManager pm;
//Teste do cadastro:


    std::cout << "=== TestePlayerManager ===\n";

    // Teste 1: Cadastro de jogadores únicos
    pm.cadastrar("Joao", "JoaoKiller");
    pm.cadastrar("Maria", "maria123");
    assert(pm.getJogadores().size() == 2);
    std::cout << "[OK] Cadastro de dois jogadores distintos\n";

    // Teste 2: Cadastro com apelido duplicado (não deve adicionar)
    pm.cadastrar("Joao", "JoaoKiller");  // Mesmo apelido
    assert(pm.getJogadores().size() == 2);    // Continua com 2
    std::cout << "[OK] Apelido duplicado ignorado\n";

    // Teste 3: Salvar e carregar de arquivo
    pm.salvar("ranking.txt");  // salva em ranking.txt

    PlayerManager outro;
    outro.carregar("ranking.txt");
    assert(outro.getJogadores().size() == 2);
    std::cout << "[OK] Salvamento e carregamento de arquivo\n";

    // Teste 4: Melhor jogador
    Player melhor = outro.getMelhorJogador();
    assert(melhor.getNome() == "Joao" || melhor.getNome() == "Maria");  // ambos têm 0 ponto
    std::cout << "[OK] Recuperação do melhor jogador\n";

    std::cout << "Todos os testes passaram!\n";

    return 0;
}
