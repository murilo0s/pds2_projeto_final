#include "doctest.h"
#include "PlayerManager.hpp"


TEST_CASE("Cadastro de dois jogadores distintos") {
    PlayerManager pm;
    pm.cadastrar("Joao", "JoaoKiller");
    pm.cadastrar("Maria", "maria123");

    CHECK(pm.getJogadores().size() == 2);
}

TEST_CASE("Cadastro duplicado lança exceção") {
    PlayerManager pm;
    pm.cadastrar("Joao", "JoaoKiller");
    
    CHECK_THROWS_WITH(pm.cadastrar("Joao", "JoaoKiller"), "Apelido já existente");
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
    bool nomeValido = (melhor.getNome() == "Joao") || (melhor.getNome() == "Maria");
    CHECK(nomeValido);
}
//Testes atualizados de acordo com a doctest.h
