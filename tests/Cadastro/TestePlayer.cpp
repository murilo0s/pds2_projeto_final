#include "doctest.h"
#include "Player.hpp"


TEST_CASE("Player::incrementar_partidas"){
    Player jogador("Jogador1", "Jog1");

    SUBCASE("Uma chamada simples"){
        jogador.incrementar_partidas();
     
        CHECK(jogador.getTotal_partidas() == 1);
    }    

    SUBCASE("Chamada maior"){
        for(int i = 0; i < 30; i++) {
            jogador.incrementar_partidas();
        }
        CHECK(jogador.getTotal_partidas() == 30);
    }
}

TEST_CASE("Player::update_pontuacao_max"){
    Player jogador("Jogador1", "Jog1");

    SUBCASE("Pontuação anterior menor que a atual"){
        jogador.update_pontuacao_max(5);
        jogador.update_pontuacao_max(10);
     
        CHECK(jogador.getPonto_max() == 10);
    }    
    
    SUBCASE("Pontuação anterior igual a atual"){
        jogador.update_pontuacao_max(10);
        jogador.update_pontuacao_max(10);
     
        CHECK(jogador.getPonto_max() == 10);
    }

    SUBCASE("Pontuação anterior maior que a atual"){
        jogador.update_pontuacao_max(10);
        jogador.update_pontuacao_max(5);
     
        CHECK(jogador.getPonto_max() == 10);
    }
}

TEST_CASE("Player::string getNome()"){
    Player jogador("Jogador1", "Jog1");
    
    CHECK(jogador.getNome()== "Jogador1");
}

TEST_CASE("Player::getApelido()"){
    Player jogador("Jogador1", "Jog1");
    
    CHECK(jogador.getApelido()== "Jog1");
}

TEST_CASE("Player::getTotal_partidas"){
    Player jogador("Jogador1", "Jog1");

    CHECK(jogador.getTotal_partidas() == 0);
}
