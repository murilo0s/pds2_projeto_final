#include "bird.hpp"
#include <iostream>
#include <allegro5/allegro_image.h>

Bird::Bird(float startX, float startY): GameObject(startX, startY, 0, 0),
      speedY(0.0f),
      gravity(-0.5f),
      jumpStrength(10.0f),
      bird_img(nullptr) {
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

void Bird::update(float deltaTime) {
    speedY += gravity * deltaTime; // Aplica a gravidade à velocidade vertical
    y += speedY * deltaTime; // Atualiza a posição vertical do pássaro
}

void Bird::render() {
    if (bird_img) {
        al_draw_bitmap(bird_img, x, y, 0); // Desenha o pássaro na tela
    }
}

bool Bird::checkCollision(const GameObject& other) {
    // Implementação simples de colisão retangular
    return (x < other.getX() + other.getWidth() &&
            x + width > other.getX() &&
            y < other.getY() + other.getHeight() &&
            y + height > other.getY());
}

int Bird::getWidth() const {
    return width; // Retorna a largura da imagem do pássaro
}

int Bird::getHeight() const {
    return height; // Retorna a altura da imagem do pássaro
}

void Bird::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
    speedY = 0.0f; // Reseta a velocidade vertical quando reposiciona
}