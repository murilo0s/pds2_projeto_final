#include "game_logic.hpp"
#include "game.hpp"
#include "bird.hpp"
#include "pipe.hpp"
#include "Player.hpp"
#include "PlayerManager.hpp"
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

GameLogic::GameLogic() {
}

GameLogic::~GameLogic() {
}

void GameLogic::spawnPipe(Game& game) {
    double currentTime = al_get_time();
    if (currentTime - game.getLastPipeSpawn() > 2.0) { // Spawn a cada 2 segundos
        try { // tenta criar um novo cano
            float gapY = 200 + (rand() % 200); // Posição aleatória do gap
            Pipe* newPipe = new Pipe(game.getScreenWidth(), gapY);
            game.getPipes().push_back(newPipe);
            game.setLastPipeSpawn(currentTime);

        } catch (const std::runtime_error& e) { // se não conseguir criar o cano, mostra mensagens de erro e sai do jogo
            std::cerr << "ERRO: " << e.what() << std::endl;
            std::cerr << "O jogo nao pode continuar! Encerrando..." << std::endl;
            game.setCurrentState(GAME_EXIT);
        }
    }
}

void GameLogic::updatePipes(Game& game) {
    for (size_t i = 0; i < game.getPipes().size(); i++) {
        game.getPipes()[i]->update(1.0 / 60.0); // deltaTime para 60 FPS
    }
}

void GameLogic::removePipes(Game& game) {
    // Remove pipes que saíram da tela
    for (int i = game.getPipes().size() - 1; i >= 0; i--) {
        if (game.getPipes()[i]->getX() + game.getPipes()[i]->getWidth() < 0) {
            delete game.getPipes()[i];
            game.getPipes().erase(game.getPipes().begin() + i);
        }
    }
}

void GameLogic::checkCollisions(Game& game) {
    if (!game.getBird()) return;
    
    // Verifica colisão com pipes
    for (size_t i = 0; i < game.getPipes().size(); i++) {
        if (game.getPipes()[i]->checkCollision(*game.getBird())) {
            game.setCurrentState(GAME_OVER);
            updateHighScore(game);
            return;
        }
    }
    
    // Verifica se o pássaro saiu da tela
    if (game.getBird()->getY() < 0 || game.getBird()->getY() > game.getScreenHeight()) {
        game.setCurrentState(GAME_OVER);
        updateHighScore(game);
        return;
    }
}

void GameLogic::calculateScore(Game& game) {
    if (!game.getBird()) return;
    
    for (size_t i = 0; i < game.getPipes().size(); i++) {
        if (game.getPipes()[i]->isPassed(*game.getBird())) {
            game.setScore(game.getScore() + 1);
        }
    }
}

void GameLogic::checkGameOver(Game& game) {
    // A verificação de game over é feita em checkCollisions
}

void GameLogic::resetGame(Game& game) {
    game.setScore(0);
    game.setCurrentState(PLAYING);
    
    // Limpa os pipes
    for (size_t i = 0; i < game.getPipes().size(); i++) {
        delete game.getPipes()[i];
    }
    game.getPipes().clear();
    
    game.setLastPipeSpawn(al_get_time());
    
    // Reseta o pássaro
    if (game.getBird()) {
        game.getBird()->setPosition(100, game.getScreenHeight() / 2);
    }
}

void GameLogic::updateHighScore(Game& game) {
    if (game.getScore() > game.getHighScore()) {
        game.setHighScore(game.getScore());
        
        // Salva o high score em arquivo
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << game.getHighScore();
            file.close();
        }
    }
}

void GameLogic::handleMenuInput(Game& game) {
    if (isKeyJustPressed(ALLEGRO_KEY_SPACE)) {
        game.setCurrentState(PLAYING);
        resetGame(game);
    }
    
    if (isKeyJustPressed(ALLEGRO_KEY_ESCAPE)) {
        game.setRunning(false);
    }
}

void GameLogic::handleGameInput(Game& game) {
    if (isKeyJustPressed(ALLEGRO_KEY_SPACE)) {
        if (game.getBird()) {
            game.getBird()->jump();
        }
    }
    
    if (isKeyJustPressed(ALLEGRO_KEY_ESCAPE)) {
        game.setRunning(false);
    }
}

void GameLogic::handleGameOverInput(Game& game) {
    if (isKeyJustPressed(ALLEGRO_KEY_SPACE)) {
        // Atualiza estatísticas do jogador atual
        if (game.getJogadorAtual()) {
            game.getJogadorAtual()->incrementar_partidas();
            game.getJogadorAtual()->update_pontuacao_max(game.getScore());
            game.getPlayerManager()->salvar("ranking.txt");
        }
        resetGame(game); // Reinicia o jogo
        game.setCurrentState(PLAYING);
    }
    if (isKeyJustPressed(ALLEGRO_KEY_M)) {
        // Atualiza estatísticas do jogador atual
        if (game.getJogadorAtual()) {
            game.getJogadorAtual()->incrementar_partidas();
            game.getJogadorAtual()->update_pontuacao_max(game.getScore());
            game.getPlayerManager()->salvar("ranking.txt");
        }
        game.setCurrentState(PLAYER_MENU);
    }
    if (isKeyJustPressed(ALLEGRO_KEY_ESCAPE)) {
        game.setRunning(false);
    }
}

