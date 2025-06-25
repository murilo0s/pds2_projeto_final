#include "doctest.h"
#include "pipe.hpp"
#include "bird.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

struct AllegroFixture {
    AllegroFixture() {
        al_init();
        al_init_image_addon();
    }
    ~AllegroFixture() {
        al_uninstall_system();
    }
};

TEST_CASE_FIXTURE(AllegroFixture, "Verifica se a imagem do pipe pode ser carregada") {
    ALLEGRO_BITMAP* bmp = al_load_bitmap("assets/pipe/pipe.png");
    CHECK_MESSAGE(bmp != nullptr, "Falha ao carregar assets/pipe/pipe.png");
    if (bmp) al_destroy_bitmap(bmp);
}

/*
TEST_CASE("Pipe inicializa corretamente com posição") {
    al_init();
    al_init_image_addon();
    
    Pipe pipe(400, 300);
    
    CHECK(pipe.getX() == 400);
    // Não há getter para gapY ou passed
    
    al_uninstall_system();
}
*/

/*
TEST_CASE("Depuração: Carregamento da imagem do pipe") {
    al_init();
    al_init_image_addon();
    ALLEGRO_BITMAP* bmp = al_load_bitmap("assets/pipe/pipe.png");
    if (!bmp) {
        std::cout << "Falha ao carregar assets/pipe/pipe.png" << std::endl;
    } else {
        std::cout << "Imagem carregada com sucesso!" << std::endl;
        al_destroy_bitmap(bmp);
    }
    al_uninstall_system();
}
*/

TEST_CASE_FIXTURE(AllegroFixture, "Pipe update() movimenta corretamente") {
    Pipe p(500, 300);
    float xInicial = p.getX();
    p.update(1.0f); // simula 1 segundo
    CHECK(p.getX() < xInicial); // deve ter se movido pra esquerda
}

TEST_CASE_FIXTURE(AllegroFixture, "Bird passa pelo Pipe") {
    Bird b(600, 300); // está após o pipe
    Pipe p(400, 300);
    CHECK(p.isPassed(b) == true);
}

TEST_CASE_FIXTURE(AllegroFixture, "Bird não passou ainda pelo Pipe") {
    Bird b(150, 300); // está antes do pipe
    Pipe p(400, 300);
    CHECK(p.isPassed(b) == false);
}

TEST_CASE_FIXTURE(AllegroFixture, "Colisão com pipe superior e inferior") {
    Bird b(400, 300);  // posição central
    Pipe p(400, 300);  // mesmo x do pássaro

    // Alinhar bird e pipe para simular colisão
    b.setPosition(p.getX() + 10, 100);  // altura da colisão superior
    CHECK(p.checkCollision(b) == true);

    b.setPosition(p.getX() + 10, 500);  // altura da colisão inferior
    CHECK(p.checkCollision(b) == true);
}
