#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <allegro5/allegro.h>

// Classe base para todos os objetos do jogo
class GameObject {
protected:
    float x, y; // Posição do objeto no espaço (coordenadas)
    float width, height; // Dimensões do objeto (largura e altura)
    float speedX, speedY; // Velocidade do objeto nos eixos X e Y

public:
    // Construtor: inicializa posição e dimensões do objeto
    GameObject(float x, float y, float width, float height);

    // Destrutor virtual padrão (permite herança segura)
    virtual ~GameObject() = default;

    // Métodos virtuais puros (devem ser implementados pelas classes derivadas)
    virtual void update(float deltaTime) = 0; // Atualiza o estado do objeto
    virtual void render() = 0; // Desenha o objeto na tela
    virtual bool checkCollision(const GameObject& other) = 0; // Verifica colisão com outro objeto

    // Métodos de implementação (podem ser sobrescritos)
    virtual bool isOffScreen(); // Verifica se o objeto saiu da tela
    virtual void move() { // Move o objeto de acordo com sua velocidade
        x += speedX;
        y += speedY;
    }

    // Getters (acessam atributos privados/protegidos)
    float getX() const { return x; } // Retorna posição X
    float getY() const { return y; } // Retorna posição Y
    float getWidth() const { return width; } // Retorna largura
    float getHeight() const { return height; } // Retorna altura
    float getSpeedX() const { return speedX; } // Retorna velocidade X
    float getSpeedY() const { return speedY; } // Retorna velocidade Y

    // Setters (modificam atributos)
    void setPosition(float newX, float newY); // Define nova posição
    void setSpeed(float newSpeedX, float newSpeedY); // Define nova velocidade

};

#endif