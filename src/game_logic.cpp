#include "game_logic.hpp"
#include "game.hpp"
#include "bird.hpp"
#include "pipe.hpp"
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
        game.setCurrentState(MENU);
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

void GameLogic::trataCadastroIput(Game& game) {
    if (isKeyJustPressed(ALLEGRO_KEY_ENTER)) {
        if(game.campoPreenchido == 0) {
            game.campoPreenchido = 1;
        } else {
            processarCadastroJogador(game);
        }
    } else if(isKeyJustPressed(ALLEGRO_KEY_ESCAPE)) {
        game.currentState = MENU;
        game.inputNome.clear();
        game.inputApelido.clear();
        game.campoPreenchido = 0;
    }
}

void GameLogic::processarCadastroJogador(Game& game) {
    if(!game.inputNome == "" || !game.inputApelido == "") {
        game.playerManager->cadastrar(game.inputNome, game.inputApelido);
        game.playerManager->salvar("ranking.txt");
        game.currentState = MENY;
        game.inputNome.clear();
        game.inputApelido.clear();
        game.campoPreenchido = 0;
    }
}

void GameLogic::atualizarEstatisticasJogador(Game& game) {
    if(game.jogadorAtual) {
        game.jogadorAtual->incrementar_partidas();
        game.jogadorAtual->update_pontuacao(game.score);
        game.playerManager->salvar("ranking.txt");
    }
}