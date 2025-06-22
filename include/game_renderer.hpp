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
    ALLEGRO_FONT* font; // Fonte para escrever textos

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

    // Desenha as telas do jogo
    void renderMenu(const Game& game);      // Desenha o menu
    void renderPlaying(const Game& game);   // Desenha o jogo
    void renderGameOver(const Game& game);  // Desenha game over
    void renderPaused(const Game& game);    // Desenha tela de pausa

    // Desenha elementos específicos
    void renderScore(const Game& game);     // Desenha a pontuação
    void renderBackground();                // Desenha o fundo
    void renderUI(const Game& game);        // Desenha a interface
    void centerText(const char* text, float y); // Centraliza texto
};

#endif 