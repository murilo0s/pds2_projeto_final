#include "GameObject.hpp"

// Construtor: inicializa posição, dimensões e velocidade (velocidade começa em 0)
GameObject::GameObject(float posicao_x, float posicao_y, float width, float height)
    : posicao_x(posicao_x), posicao_y(posicao_y), width(width), height(height), speedX(0), speedY(0) {}

// Verifica se o objeto saiu da tela (padrão: tela 800x600)
// Retorna true se qualquer parte do objeto estiver fora dos limites da tela
bool GameObject::isOffScreen()
{
   return  posicao_x < 0 || posicao_x + width > 800 || posicao_y < 0 || posicao_y + height > 600;
}

void GameObject::move()
{
    posicao_x += speedX;
    posicao_y += speedY;
}

float GameObject::getX()
{
    return posicao_x;
}

float GameObject::getY()
{
    return posicao_y;
}

float GameObject::getWidth()
{
    return width;
}

float GameObject::getHeight()
{
    return height;
}

float GameObject::getSpeedX()
{
    return speedX;
}

float GameObject::getSpeedY()
{
    return speedY;
}

// Define nova posição para o objeto, alterando os valores de x e y
void GameObject::setPosition(float newX, float newY)
{
    posicao_x = newX;
    posicao_y = newY;
}

// Define nova velocidade para o objeto, alterando os valores de speedX e speedY
void GameObject::setSpeed(float newSpeedX, float newSpeedY)
{
    speedX = newSpeedX;
    speedY = newSpeedY;
}
