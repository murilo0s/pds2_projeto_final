#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "bird.hpp"
#include "pipe.hpp"
#include "game.hpp"

// Forward declarations
class Game;

/**
 * @brief Classe que desenha tudo na tela
 *
 * Esta classe desenha:
 * - Menu, jogo e tela de game over
 * - Pontuação e textos
 * - Fundo do jogo
 */
class GameRenderer {
private:
    ALLEGRO_FONT* font; ///< Fonte para escrever textos
    ALLEGRO_BITMAP* background_img; ///< Imagem de fundo do jogo
    ALLEGRO_BITMAP* ground_img; ///< Imagem do chão
    ALLEGRO_BITMAP* gameover_bg_img; ///< Imagem de fundo para Game Over

public:
    /**
     * @brief Construtor da classe GameRenderer
     * 
     * Recebe a fonte que será usada para renderizar
     * todos os textos do jogo.
     * 
     * @param font Ponteiro para a fonte do Allegro
     */
    GameRenderer(ALLEGRO_FONT* font);

    /**
     * @brief Destrutor da classe GameRenderer
     */
    ~GameRenderer();

    /**
     * @brief Desenha o menu do jogo
     * 
     * @param game Referencia o objeto game
     */
    void renderMenu(const Game& game);    
    /**
     * @brief Desenha o jogo propriamente dito
     * 
     * @param game Referencia o objeto game
     */
    void renderPlaying(const Game& game);   
    /**
     * @brief Desenha a tela de game over
     * 
     * @param game Referencia o objeto game
     */
    void renderGameOver(const Game& game); 
    /**
     * @brief Desenha a tela de pause do jogo
     * 
     * @param game Referencia o objeto game
     */
    void renderPaused(const Game& game);    

    /**
     * @brief Desenha a pontuação do jogador
     * 
     * @param game Referencia o objeto game
     */
    void renderScore(const Game& game);
    /**
     * @brief Desenha a tela de fundo do jogo
     * 
     */
    void renderBackground();                
    /**
     * @brief Desenha a interface gráfica do jogo
     * 
     * @param game Referencia o objeto game
     */
    void renderUI(const Game& game);        
    /**
     * @brief Centralização do texto
     * 
     * @param text Referencia o texto
     * @param y 
     */
    void centerText(const char* text, float y); 
    /**
     * @brief Desenha a tela de cadastro de jogadores
     * 
     * @param game Referencia o objeto game
     */
    void renderCadastro(const Game& game); 
    /**
     * @brief Desenha a caixa de entrada de texto para cadastro de jogadores
     * 
     * @param value Referencia o valor de entrada
     * @param x Referencia a posição x
     * @param y Referencia a posição y
     * @param active 
     */
    void renderAreaDeInput(const std::string& value, int x, int y, bool active); 
    /**
     * @brief Desenha a tela de seleção de jogadores
     * 
     * @param game Referencia o objeto game
     */
    void renderSelecaoJogador(const Game& game); // Desenha a tela de seleção de jogador
    /**
     * @brief Desenha a tela de ranking dos jogadores com base nas pontuações prévias
     * 
     * @param game Referencia o objeto game
     */
    void renderRanking(const Game& game);
    /**
     * @brief Desenha o menu de jogadores
     * 
     * @param game Referencia o objeto game 
     */
    void renderPlayerMenu(const Game& game);
    /**
     * @brief Desenha a tela de cadastro dos jogadores
     * 
     * @param game Referencia o objeto game
     */
    void renderCadastroJogador(const Game& game);
};

#endif 