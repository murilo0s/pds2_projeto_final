#ifndef PIPE_H
#define PIPE_H

#include "GameObject.hpp"
#include "bird.hpp"

// A classe Pipe herda metodos da classe GameObject
/**
 * @brief Classe que representa os canos que serão usados como obstáculo para o pássaro.
 * 
 * O cano é desenhado na tela e se move da direita para a esquerda.
 * Também detecta colisões com o pássaro e informa se o pássaro já passou.
 */
class Pipe : public GameObject {
public:
    // construtor e destrutor
    /**
     * @brief Construtor da classe Pipe.
     * 
     * @param startX Posição X inicial do cano.
     * @param gapCenterY Posição Y central do buraco entre os canos.
     */
    Pipe(float startX, float gapCenterY);
    /**
     * @brief Destrutor da classe Pipe.
     * 
     * Libera a memória alocada para a imagem do cano.
     */
    ~Pipe();
    
    /**
     * @brief Atualiza a posição do cano conforme o tempo vai passando
     * 
     * @param deltaTime Tempo percorrido desde a última atualização (em segundos).
     * 
     */ 
    void update() override;
    /**
     * @brief Desenha o cano na tela.
     */
    void draw() override;
    /**
     * @brief Verifica se o cano colidiu com o objeto 
     * 
     * @param other verifica qual é o objeto que colidiu com o cano.
     * @return true se o cano colidiu com o objeto.
     * @return false se o cano não colidiu com o objeto.
     */
    bool isColliding(const GameObject& other) override;

    /**
     * @brief Verifica se o pássaro já passou pelo cano.
     * usa a variavel passed para saber se o pássaro já passou pelo cano.
     * 
     * @param bird verifica se o pássaro já passou pelo cano.
     * @return true se o pássaro já passou pelo cano.
     * @return false se o pássaro não passou pelo cano.
     */
    bool isPassed(const Bird& bird);

private:
    
    float gapY;       ///< essa variavel armazena o espaço (onde o passaro passa) entre os canos de cima e de baixo 
    bool passed;      ///< garante que o jogador ganhe pontos por passar do cano apenas uma vez
    ALLEGRO_BITMAP* pipe_img; ///< ponteiro que guarda o endereço da imagem do cano
};

#endif
