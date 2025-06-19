#include "bird.hpp"
#include <iostream>
#include <allegro5/allegro_image.h>

Bird::Bird(float startX, float startY): GameObject(startX, startY),
      speedY(0.0f),
      gravity(-0.5f),
      jumpStrength(10.0f),
      bird_img(nullptr),
      width(0),
      height(0) {
    // Carrega a imagem do pássaro
    bird_img = al_load_bitmap("assets/bird.png");
    if (!bird_img) {
        std::cerr << "Erro ao carregar imagem do passaro!" << std::endl;
    } else {
        width = al_get_bitmap_width(bird_img);
        height = al_get_bitmap_height(bird_img);
    }
}

// destrutor
Bird::~Bird() {
    if (bird_img) {
        al_destroy_bitmap(bird_img);
    }
}

// faz o passaro pular
void Bird::jump() {
    speedY = jumpStrength; // Define a velocidade vertical para o valor do pulo
}

void Bird::update() {
    speedY += gravity; // Aplica a gravidade à velocidade vertical
    y += speedY; // Atualiza a posição vertical do pássaro
}

void Bird::render() {
    if (bird_img) {
        al_draw_bitmap(bird_img, x, y, 0); // Desenha o pássaro na tela
    }
}

bool Bird::isColliding(const GameObject& other) {
    /*Esta implementação de colisão é genérica. A lógica de verificação
    será feita na classe Game, que tem acesso ao pássaro e aos canos.
    O método GameObject::isColliding pode ser usado para isso.*/
    return GameObject::isColliding(other);
}

int Bird::getWidth() const {
    return width; // Retorna a largura da imagem do pássaro
}

int Bird::getHeight() const {
    return height; // Retorna a altura da imagem do pássaro
}