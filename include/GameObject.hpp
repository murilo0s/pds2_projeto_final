#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <allegro5/allegro.h>

/**
 * @brief Classe base para todos os objetos do jogo
 * 
 */
class GameObject {
protected:
    float x, y; ///< Posição do objeto no espaço (coordenadas)
    float width, height; ///< Dimensões do objeto (largura e altura)
    float speedX, speedY; ///< Velocidade do objeto nos eixos X e Y

public:
    /**
     * @brief Construtor que inicializa a posição e as dimensões do objeto
     * 
     * @param x Eixo x da posição
     * @param y Eixo y da posição
     * @param width Largura
     * @param height Altura
     */
    GameObject(float x, float y, float width, float height);

    // Destrutor virtual padrão (permite herança segura)
    virtual ~GameObject() = default;

    // Métodos virtuais puros (devem ser implementados pelas classes derivadas)
    /**
     * @brief Atualiza o estado do objeto
     * 
     * @param deltaTime Referencia o tempo percorrido entre um frame e outro 
     */
    virtual void update(float deltaTime) = 0; 
    /**
     * @brief Desenha o objeto na tela
     */
    virtual void render() = 0;
    /**
     * @brief Verifica colisão com outro objeto
     * 
     * @param other Referencia o objeto other
     * @return true 
     * @return false 
     */
    virtual bool checkCollision(const GameObject& other) = 0;

    // Métodos de implementação (podem ser sobrescritos)
    /**
     * @brief Verifica se o objeto saiu da tela
     * 
     * @return true 
     * @return false 
     */
    virtual bool isOffScreen(); 
    /**
     * @brief Move o objeto de acordo com sua velocidade
     * 
     */
    virtual void move() { 
        x += speedX;
        y += speedY;
    }

    // Getters (acessam atributos privados/protegidos)
    /**
     * @brief Retorna a posição do eixo x do objeto
     */
    float getX() const { return x; }
    /**
     * @brief Retorna a posição do eixo y do objeto 
     */
    float getY() const { return y; } 
    /**
     * @brief Retorna a largura do objeto
     */
    float getWidth() const { return width; } 
    /**
     * @brief Retorna a altura do objeto
     */
    float getHeight() const { return height; } 
    /**
     * @brief Retorna a velocidade do objeto no eixo x
     */
    float getSpeedX() const { return speedX; } 
    /** 
     * @brief Retorna a velocidade do objeto no eixo y
     */
    float getSpeedY() const { return speedY; } 

    // Setters (modificam atributos)
    /**
     * @brief Define nova posição do objeto
     * 
     * @param newX novo eixo x
     * @param newY novo eixo y
     */
    void setPosition(float newX, float newY); 
    /**
     * @brief Define a nova velocidade do objeto
     * 
     * @param newSpeedX nova velocidade no eixo x
     * @param newSpeedY nova velocidade no eixo y
     */
    void setSpeed(float newSpeedX, float newSpeedY); 
};

#endif