void GameLogic::handlePauseInput(Game& game) {
    if (isKeyJustPressed(ALLEGRO_KEY_P)) {
        game.setCurrentState(PLAYING);
    }
    
    if (isKeyJustPressed(ALLEGRO_KEY_ESCAPE)) {
        game.setRunning(false);
    }
}

void GameLogic::handlePlayerMenuInput(Game& game) {
    ALLEGRO_EVENT event;
    while (al_get_next_event(game.eventQueue, &event)) {
        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            int key = event.keyboard.keycode;
            if (key == ALLEGRO_KEY_N) {
                game.inputNome = "";
                game.inputApelido = "";
                game.campoPreenchido = 0;
                game.setCurrentState(CADASTRO_JOGADOR);
            } else if (key >= ALLEGRO_KEY_1 && key <= ALLEGRO_KEY_9) {
                int idx = key - ALLEGRO_KEY_1;
                auto& jogadores = game.getPlayerManager()->getJogadores();
                if (idx < jogadores.size()) {
                    game.setJogadorAtual(&(jogadores[idx]));
                    game.setCurrentState(MENU);
                    return;
                }
            } else if (key == ALLEGRO_KEY_ESCAPE) {
                game.setRunning(false);
                return;
            }
        }
    }
}

void GameLogic::handleCadastroJogadorInput(Game& game) {
    ALLEGRO_EVENT event;
    while (al_get_next_event(game.eventQueue, &event)) {
        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            int key = event.keyboard.keycode;
            unsigned int unichar = event.keyboard.unichar;

            if (key == ALLEGRO_KEY_TAB) {
                game.campoPreenchido = 1 - game.campoPreenchido; // alterna entre nome e apelido
                // Reseta o cursor quando muda de campo
                game.setCursorVisible(true);
                game.setCursorBlinkTime(0);
                // Limpa mensagem de feedback quando o usuário interage
                game.setShowFeedback(false);
            } else if (key == ALLEGRO_KEY_ENTER) {
                if (!game.inputNome.empty() && !game.inputApelido.empty()) {
                    // Verifica se o apelido já existe
                    bool apelidoExiste = false;
                    for (const auto& jogador : game.getPlayerManager()->getJogadores()) {
                        if (jogador.getApelido() == game.inputApelido) {
                            apelidoExiste = true;
                            break;
                        }
                    }
                    
                    if (apelidoExiste) {
                        // Mostra mensagem de erro
                        game.setFeedbackMessage("Apelido ja existe. Tente outro.");
                        game.setFeedbackStartTime(al_get_time());
                        game.setShowFeedback(true);
                    } else {
                        // Cadastra o jogador com sucesso
                        game.getPlayerManager()->cadastrar(game.inputNome, game.inputApelido);
                        game.getPlayerManager()->salvar("ranking.txt");
                        
                        // Mostra mensagem de sucesso
                        game.setFeedbackMessage("Jogador cadastrado com sucesso!");
                        game.setFeedbackStartTime(al_get_time());
                        game.setShowFeedback(true);
                        
                        // Aguarda um pouco antes de voltar ao menu
                        al_rest(2.0);
                        game.setCurrentState(PLAYER_MENU);
                    }
                }
            } else if (key == ALLEGRO_KEY_ESCAPE) {
                game.setCurrentState(PLAYER_MENU);
            } else if (key == ALLEGRO_KEY_BACKSPACE) {
                if (game.campoPreenchido == 0 && !game.inputNome.empty())
                    game.inputNome.pop_back();
                else if (game.campoPreenchido == 1 && !game.inputApelido.empty())
                    game.inputApelido.pop_back();
                
                // Reseta o cursor quando o usuário digita
                game.setCursorVisible(true);
                game.setCursorBlinkTime(0);
                // Limpa mensagem de feedback quando o usuário interage
                game.setShowFeedback(false);
            } else if (unichar >= 32 && unichar <= 126) { // caracteres imprimíveis
                if (game.campoPreenchido == 0 && game.inputNome.size() < 16)
                    game.inputNome += static_cast<char>(unichar);
                else if (game.campoPreenchido == 1 && game.inputApelido.size() < 16)
                    game.inputApelido += static_cast<char>(unichar);
                
                // Reseta o cursor quando o usuário digita
                game.setCursorVisible(true);
                game.setCursorBlinkTime(0);
                // Limpa mensagem de feedback quando o usuário interage
                game.setShowFeedback(false);
            }
        }
    }
}

bool GameLogic::isKeyPressed(int keycode) {
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);
    return al_key_down(&state, keycode);
}

bool GameLogic::isKeyJustPressed(int keycode) {
    // Implementação simples - pode ser melhorada com tracking de estado
    static bool keyStates[ALLEGRO_KEY_MAX] = {false};
    
    bool currentlyPressed = isKeyPressed(keycode);
    bool wasPressed = keyStates[keycode];
    
    keyStates[keycode] = currentlyPressed;
    
    return currentlyPressed && !wasPressed;
}