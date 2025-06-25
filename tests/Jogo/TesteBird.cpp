#include "bird.hpp"
#include "pipe.hpp"
#include "doctest.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <iostream>

TEST_CASE("Bird::Construtor") {
    CHECK(al_init());
    CHECK(al_init_image_addon());
    Bird passarinho(100, 200);
    CHECK(passarinho.getX() == 100);
    CHECK(passarinho.getY() == 200);
    CHECK(passarinho.getSpeedY() == doctest::Approx(0.0f));

    al_shutdown_image_addon();
}

TEST_CASE("Bird::jump") {
    CHECK(al_init());
    CHECK(al_init_image_addon());
    
    Bird passarinho(0, 0);
    passarinho.jump();
    CHECK(passarinho.getSpeedY() == doctest::Approx(-300.0f));
    
    al_shutdown_image_addon();
}

TEST_CASE("Bird::update") {
    CHECK(al_init());
    CHECK(al_init_image_addon());
    
    Bird passarinho(0, 0);

    SUBCASE("Chamada simples") {
        passarinho.jump();
        float antes = passarinho.getSpeedY();
        passarinho.update(0.1);
        float esperado = antes + 800.0f * 0.1f;
        CHECK(passarinho.getSpeedY() == doctest::Approx(esperado));
    }

    SUBCASE("Tempo maior") {
        passarinho.jump();
        float antes = passarinho.getSpeedY();
        passarinho.update(10);
        float esperado = antes + 800.0f * 10.0f;
        if (esperado > 1000.0f) {
            esperado = 1000.0f;
        }
        std::cout << "antes: " << antes << ", esperado: " << esperado << ", getSpeedY(): " << passarinho.getSpeedY() << std::endl;
        CHECK(passarinho.getSpeedY() == doctest::Approx(esperado));
    }

    SUBCASE("Tempo negativo") {
        passarinho.jump();
        float antes = passarinho.getSpeedY();
        passarinho.update(-10);
        float esperado = antes + 800.0f * (-10.0f);
        CHECK(passarinho.getSpeedY() == doctest::Approx(esperado));
    }
    
    al_shutdown_image_addon();
}

/*
TEST_CASE("Bird::render") {
    CHECK(al_init());
    CHECK(al_init_image_addon());

    SUBCASE("Passarinho em posição simples") {
        Bird passarinho(0, 0);
        passarinho.render();
        CHECK(passarinho.getX() == 0);
        CHECK(passarinho.getY() == 0);
    }

    SUBCASE("Passarinho no negativo") {
        Bird passarinho(-1, -3);
        passarinho.render();
        CHECK(passarinho.getX() == -1);
        CHECK(passarinho.getY() == -3);
    }

    SUBCASE("Passarinho em coordenadas quebradas") {
        Bird passarinho(0.75, 7.6);
        passarinho.render();
        CHECK(passarinho.getX() == doctest::Approx(0.75));
        CHECK(passarinho.getY() == doctest::Approx(7.6));
    }

    al_shutdown_image_addon();
}
*/

TEST_CASE("Bird::checkCollision") {
    CHECK(al_init());
    CHECK(al_init_image_addon());

    SUBCASE("Colisão") {
        Bird passarinho(1, 1);
        Pipe cano(1, 1);
        CHECK(passarinho.checkCollision(cano) == true);
    }

    SUBCASE("Objetos muito longe") {
        Bird passarinho(100, 100);
        Pipe cano(0, 0);
        CHECK(passarinho.checkCollision(cano) == false);
    }

    SUBCASE("Objetos muito próximos (sem sobreposição)") {
        Bird passarinho(150, 100);  // Muito à direita do pipe
        Pipe cano(31, 40);
        
        std::cout << "Bird: x=" << passarinho.getX() << ", y=" << passarinho.getY() 
                  << ", w=" << passarinho.getWidth() << ", h=" << passarinho.getHeight() << std::endl;
        std::cout << "Pipe: x=" << cano.getX() << ", y=" << cano.getY() 
                  << ", w=" << cano.getWidth() << ", h=" << cano.getHeight() << std::endl;
        
        bool colisao = passarinho.checkCollision(cano);
        std::cout << "Colisão detectada: " << (colisao ? "true" : "false") << std::endl;
        
        CHECK(colisao == false);
    }

    al_shutdown_image_addon();
}

TEST_CASE("Bird::getWidth") {
    CHECK(al_init());
    CHECK(al_init_image_addon());

    Bird passarinho(1, 10);
    int largura = passarinho.getWidth();
    CHECK((largura == 0 || largura > 0));

    al_shutdown_image_addon();
}

TEST_CASE("Bird::getHeight") {
    CHECK(al_init());
    CHECK(al_init_image_addon());

    Bird passarinho(1, 10);
    int altura = passarinho.getHeight();
    CHECK((altura == 0 || altura > 0));

    al_shutdown_image_addon();
}

TEST_CASE("Bird::setPosition") {
    CHECK(al_init());
    CHECK(al_init_image_addon());
    
    Bird passarinho(0, 0);

    SUBCASE("Reseta para valores padrões") {
        passarinho.setPosition(10, 10);
        CHECK(passarinho.getX() == 10);
        CHECK(passarinho.getY() == 10);
        CHECK(passarinho.getSpeedY() == 0);
    }

    SUBCASE("Reseta para valores muito altos") {
        passarinho.setPosition(100000, 100000);
        CHECK(passarinho.getX() == 100000);
        CHECK(passarinho.getY() == 100000);
        CHECK(passarinho.getSpeedY() == 0);
    }

    SUBCASE("Reseta para valores negativos") {
        passarinho.setPosition(-10, -10);
        CHECK(passarinho.getX() == -10);
        CHECK(passarinho.getY() == -10);
        CHECK(passarinho.getSpeedY() == 0);
    }

    SUBCASE("Reseta para mesmo valor inicial") {
        passarinho.setPosition(0, 0);
        CHECK(passarinho.getX() == 0);
        CHECK(passarinho.getY() == 0);
        CHECK(passarinho.getSpeedY() == 0);
    }
    
    al_shutdown_image_addon();
}
