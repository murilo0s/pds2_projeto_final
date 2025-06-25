#include "doctest.h"
#include "pipe.hpp"
#include "bird.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

TEST_CASE("Pipe inicializa corretamente com posição") {
    al_init(); // Inicializa Allegro
    al_init_image_addon(); // Para carregar imagens

    Pipe p(400, 300);
    CHECK(p.getX() == 400);
    CHECK(p.getWidth() > 0);  // se a imagem for carregada

    al_uninstall_system();
}

TEST_CASE("Pipe update() movimenta corretamente") {
    al_init(); 
    al_init_image_addon();

    Pipe p(500, 300);
    float xInicial = p.getX();
    p.update(1.0f); // simula 1 segundo
    CHECK(p.getX() < xInicial); // deve ter se movido pra esquerda

    al_uninstall_system();
}

TEST_CASE("Bird passa pelo Pipe") {
    al_init(); 
    al_init_image_addon();

    Bird b(600, 300); // está após o pipe
    Pipe p(400, 300);
    CHECK(p.isPassed(b) == true);

    al_uninstall_system();
}

TEST_CASE("Bird não passou ainda pelo Pipe") {
    al_init(); 
    al_init_image_addon();

    Bird b(390, 300); // está antes do pipe
    Pipe p(400, 300);
    CHECK(p.isPassed(b) == false);

    al_uninstall_system();
}
TEST_CASE("Colisão com pipe superior e inferior") {
    al_init(); al_init_image_addon();

    Bird b(400, 300);  // posição central
    Pipe p(400, 300);  // mesmo x do pássaro

    // Alinhar bird e pipe para simular colisão
    b.setPosition(p.getX() + 10, 100);  // altura da colisão superior
    CHECK(p.checkCollision(b) == true);

    b.setPosition(p.getX() + 10, 500);  // altura da colisão inferior
    CHECK(p.checkCollision(b) == true);

    al_uninstall_system();
}
