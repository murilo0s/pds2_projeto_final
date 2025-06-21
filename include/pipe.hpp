#ifndef PIPE_H
#define PIPE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "bird.hpp" // A gente precisa "conhecer" o Bird pra checar a colisão com ele

class Pipe : public GameObject {
private:
    bool passed; // Flag pra não contar o mesmo ponto duas vezes
    ALLEGRO_BITMAP * pipe_img; // Procurar imagem do cano

public:
    // Construtor -> A função que "cria" o cano, chamada com 'new Pipe()'
    Pipe(float _posicao_x, float _posicao_y, float width, float height, ALLEGRO_BITMAP* _pipe_img);

    // Destrutor -> chamado quando a gente usa 'delete' no cano, pra limpar a memória
    ~Pipe()override;

    // Funções que a gente vai chamar a cada "tick" do jogo no loop principal
    void update(float deltaTime); // 'deltaTime' ajuda a manter o movimento suave
    void draw();                  // Desenha o cano na tela

    // Funções relacionadas a jogabilidade em si
    bool checkCollision(Bird *bird); // Retorna 'true' se o pássaro bateu
    bool isPassed(Bird *bird);       // Retorna 'true' se o pássaro passou pelo cano (pra gente marcar ponto)
};

#endif