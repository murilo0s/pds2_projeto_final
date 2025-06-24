#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
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
    CHECK(melhor.getNome() == "Joao" || melhor.getNome() == "Maria");
}
//Testes atualizados de acordo com a doctest.h
