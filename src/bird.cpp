#include "bird.hpp"
#include <iostream>
#include <allegro5/allegro_image.h>

Bird::Bird(float startX, float startY): GameObject(startX, startY, 0, 0),
      gravity(800.0f),
      jumpStrength(-300.0f),
      bird_img(nullptr) {
    // Carrega a imagem do pássaro
    bird_img = al_load_bitmap("assets/bird/plane.png");
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
    // std::cout << "PULO!" << std::endl;
    setSpeed(getSpeedX(), jumpStrength); // Define a velocidade vertical para o valor do pulo
}

void Bird::update(float deltaTime) {
    float currentSpeedY = getSpeedY();
    currentSpeedY += gravity * deltaTime; // Aplica a gravidade à velocidade vertical
    
    // Limita a velocidade de queda para não ficar muito rápida
    if (currentSpeedY > 1000.0f) {
        currentSpeedY = 1000.0f;
    }
    
    setSpeed(getSpeedX(), currentSpeedY);
    y += currentSpeedY * deltaTime; // Atualiza a posição vertical do pássaro
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
    setSpeed(getSpeedX(), 0.0f); // Reseta a velocidade vertical quando reposiciona
}