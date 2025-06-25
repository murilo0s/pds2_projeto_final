#include "game.hpp"
#include "game_renderer.hpp"
#include "game_logic.hpp"
#include "bird.hpp"
#include "pipe.hpp"
#include "PlayerManager.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <fstream>
#include <cstdlib>
#include <iostream>

Game::Game() : display(nullptr), eventQueue(nullptr), timer(nullptr), font(nullptr),
               fontLarge(nullptr), fontMedium(nullptr), fontTitle(nullptr), fontScore(nullptr),
               fontRegular(nullptr), fontSmall(nullptr), bird(nullptr), playerManager(nullptr), renderer(nullptr), logic(nullptr),
               currentState(PLAYER_MENU), score(0), highScore(0), running(true),
               lastPipeSpawn(0), gameStartTime(0), inputNome(""), inputApelido(""), campoPreenchido(0),
               cursorBlinkTime(0), cursorVisible(true), feedbackMessage(""), feedbackStartTime(0), showFeedback(false) {
    
    // Inicializa o array de teclas (define todas as teclas como não pressionadas)
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        keys[i] = false;
    }
    
    try {
        if (!initAllegro()) {
            throw std::runtime_error("Falha na inicialização do Allegro");
        }
        
        if (!initFonts()) {
            throw std::runtime_error("Falha na inicialização das fontes");
        }
        
        // Inicializa as classes auxiliares
        renderer = new GameRenderer(font);
        logic = new GameLogic();
        
        initGameObjects();
        loadHighScore();
        playerManager->carregar("ranking.txt");
        jogadorAtual = nullptr;
        jogadorSelecionado = false;
        campoPreenchido = 0;
    } catch (const std::exception& e) {
        cleanup();
        throw; // Re-lança a exceção para ser capturada no main
    }
}

Game::~Game() {
    cleanup();
}

void Game::run() {
    gameStartTime = al_get_time();
    lastPipeSpawn = gameStartTime;
    while (running) {
        processInput();
        update();
        render();
        al_rest(1.0 / FPS);
    }
}

bool Game::initAllegro() {
    if (!al_init()) {
        throw std::runtime_error("Falha na inicialização do Allegro");
    }
    
    if (!al_init_image_addon()) {
        throw std::runtime_error("Falha na inicialização do addon de imagem do Allegro");
    }
    
    if (!al_init_font_addon()) {
        throw std::runtime_error("Falha na inicialização do addon de fonte do Allegro");
    }
    
    if (!al_init_ttf_addon()) {
        throw std::runtime_error("Falha na inicialização do addon TTF do Allegro");
    }
    
    if (!al_init_primitives_addon()) {
        throw std::runtime_error("Falha na inicialização do addon de primitivas do Allegro");
    }
    
    if (!al_install_keyboard()) {
        throw std::runtime_error("Falha na instalação do teclado");
    }
    
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        throw std::runtime_error("Falha na criação do display");
    }
    
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        throw std::runtime_error("Falha na criação da fila de eventos");
    }
    
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        throw std::runtime_error("Falha na criação do timer");
    }
    
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    
    al_start_timer(timer);
    
    return true;
}

bool Game::initFonts() {
    font = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 25, 0);
    fontLarge = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 48, 0);
    fontMedium = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 32, 0);
    fontTitle = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 48, 0);
    fontScore = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 36, 0);
    fontRegular = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 24, 0);
    fontSmall = al_load_ttf_font("assets/Fontes/GBStudioMono.ttf", 20, 0);
    if (!font || !fontLarge || !fontMedium || !fontTitle || !fontScore || !fontRegular || !fontSmall) {
        throw std::runtime_error("Falha no carregamento das fontes TTF");
    }
    return true;
}

void Game::initGameObjects() {
    bird = new Bird(100, SCREEN_HEIGHT / 2);
    playerManager = new PlayerManager();
    playerManager->carregar("ranking.txt");
}

void Game::processEvents() {
    ALLEGRO_EVENT event;
    while (al_get_next_event(eventQueue, &event)) {
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
    }
}

void Game::processInput() {
    switch (currentState) {
        case PLAYER_MENU:
            logic->handlePlayerMenuInput(*this);
            break;
        case CADASTRO_JOGADOR:
            logic->handleCadastroJogadorInput(*this);
            break;
        case MENU:
            logic->handleMenuInput(*this);
            break;
        case PLAYING:
            logic->handleGameInput(*this);
            break;
        case GAME_OVER:
            logic->handleGameOverInput(*this);
            break;
        case GAME_EXIT:
            running = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    if (currentState == PLAYING) {
        // Atualiza o pássaro
        if (bird) {
            bird->update(1.0 / FPS);
        }
        
        // Atualiza pipes
        logic->spawnPipe(*this);
        logic->updatePipes(*this);
        logic->removePipes(*this);
        
        // Verifica colisões e pontuação
        logic->checkCollisions(*this);
        logic->calculateScore(*this);
    }
    
    // Atualiza o cursor piscante para a tela de cadastro
    if (currentState == CADASTRO_JOGADOR) {
        cursorBlinkTime += 1.0 / FPS;
        
        // Pisca o cursor a cada 0.5 segundos
        if (cursorBlinkTime >= 0.5) {
            cursorVisible = !cursorVisible;
            cursorBlinkTime = 0;
        }
    }
    
    // Controla a duração das mensagens de feedback
    if (showFeedback) {
        double currentTime = al_get_time();
        if (currentTime - feedbackStartTime >= 3.0) { // 3 segundos
            showFeedback = false;
            feedbackMessage = "";
        }
    }
}

void Game::render() {
    switch (currentState) {
        case PLAYER_MENU:
            renderer->renderPlayerMenu(*this);
            break;
        case CADASTRO_JOGADOR:
            renderer->renderCadastroJogador(*this);
            break;
        case MENU:
            renderer->renderMenu(*this);
            break;
        case PLAYING:
            renderer->renderPlaying(*this);
            break;
        case GAME_OVER:
            renderer->renderGameOver(*this);
            break;
        case GAME_EXIT:
            // Não renderiza nada quando está saindo
            break;
        default:
            break;
    }
}

void Game::loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}

void Game::cleanup() {
    cleanupGameObjects();
    cleanupAllegro();
    if (playerManager && jogadorAtual) {
        jogadorAtual->incrementar_partidas();
        jogadorAtual->update_pontuacao_max(score);
        playerManager->salvar("ranking.txt");
    }
}

void Game::cleanupAllegro() {
    if (font) al_destroy_font(font);
    if (fontLarge) al_destroy_font(fontLarge);
    if (fontMedium) al_destroy_font(fontMedium);
    if (fontTitle) al_destroy_font(fontTitle);
    if (fontScore) al_destroy_font(fontScore);
    if (fontRegular) al_destroy_font(fontRegular);
    if (fontSmall) al_destroy_font(fontSmall);
    if (timer) al_destroy_timer(timer);
    if (eventQueue) al_destroy_event_queue(eventQueue);
    if (display) al_destroy_display(display);
}

void Game::cleanupGameObjects() {
    if (bird) {
        delete bird;
    }
    
    // Limpa os pipes
    for (size_t i = 0; i < pipes.size(); i++) {
        delete pipes[i];
    }
    pipes.clear();
    
    if (playerManager) {
        delete playerManager;
    }
    
    if (renderer) {
        delete renderer;
    }
    
    if (logic) {
        delete logic;
    }
}

void Game::menuJogador() {
}