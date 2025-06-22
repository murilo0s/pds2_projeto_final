#include "pipe.hpp"
#include <iostream>
#include <stdexcept>

// Constantes para os canos
const float PIPE_SPEED = 180.0f; // define velocidade de movimento dos canos
const float GAP_HEIGHT = 200.0f; // define o tamanho do vão entre os canos

// chama o construtor de gameObject com os valores zerados pois não sabemos as dimensões do cano
Pipe::Pipe(float startX, float gapCenterY) : GameObject(0, 0, 0, 0) {
    // Tenta carregar a imagem do cano do arquivo "pipe.png".
    pipe_img = al_load_bitmap("pipe.png");
    
    // Verifica se a imagem foi carregada
    if(!pipe_img) {
	// carrega uma msg de erro
	throw std::runtime_error("Não foi possível carregar a imagem do cano");
    }
    // se a imagem carregou, o codigo continua normalmente e carrega as dimensões da imagem
    this->width = al_get_bitmap_width(pipe_img);
    this->height = al_get_bitmap_height(pipe_img);

    // Agora inicializa o resto das variáveis
    this->x = startX;
    this->gapY = gapCenterY;
    this->passed = false;
    this->setSpeed(PIPE_SPEED, 0); // Define a velocidade de movimento horizontal
}

Pipe::~Pipe() {
    // Libera a memória da imagem se ela foi carregada
    if (pipe_img) {
        al_destroy_bitmap(pipe_img);
    }
}

void Pipe::update(float deltaTime) {
    // Move o cano para a esquerda usando a velocidade definida no GameObject
    this->x -= this->speedX * deltaTime;
}

void Pipe::render() {
    if (!pipe_img) return;

    // Cano de baixo
    float lower_pipe_y = gapY + (GAP_HEIGHT / 2);
    al_draw_bitmap(pipe_img, this->x, lower_pipe_y, 0);

    // Cano de cima (rotacionado)
    float upper_pipe_y = gapY - (GAP_HEIGHT / 2);
    al_draw_rotated_bitmap(pipe_img, this->width / 2, this->height / 2, this->x + this->width / 2, upper_pipe_y - this->height / 2, 3.14159f, 0); // quero mudar essa parte aqui (quero usar duas imagens, não rotacionar)
}

// verifica se o cano colidiu com o objeto
bool Pipe::checkCollision(const GameObject& other) {
    // assume que other é sempre bird pq a logica de colisão é controlada por Game
    const Bird* bird = static_cast<const Bird*>(&other);

    // pega as dimensões do pássaro
    float bird_x = bird->getX();
    float bird_y = bird->getY();
    float bird_w = bird->getWidth();
    float bird_h = bird->getHeight();

    // pega as dimensões do cano de baixo
    float lower_pipe_x = this->x;
    float lower_pipe_y = gapY + (GAP_HEIGHT / 2);
    
    // pega as dimensões do cano de cima
    float upper_pipe_x = this->x;
    float upper_pipe_y = gapY - (GAP_HEIGHT / 2) - this->height;

    bool hit_lower = (bird_x + bird_w > lower_pipe_x && bird_x < lower_pipe_x + this->width &&
                      bird_y + bird_h > lower_pipe_y && bird_y < lower_pipe_y + this->height);

    bool hit_upper = (bird_x + bird_w > upper_pipe_x && bird_x < upper_pipe_x + this->width &&
                      bird_y < upper_pipe_y + this->height && bird_y + bird_h > upper_pipe_y);

    return hit_lower || hit_upper;
}

// verifica se o cano foi passado pelo pássaro
bool Pipe::isPassed(const Bird& bird) {
    if (passed) {
        return false;
    }
    // O ponto é marcado quando a frente do pássaro passa pelo final do cano
    if (bird.getX() > this->x + this->width) {
        passed = true;
        return true;
    }
    return false;
}

// retorna a posição x do cano
float Pipe::getX() const {
    return x;
}

// retorna a largura do cano
float Pipe::getWidth() const {
    if (pipe_img) {
        return al_get_bitmap_width(pipe_img);
    }
    return 0; // Se não tiver imagem, largura é 0
}
