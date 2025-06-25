#include "PlayerManager.hpp"
#include "doctest.h"


TEST_CASE("Cadastro de dois jogadores distintos") {
    PlayerManager pm;
    pm.cadastrar("Joao", "JoaoKiller");
    pm.cadastrar("Maria", "maria123");

    CHECK(pm.getJogadores().size() == 2);
}

TEST_CASE("Cadastro com apelido duplicado é ignorado") {
    PlayerManager pm;
    pm.cadastrar("Joao", "JoaoKiller");
    pm.cadastrar("Maria", "maria123");

    pm.cadastrar("Joao", "JoaoKiller");  // Tentativa duplicada

    CHECK(pm.getJogadores().size() == 2);  // Não deve aumentar
}

TEST_CASE("Salvamento e carregamento de arquivo") {
    PlayerManager pm;
    pm.cadastrar("Joao", "JoaoKiller");
    pm.cadastrar("Maria", "maria123");

    pm.salvar("ranking.txt");

    PlayerManager outro;
    outro.carregar("ranking.txt");

    CHECK(outro.getJogadores().size() == 2);
}

TEST_CASE("Melhor jogador é corretamente identificado") {
    PlayerManager pm;
    pm.cadastrar("Joao", "JoaoKiller");
    pm.cadastrar("Maria", "maria123");

    Player melhor = pm.getMelhorJogador();
    std::string nome = melhor.getNome();
    bool nomeValido = (nome == "Joao") || (nome == "Maria");
    CHECK_MESSAGE(nomeValido, "Nome retornado: " << nome << " (esperado: Joao ou Maria)");


}

