#include "bird.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <allegro5/allegro_image.h>

const float GRAVITY = -0.5f;
const float JUMPSTRENGHT = 10.0f; 
const float BIRDWIDTH = 0; //mudar quando tivermos o passaro
const float BIRDHEIGHT = 0; //mudar quando tivermos o passaro

Bird::Bird(float _posicao_x, float _posicao_y, ALLEGRO_BITMAP * _bird_img) : 
GameObject(_posicao_x, _posicao_y, BIRDWIDTH, BIRDHEIGHT),
bird_img(_bird_img)
{
    this->width = BIRDWIDTH;
    this->height = BIRDHEIGHT;
    this->gravity = GRAVITY;
    this->jumpStrength = JUMPSTRENGHT;

    // Carrega a imagem do pássaro
    bird_img = al_load_bitmap("assets/bird.png");
    if (!bird_img) {
       throw erroCarregaBird;
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
    posicao_y += speedY; // Atualiza a posição vertical do pássaro
}

void Bird::render() {
    if (bird_img) {
        al_draw_bitmap(bird_img, posicao_x, posicao_y, 0); // Desenha o pássaro na tela
    }
}

bool Bird::isColliding(const GameObject& other) {
    /*Esta implementação de colisão é genérica. A lógica de verificação
    será feita na classe Game, que tem acesso ao pássaro e aos canos.
    O método GameObject::isColliding pode ser usado para isso.*/
    return GameObject::isColliding(other);
}
