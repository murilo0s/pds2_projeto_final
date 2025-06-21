#include "pipe.hpp"
#include "exceptions.hpp"
#include <iostream>

// Algumas constantes pra facilitar a vida e não usar "números mágicos" no código
const float PIPE_SPEED = 180.0f; // Velocidade dos canos em pixels por segundo
const float GAP_HEIGHT = 200.0f; // Tamanho da abertura entre o cano de cima e o de baixo

// O Construtor é chamado quando fazemos: new Pipe(...)
// GameObject::GameObject(float x, float y, float width, float height)
//  : x(x), y(y), width(width), height(height), speedX(0), speedY(0) {}

Pipe::Pipe(float _posicao_x, float _posicao_y, float width, float height, ALLEGRO_BITMAP *_pipe_img) : GameObject(_posicao_x, _posicao_y, width, height),
                                                                                                       passed(false),
                                                                                                       pipe_img(_pipe_img)
{
    this->speedX = PIPE_SPEED;

    // Aqui tentatamos carregar a imagem no cano que tem que ser nomeado de pipe.png
    _pipe_img = al_load_bitmap("pipe.png");
    if (!pipe_img)
    {
        throw erroCarregaPipe;
    }
}

// O Destrutor é chamado quando fazemos: delete pipe;
Pipe::~Pipe()
{
    // Se a imagem do cano foi carregada, temos que destruir ela pra não vazar memória.
    if (pipe_img)
    {
        al_destroy_bitmap(pipe_img);
    }
}

// Atualiza a posição do cano a cada frame
void Pipe::update(float deltaTime)
{
    // Mover pra esquerda. Multiplicar pelo deltaTime faz o jogo rodar igual
    // em computadores rápidos ou lentos.
    posicao_x = posicao_x - speedX * deltaTime;
}

// Desenha o cano na tela
void Pipe::draw()
{
    if (!pipe_img)
        return; // Se a imagem não carregou, não há o que desenhar

    float pipe_width = al_get_bitmap_width(pipe_img);
    float pipe_height = al_get_bitmap_height(pipe_img);

    // --- Desenhar o cano de baixo ---
    // A posição Y dele é o centro do vão MAIS metade da altura do vão
    float lower_pipe_y = posicao_y + (GAP_HEIGHT / 2);
    al_draw_bitmap(pipe_img, posicao_x, lower_pipe_y, 0);

    // --- Desenhar o cano de cima ---
    // Esse é um pouco mais complicado. A gente precisa rotacionar a imagem.
    // Posição Y: centro do vão MENOS metade da altura do vão.
    float upper_pipe_y = posicao_y - (GAP_HEIGHT / 2);
    // Para rotacionar em volta do centro da imagem, precisamos das coordenadas do centro
    float img_center_x = pipe_width / 2;
    float img_center_y = pipe_height / 2;
    // O ângulo de 180 graus em radianos é PI (aprox. 3.14159) PI HAHA
    float angle = 3.14159f;
    // A posição final do cano rotacionado precisa ser ajustada pelo centro da imagem
    al_draw_rotated_bitmap(pipe_img, img_center_x, img_center_y, posicao_x + img_center_x, upper_pipe_y - img_center_y, angle, 0);
}

// A função de colisão!
bool Pipe::checkCollision(Bird *bird)
{
    // Vamos pegar as recem descobertas (por mim) "bounding boxes" (caixas de colisão retangulares) de tudo
    float bird_x = bird->getX();
    float bird_y = bird->getY();
    float bird_w = bird->getWidth();
    float bird_h = bird->getHeight();

    float pipe_w = getWidth();
    float pipe_h = al_get_bitmap_height(pipe_img);

    // Caixa de colisão do cano de baixo
    float lower_pipe_x = posicao_x;
    float lower_pipe_y = posicao_y + (GAP_HEIGHT / 2);

    // Caixa de colisão do cano de cima (aqui o Y é a parte de cima da imagem)
    float upper_pipe_x = posicao_x;
    float upper_pipe_y = posicao_y - (GAP_HEIGHT / 2) - pipe_h;

    // Teste de colisão AABB (Caixa Delimitadora Alinhada aos Eixos)
    // Retorna true se a caixa do pássaro sobrepõe a caixa de QUALQUER um dos canos

    // Colidiu com o cano de baixo?
    bool hit_lower = (bird_x + bird_w > lower_pipe_x && // Lado direito do pássaro > lado esquerdo do cano
                      bird_x < lower_pipe_x + pipe_w && // Lado esquerdo do pássaro < lado direito do cano
                      bird_y + bird_h > lower_pipe_y && // Base do pássaro > topo do cano
                      bird_y < lower_pipe_y + pipe_h);  // Topo do pássaro < base do cano

    // Colidiu com o cano de cima?
    bool hit_upper = (bird_x + bird_w > upper_pipe_x &&
                      bird_x < upper_pipe_x + pipe_w &&
                      bird_y < upper_pipe_y + pipe_h && // Topo do pássaro < base do cano
                      bird_y + bird_h > upper_pipe_y);  // Base do pássaro > topo do cano

    return hit_lower || hit_upper;
}

// Verifica se o pássaro passou pra marcar ponto
bool Pipe::isPassed(Bird *bird)
{
    // Se a flag 'passed' já é true, a gente já pontuou, então retorna false.
    if (passed)
    {
        return false;
    }

    // O ponto é marcado quando a frente do pássaro passa as costas do cano
    if (bird->getX() > posicao_x + getWidth())
    {
        passed = true; // Marca como passado pra não pontuar de novo
        return true;   // Retorna true SÓ na primeira vez que passa
    }

    return false;
}