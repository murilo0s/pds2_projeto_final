#include "pipe.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <stdexcept>

// Constantes para os canos
const float PIPE_SPEED = 180.0f; // define velocidade de movimento dos canos
const float GAP_HEIGHT = 200.0f; // define o tamanho do vão entre os canos

<<<<<<< HEAD
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
=======
// chama o construtor de gameObject com os valores zerados pois não sabemos as dimensões do cano
Pipe::Pipe(float startX, float gapCenterY) : GameObject(0, 0, 0, 0) {
    // Tenta carregar a imagem do cano do arquivo "pipe.png".
    pipe_img = al_load_bitmap("pipe.png");
    
    // Verifica se a imagem foi carregada
    if(!pipe.img) {
	// carrega uma msg de erro
	throw std::runtime_error("Não foi possível carregar a imagem do cano");
>>>>>>> fd1661439e36e26bc89fb1ad0b1137b93240710d
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

<<<<<<< HEAD
// O Destrutor é chamado quando fazemos: delete pipe;
Pipe::~Pipe()
{
    // Se a imagem do cano foi carregada, temos que destruir ela pra não vazar memória.
    if (pipe_img)
    {
=======
Pipe::~Pipe() {
    // Libera a memória da imagem se ela foi carregada
    if (pipe_img) {
>>>>>>> fd1661439e36e26bc89fb1ad0b1137b93240710d
        al_destroy_bitmap(pipe_img);
    }
}

<<<<<<< HEAD
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
=======
void Pipe::update() {
    // Move o cano para a esquerda usando a velocidade definida no GameObject
    this->x -= this->speedX;
}

void Pipe::draw() {
    if (!pipe_img) return;

    // Cano de baixo
    float lower_pipe_y = gapY + (GAP_HEIGHT / 2);
    al_draw_bitmap(pipe_img, this->x, lower_pipe_y, 0);

    // Cano de cima (rotacionado)
    float upper_pipe_y = gapY - (GAP_HEIGHT / 2);
    al_draw_rotated_bitmap(pipe_img, this->width / 2, this->height / 2, this->x + this->width / 2, upper_pipe_y - this->height / 2, 3.14159f, 0); // quero mudar essa parte aqui (quero usar duas imagens, não rotacionar)
}

// verifica se o cano colidiu com o objeto
bool Pipe::isColliding(const GameObject& other) {
    // assume que other é sempre bird pq a logica de colisão é controlada por Game
    const Bird* bird = static_cast<const Bird*>(&other);

    // pega as dimensões do pássaro
>>>>>>> fd1661439e36e26bc89fb1ad0b1137b93240710d
    float bird_x = bird->getX();
    float bird_y = bird->getY();
    float bird_w = bird->getWidth();
    float bird_h = bird->getHeight();

<<<<<<< HEAD
    float pipe_w = getWidth();
    float pipe_h = al_get_bitmap_height(pipe_img);

    // Caixa de colisão do cano de baixo
    float lower_pipe_x = posicao_x;
    float lower_pipe_y = posicao_y + (GAP_HEIGHT / 2);

    // Caixa de colisão do cano de cima (aqui o Y é a parte de cima da imagem)
    float upper_pipe_x = posicao_x;
    float upper_pipe_y = posicao_y - (GAP_HEIGHT / 2) - pipe_h;
=======
    // pega as dimensões do cano de baixo
    float lower_pipe_x = this->x;
    float lower_pipe_y = gapY + (GAP_HEIGHT / 2);
    
    // pega as dimensões do cano de cima
    float upper_pipe_x = this->x;
    float upper_pipe_y = gapY - (GAP_HEIGHT / 2) - this->height;

    bool hit_lower = (bird_x + bird_w > lower_pipe_x && bird_x < lower_pipe_x + this->width &&
                      bird_y + bird_h > lower_pipe_y && bird_y < lower_pipe_y + this->height);
>>>>>>> fd1661439e36e26bc89fb1ad0b1137b93240710d

    bool hit_upper = (bird_x + bird_w > upper_pipe_x && bird_x < upper_pipe_x + this->width &&
                      bird_y < upper_pipe_y + this->height && bird_y + bird_h > upper_pipe_y);

    return hit_lower || hit_upper;
}

<<<<<<< HEAD
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
=======
// verifica se o cano foi passado pelo pássaro
bool Pipe::isPassed(const Bird& bird) {
    if (passed) {
        return false;
    }
    // O ponto é marcado quando a frente do pássaro passa pelo final do cano
    if (bird.getX() > this->x + this->width) {
        passed = true;
        return true;
>>>>>>> fd1661439e36e26bc89fb1ad0b1137b93240710d
    }
    return false;
<<<<<<< HEAD
=======
}

// retorna a posição x do cano
float Pipe::getX() {
    return x;
}

// retorna a largura do cano
float Pipe::getWidth() {
    if (pipe_img) {
        return al_get_bitmap_width(pipe_img);
    }
    return 0; // Se não tiver imagem, largura é 0
>>>>>>> fd1661439e36e26bc89fb1ad0b1137b93240710d
}