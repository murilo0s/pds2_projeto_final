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

GameRenderer::GameRenderer(ALLEGRO_FONT* font) : font(font), background_img(nullptr), ground_img(nullptr), gameover_bg_img(nullptr) {
    // Carrega a imagem de background
    background_img = al_load_bitmap("assets/background/background_2.png");
    if (!background_img) {
        std::cerr << "Erro ao carregar imagem de background!" << std::endl;
    }
    // Carrega a imagem do chão
    ground_img = al_load_bitmap("assets/ground/layer-3-ground.png");
    if (!ground_img) {
        std::cerr << "Erro ao carregar imagem do chão!" << std::endl;
    }
    gameover_bg_img = al_load_bitmap("assets/background/background_2.png");
    if (!gameover_bg_img) {
        std::cerr << "Erro ao carregar imagem de fundo do Game Over!" << std::endl;
    }
}

GameRenderer::~GameRenderer() {
    if (background_img) {
        al_destroy_bitmap(background_img);
    }
    if (ground_img) {
        al_destroy_bitmap(ground_img);
    }
    if (gameover_bg_img) {
        al_destroy_bitmap(gameover_bg_img);
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
    // Desenha a imagem de fundo do Game Over, se existir
    if (gameover_bg_img) {
        al_draw_bitmap(gameover_bg_img, 0, 0, 0);
    } else {
        renderBackground(); // fallback para fundo padrão
    }
    
    // Painel cobre toda a tela
    int panelX = 0;
    int panelY = 0;
    int panelWidth = game.getScreenWidth();
    int panelHeight = game.getScreenHeight();
    
    // Painel de fundo semitransparente
    al_draw_filled_rectangle(panelX, panelY, panelX + panelWidth, panelY + panelHeight, 
                           al_map_rgba(0, 0, 0, 180));
    
    // Borda do painel
    al_draw_rectangle(panelX, panelY, panelX + panelWidth, panelY + panelHeight, 
                     al_map_rgb(255, 255, 255), 3);
    
    // Título "FIM DE JOGO"
    al_draw_text(game.getFontTitle(), al_map_rgb(255, 60, 60), 
                game.getScreenWidth() / 2, panelY + 60, 
                ALLEGRO_ALIGN_CENTER, "FIM DE JOGO");
    
    // Estatísticas da partida
    int startY = panelY + 120;
    int lineHeight = 45;
    int xCenter = game.getScreenWidth() / 2;
    
    // Rótulo Pontuação
    al_draw_text(game.getFontRegular(), al_map_rgb(220, 220, 220), xCenter, startY, ALLEGRO_ALIGN_CENTER, "Pontuação:");
    // Número da Pontuação
    char scoreNum[32];
    sprintf(scoreNum, "%d", game.getScore());
    al_draw_text(game.getFontScore(), al_map_rgb(255, 255, 0), xCenter, startY + 28, ALLEGRO_ALIGN_CENTER, scoreNum);
    
    // Rótulo Seu Recorde
    al_draw_text(game.getFontRegular(), al_map_rgb(200, 200, 200), xCenter, startY + lineHeight + 10, ALLEGRO_ALIGN_CENTER, "Seu Recorde:");
    // Número do Recorde Pessoal
    if (game.getJogadorAtual()) {
        char personalBestNum[32];
        sprintf(personalBestNum, "%d", game.getJogadorAtual()->getPonto_max());
        al_draw_text(game.getFontScore(), al_map_rgb(255, 255, 255), xCenter, startY + lineHeight + 38, ALLEGRO_ALIGN_CENTER, personalBestNum);
    }
    
    // Rótulo Recorde Geral
    al_draw_text(game.getFontRegular(), al_map_rgb(200, 200, 200), xCenter, startY + lineHeight*2 + 20, ALLEGRO_ALIGN_CENTER, "Recorde Geral:");
    // Número do Recorde Geral
    char globalRecordNum[32];
    sprintf(globalRecordNum, "%d", game.getHighScore());
    al_draw_text(game.getFontScore(), al_map_rgb(255, 255, 255), xCenter, startY + lineHeight*2 + 48, ALLEGRO_ALIGN_CENTER, globalRecordNum);
    
    // Mensagem de celebração se for novo recorde
    bool isNewPersonalRecord = false;
    if (game.getJogadorAtual() && game.getScore() > game.getJogadorAtual()->getPonto_max()) {
        isNewPersonalRecord = true;
    }
    bool isNewGlobalRecord = (game.getScore() > game.getHighScore());
    int yNovoRecorde = startY + lineHeight*2 + 90; // 90px abaixo do início do bloco do recorde geral
    if (isNewPersonalRecord || isNewGlobalRecord) {
        al_draw_text(game.getFontRegular(), al_map_rgb(255, 215, 0), xCenter, yNovoRecorde, ALLEGRO_ALIGN_CENTER, "NOVO RECORDE!");
    }
    
    // Informações do jogador atual
    if (game.getJogadorAtual()) {
        char playerInfo[200];
        sprintf(playerInfo, "Jogador: %s (%s)", 
                game.getJogadorAtual()->getNome().c_str(),
                game.getJogadorAtual()->getApelido().c_str());
        al_draw_text(game.getFontRegular(), al_map_rgb(220, 220, 220), xCenter, startY + lineHeight*4 + 10, ALLEGRO_ALIGN_CENTER, playerInfo);
    }
    
    // Botões de ação centralizados
    int buttonY = panelY + panelHeight - 160;
    int buttonWidth = 240;
    int buttonHeight = 40;
    int buttonSpacing = 60;
    int btn1X = xCenter - buttonWidth - buttonSpacing/2;
    int btn2X = xCenter + buttonSpacing/2;
    // Botão "Jogar Novamente"
    al_draw_filled_rectangle(btn1X, buttonY, btn1X + buttonWidth, buttonY + buttonHeight, al_map_rgb(50, 150, 50));
    al_draw_rectangle(btn1X, buttonY, btn1X + buttonWidth, buttonY + buttonHeight, al_map_rgb(255, 255, 255), 2);
    al_draw_text(game.getFontRegular(), al_map_rgb(255, 255, 255), btn1X + buttonWidth/2, buttonY + 10, ALLEGRO_ALIGN_CENTER, "JOGAR NOVAMENTE");
    // Botão "Menu Principal"
    al_draw_filled_rectangle(btn2X, buttonY, btn2X + buttonWidth, buttonY + buttonHeight, al_map_rgb(150, 50, 50));
    al_draw_rectangle(btn2X, buttonY, btn2X + buttonWidth, buttonY + buttonHeight, al_map_rgb(255, 255, 255), 2);
    al_draw_text(game.getFontRegular(), al_map_rgb(255, 255, 255), btn2X + buttonWidth/2, buttonY + 10, ALLEGRO_ALIGN_CENTER, "MENU PRINCIPAL");
    // Instruções de rodapé
    int instructionsY = buttonY + buttonHeight + 20;
    al_draw_text(game.getFontSmall(), al_map_rgb(180, 180, 180), xCenter, instructionsY, ALLEGRO_ALIGN_CENTER, "ESPACO: Jogar Novamente | M: Menu Principal | ESC: Sair");
    
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
    al_draw_bitmap(background_img, 0, 0, 0);
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
    
    // Calcula posições dos campos
    int centerX = game.getScreenWidth() / 2;
    int nomeY = 150;
    int apelidoY = 200;
    int fieldWidth = 300;
    int fieldHeight = 30;
    
    // Desenha campo Nome com indicador de campo ativo
    if (game.campoPreenchido == 0) {
        // Campo ativo - destaque
        al_draw_filled_rectangle(centerX - fieldWidth/2 - 5, nomeY - 5, 
                                centerX + fieldWidth/2 + 5, nomeY + fieldHeight + 5, 
                                al_map_rgb(100, 100, 255));
    }
    al_draw_filled_rectangle(centerX - fieldWidth/2, nomeY, 
                            centerX + fieldWidth/2, nomeY + fieldHeight, 
                            al_map_rgb(50, 50, 50));
    al_draw_text(font, al_map_rgb(255,255,255), centerX - fieldWidth/2 + 10, nomeY + 5, 
                ALLEGRO_ALIGN_LEFT, ("Nome: " + game.inputNome).c_str());
    
    // Adiciona cursor piscante no campo ativo
    if (game.campoPreenchido == 0 && game.getCursorVisible()) {
        int cursorX = centerX - fieldWidth/2 + 10 + al_get_text_width(font, ("Nome: " + game.inputNome).c_str());
        al_draw_line(cursorX, nomeY + 5, cursorX, nomeY + fieldHeight - 5, al_map_rgb(255, 255, 255), 2);
    }
    
    // Desenha campo Apelido com indicador de campo ativo
    if (game.campoPreenchido == 1) {
        // Campo ativo - destaque
        al_draw_filled_rectangle(centerX - fieldWidth/2 - 5, apelidoY - 5, 
                                centerX + fieldWidth/2 + 5, apelidoY + fieldHeight + 5, 
                                al_map_rgb(100, 100, 255));
    }
    al_draw_filled_rectangle(centerX - fieldWidth/2, apelidoY, 
                            centerX + fieldWidth/2, apelidoY + fieldHeight, 
                            al_map_rgb(50, 50, 50));
    al_draw_text(font, al_map_rgb(255,255,255), centerX - fieldWidth/2 + 10, apelidoY + 5, 
                ALLEGRO_ALIGN_LEFT, ("Apelido: " + game.inputApelido).c_str());
    
    // Adiciona cursor piscante no campo ativo
    if (game.campoPreenchido == 1 && game.getCursorVisible()) {
        int cursorX = centerX - fieldWidth/2 + 10 + al_get_text_width(font, ("Apelido: " + game.inputApelido).c_str());
        al_draw_line(cursorX, apelidoY + 5, cursorX, apelidoY + fieldHeight - 5, al_map_rgb(255, 255, 255), 2);
    }
    
    // Instruções
    al_draw_text(font, al_map_rgb(0,255,0), 400, 300, ALLEGRO_ALIGN_CENTRE, 
                "ENTER para confirmar, TAB para alternar campo, ESC para cancelar");
    
    // Mensagem de feedback
    if (game.getShowFeedback()) {
        ALLEGRO_COLOR feedbackColor = (game.getFeedbackMessage().find("sucesso") != std::string::npos) ? 
                                     al_map_rgb(0, 255, 0) : al_map_rgb(255, 100, 100);
        al_draw_text(font, feedbackColor, 400, 350, ALLEGRO_ALIGN_CENTRE, 
                    game.getFeedbackMessage().c_str());
    }
    
    al_flip_display();
}
