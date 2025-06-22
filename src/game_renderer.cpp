#include "game_renderer.hpp"
#include "game.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>

GameRenderer::GameRenderer(ALLEGRO_FONT* font) : font(font) {
}

GameRenderer::~GameRenderer() {
}

void GameRenderer::renderMenu(const Game& game) {
    al_clear_to_color(al_map_rgb(135, 206, 235)); // Cor de fundo azul claro
    
    // Título do jogo
    centerText("FLAPPY BIRD", game.getScreenHeight() / 3);
    
    // Instruções
    centerText("Pressione ESPACO para comecar", game.getScreenHeight() / 2);
    centerText("Pressione ESC para sair", game.getScreenHeight() * 2 / 3);
    
    al_flip_display();
}

void GameRenderer::renderPlaying(const Game& game) {
    al_clear_to_color(al_map_rgb(135, 206, 235)); // Cor de fundo azul claro
    
    // Renderiza o fundo
    renderBackground();
    
    // Renderiza o pássaro
    if (game.getBird()) {
        game.getBird()->render();
    }
    
    // Renderiza os pipes
    for (size_t i = 0; i < game.getPipes().size(); i++) {
        game.getPipes()[i]->render();
    }
    
    // Renderiza a pontuação
    renderScore(game);
    
    al_flip_display();
}

void GameRenderer::renderGameOver(const Game& game) {
    al_clear_to_color(al_map_rgb(135, 206, 235));
    
    centerText("GAME OVER", game.getScreenHeight() / 3);
    
    char scoreText[50];
    sprintf(scoreText, "Pontuacao: %d", game.getScore());
    centerText(scoreText, game.getScreenHeight() / 2);
    
    char highScoreText[50];
    sprintf(highScoreText, "Melhor Pontuacao: %d", game.getHighScore());
    centerText(highScoreText, game.getScreenHeight() * 2 / 3);
    
    centerText("Pressione ESPACO para jogar novamente", game.getScreenHeight() * 4 / 5);
    
    al_flip_display();
}

void GameRenderer::renderPaused(const Game& game) {
    // Renderiza o jogo em pausa
    renderPlaying(game);
    
    // Overlay de pausa
    al_draw_filled_rectangle(0, 0, game.getScreenWidth(), game.getScreenHeight(), 
                           al_map_rgba(0, 0, 0, 128));
    
    centerText("PAUSADO", game.getScreenHeight() / 2);
    centerText("Pressione P para continuar", game.getScreenHeight() * 2 / 3);
    
    al_flip_display();
}

void GameRenderer::renderScore(const Game& game) {
    char scoreText[20];
    sprintf(scoreText, "%d", game.getScore());
    
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                400, 50, ALLEGRO_ALIGN_CENTER, scoreText);
}

void GameRenderer::renderBackground() {
    // Renderiza um fundo simples
    al_draw_filled_rectangle(0, 600 - 100, 800, 600, 
                           al_map_rgb(34, 139, 34)); // Verde para o chão
}

void GameRenderer::renderUI(const Game& game) {
    // Renderiza elementos da interface do usuário
    renderScore(game);
}

void GameRenderer::centerText(const char* text, float y) {
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                400, y, ALLEGRO_ALIGN_CENTER, text);
} 