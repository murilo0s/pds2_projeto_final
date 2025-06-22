#pragma once

#include "GameObject.hpp"
#include <allegro5/allegro.h>

class Bird : public GameObject {
private:
    float speedY; ///< Velocidade vertical do pássaro
    float gravity; ///< Força da gravidade aplicada ao pássaro
    float jumpStrength; ///< Força do pulo do pássaro

    ALLEGRO_BITMAP *bird_img; ///< ponteiro que guarda o endereço da imagem do pássaro

public:
    /**
     * @brief Construtor da classe Bird.
     * 
     * @param startX Posição X inicial do pássaro.
     * @param startY Posição Y inicial do pássaro.
     */
    Bird(float startX, float startY);

    /**
     * @brief Destrutor da classe Bird.
     * 
     * Libera a memória alocada para a imagem do pássaro.
     */
    ~Bird() override;

    /**
     * @brief Faz o pássaro pular.
     * 
     * Aumenta a velocidade vertical do pássaro para fazê-lo subir.
     */
    void jump();

    /**
     * @brief Atualiza a posição do pássaro.
     * 
     * Atualiza a posição do pássaro com base na velocidade e na gravidade.
     * 
     * @param deltaTime Tempo percorrido desde a última atualização (em segundos).
     */
    void update(float deltaTime) override; // Atualiza a posição do pássaro com base na velocidade

    /**
     * @brief Desenha o pássaro na tela.
     */
    void render() override; // Desenha o pássaro na tela

    /**
     * @brief Retorna a largura da imagem do pássaro.
     */
    int getWidth() const;

    /**
     * @brief Retorna a altura da imagem do pássaro.
     */
    int getHeight() const;

    /**
     * @brief Define a posição do pássaro.
     * 
     * @param newX Nova posição X do pássaro.
     * @param newY Nova posição Y do pássaro.
     */
    void setPosition(float newX, float newY);

    /**
     * @brief Verifica colisão com outro objeto.
     * 
     * @param other Objeto com o qual verificar colisão.
     * @return true se há colisão, false caso contrário.
     */
    bool checkCollision(const GameObject& other) override;

};