#include "game_renderer.hpp"
#include "game.hpp"
#include "PlayerManager.hpp"
#include "Player.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <iostream>
#include <algorithm>

GameRenderer::GameRenderer(ALLEGRO_FONT* font) : font(font), background_img(nullptr), ground_img(nullptr) {
    // Carrega a imagem de background
    background_img = al_load_bitmap("assets/background/forest2_background.png");
    if (!background_img) {
        std::cerr << "Erro ao carregar imagem de background!" << std::endl;
    }
    // Carrega a imagem do chão
    ground_img = al_load_bitmap("assets/ground.png");
    if (!ground_img) {
        std::cerr << "Erro ao carregar imagem do chão!" << std::endl;
    }
}

GameRenderer::~GameRenderer() {
    if (background_img) {
        al_destroy_bitmap(background_img);
    }
    if (ground_img) {
        al_destroy_bitmap(ground_img);
    }
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
    
    centerText("Pressione ESPACO para jogar novamente", game.getScreenHeight() * 4 / 5 - 30);
    centerText("Pressione M para voltar ao menu de jogadores", game.getScreenHeight() * 4 / 5 + 10);
    
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
    if (background_img) {
        // Desenha a imagem de background
        al_draw_bitmap(background_img, 0, 0, 0);
    } else {
        // Fallback para cor sólida se a imagem não carregou
        al_clear_to_color(al_map_rgb(135, 206, 235)); // Azul claro
    }
    // Renderiza o chão
    if (ground_img) {
        al_draw_bitmap(ground_img, 0, 600 - 100, 0);
    } else {
        al_draw_filled_rectangle(0, 600 - 100, 800, 600, al_map_rgb(34, 139, 34));
    }
}

void GameRenderer::renderUI(const Game& game) {
    // Renderiza elementos da interface do usuário
    renderScore(game);
}

void GameRenderer::centerText(const char* text, float y) {
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                400, y, ALLEGRO_ALIGN_CENTER, text);
} 

void GameRenderer::renderSelecaoJogador(const Game& game) {
    al_clear_to_color(al_map_rgb(40, 40, 80));
    al_draw_text(font, al_map_rgb(255,255,255), game.getScreenWidth()/2, 60, ALLEGRO_ALIGN_CENTER, "SELECIONE UM JOGADOR");

    const auto& jogadores = game.getPlayerManager()->getJogadores();
    int y = 140;
    int x = game.getScreenWidth()/2;

    if (jogadores.empty()) {
        al_draw_text(font, al_map_rgb(255,80,80), x, y, ALLEGRO_ALIGN_CENTER, "Nenhum jogador cadastrado!");
    } else {
        for (size_t i = 0; i < jogadores.size(); ++i) {
            std::string info = std::to_string(i+1) + ". " + jogadores[i].getNome() + " (" + jogadores[i].getApelido() + ")";
            al_draw_text(font, al_map_rgb(255,255,255), x, y + 30 * i, ALLEGRO_ALIGN_CENTER, info.c_str());
        }
        al_draw_text(font, al_map_rgb(200,200,200), x, y + 30 * jogadores.size() + 30, ALLEGRO_ALIGN_CENTER, "Digite o número do jogador e pressione ENTER");
    }
    al_draw_text(font, al_map_rgb(200,200,200), x, game.getScreenHeight() - 60, ALLEGRO_ALIGN_CENTER, "ESC: Voltar ao menu");
}

void GameRenderer::renderRanking(const Game& game) {
    al_clear_to_color(al_map_rgb(40, 40, 80));
    al_draw_text(font, al_map_rgb(255,255,255), game.getScreenWidth()/2, 60, ALLEGRO_ALIGN_CENTER, "RANKING DE JOGADORES");

    // Ordena por pontuação máxima (se ainda não estiver ordenado)
    std::vector<Player> jogadores = game.getPlayerManager()->getJogadores();
    std::sort(jogadores.begin(), jogadores.end(), [](const Player& a, const Player& b) {
        return a.getPonto_max() > b.getPonto_max();
    });

    int y = 140;
    int x = game.getScreenWidth()/2;

    if (jogadores.empty()) {
        al_draw_text(font, al_map_rgb(255,80,80), x, y, ALLEGRO_ALIGN_CENTER, "Nenhum jogador cadastrado!");
    } else {
        for (size_t i = 0; i < jogadores.size(); ++i) {
            std::string info = std::to_string(i+1) + ". " + jogadores[i].getNome() + " (" + jogadores[i].getApelido() + ") - "
                + std::to_string(jogadores[i].getPonto_max()) + " pts, " + std::to_string(jogadores[i].getTotal_partidas()) + " jogos";
            al_draw_text(font, al_map_rgb(255,255,255), x, y + 30 * i, ALLEGRO_ALIGN_CENTER, info.c_str());
        }
    }
    al_draw_text(font, al_map_rgb(200,200,200), x, game.getScreenHeight() - 60, ALLEGRO_ALIGN_CENTER, "ESC: Voltar ao menu");
}

void GameRenderer::renderPlayerMenu(const Game& game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255,255,0), 400, 50, ALLEGRO_ALIGN_CENTRE, "MENU DE JOGADORES");
    int y = 120;
    int idx = 1;
    for (const auto& jogador : game.getPlayerManager()->getJogadores()) {
        al_draw_textf(font, al_map_rgb(255,255,255), 400, y, ALLEGRO_ALIGN_CENTRE,
            "%d. %s (%s) - Pontos: %d, Partidas: %d",
            idx++, jogador.getNome().c_str(), jogador.getApelido().c_str(),
            jogador.getPonto_max(), jogador.getTotal_partidas());
        y += 30;
    }
    al_draw_text(font, al_map_rgb(0,255,0), 400, y+30, ALLEGRO_ALIGN_CENTRE, "N - Novo jogador");
    al_draw_text(font, al_map_rgb(0,255,0), 400, y+60, ALLEGRO_ALIGN_CENTRE, "1-9 - Selecionar jogador");
    al_draw_text(font, al_map_rgb(255,0,0), 400, y+90, ALLEGRO_ALIGN_CENTRE, "ESC - Sair");
    al_flip_display();
}

void GameRenderer::renderCadastroJogador(const Game& game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255,255,0), 400, 50, ALLEGRO_ALIGN_CENTRE, "CADASTRO DE JOGADOR");
    al_draw_textf(font, al_map_rgb(255,255,255), 400, 150, ALLEGRO_ALIGN_CENTRE, "Nome: %s%s", 
        game.inputNome.c_str(), (game.campoPreenchido == 0 ? "_" : ""));
    al_draw_textf(font, al_map_rgb(255,255,255), 400, 200, ALLEGRO_ALIGN_CENTRE, "Apelido: %s%s", 
        game.inputApelido.c_str(), (game.campoPreenchido == 1 ? "_" : ""));
    al_draw_text(font, al_map_rgb(0,255,0), 400, 300, ALLEGRO_ALIGN_CENTRE, "ENTER para confirmar, TAB para alternar campo, ESC para cancelar");
    al_flip_display();
}
