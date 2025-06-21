#pragma once

#include "GameObject.hpp"
#include <allegro5/allegro.h>

class Bird : public GameObject {
private:
    //float speedY; // Velocidade vertical do pássaro
    float gravity; // Força da gravidade aplicada ao pássaro
    float jumpStrength; // Força do pulo do pássaro

    // carrega a imagem do pássaro
    ALLEGRO_BITMAP *bird_img; // Imagem do pássaro
    //int width, height; // Dimensões da imagem do pássaro

public:
    // construtor (inicializa o passaro com uma posição inicial)
    Bird(float _posicao_x, float _posicao_y, ALLEGRO_BITMAP * _bird_img);

    // destrutor
    ~Bird() override;

    // faz o passaro pular
    void jump();

    // metodos herdados de GameObject
    void update() override; // Atualiza a posição do pássaro com base na velocidade
    void render(); // Desenha o pássaro na tela
    bool isColliding(const GameObject& other) override; // Verifica colisão com outro objeto

};