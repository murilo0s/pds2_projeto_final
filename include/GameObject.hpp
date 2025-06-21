#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <allegro5/allegro.h>

// Classe base para todos os objetos do jogo
class GameObject {
protected:
    float posicao_x, posicao_y; // Posição do objeto no espaço (coordenadas)
    float width, height; // Dimensões do objeto (largura e altura)
    float speedX, speedY; // Velocidade do objeto nos eixos X e Y

public:
    // Construtor: inicializa posição e dimensões do objeto
    GameObject(float x, float y, float width, float height);

    // Destrutor virtual padrão (permite herança segura)
    virtual ~GameObject() = default;

    // Métodos virtuais puros (devem ser implementados pelas classes derivadas)
    virtual void update() = 0; // Atualiza o estado do objeto
    virtual void draw() = 0; // Desenha o objeto na tela
    virtual bool isColliding(const GameObject& other) = 0; // Verifica colisão com outro objeto

    // Métodos de implementação (podem ser sobrescritos)
    virtual bool isOffScreen(); // Verifica se o objeto saiu da tela
    virtual void move(); // Move o objeto de acordo com sua velocidade

    // Getters (acessam atributos privados/protegidos)
    float getX(); // Retorna posição X
    float getY(); // Retorna posição Y
    float getWidth(); // Retorna largura
    float getHeight(); // Retorna altura
    float getSpeedX(); // Retorna velocidade X
    float getSpeedY(); // Retorna velocidade Y

    // Setters (modificam atributos)
    void setPosition(float newX, float newY); // Define nova posição
    void setSpeed(float newSpeedX, float newSpeedY); // Define nova velocidade

};

#endif