#include "GameObject.hpp"

// Construtor: inicializa posição, dimensões e velocidade (velocidade começa em 0)
GameObject::GameObject(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speedX(0), speedY(0) {}

// Verifica se o objeto saiu da tela (padrão: tela 800x600)
// Retorna true se qualquer parte do objeto estiver fora dos limites da tela
bool GameObject::isOffScreen() {
    return (x < 0 || x + width > 800 || y < 0 || y + height > 600);
}

// Define nova posição para o objeto, alterando os valores de x e y
void GameObject::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

// Define nova velocidade para o objeto, alterando os valores de speedX e speedY
void GameObject::setSpeed(float newSpeedX, float newSpeedY) {
    speedX = newSpeedX;
    speedY = newSpeedY;
}
