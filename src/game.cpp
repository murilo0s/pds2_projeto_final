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

Game::Game() : display(nullptr), eventQueue(nullptr), timer(nullptr), font(nullptr),
               bird(nullptr), playerManager(nullptr), renderer(nullptr), logic(nullptr),
               currentState(MENU), score(0), highScore(0), running(true),
               lastPipeSpawn(0), gameStartTime(0) {
    
    // Inicializa o array de teclas (define todas as teclas como não pressionadas)
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        keys[i] = false;
    }
    
    if (!initAllegro()) {
        // Tratar erro de inicialização
        return;
    }
    
    if (!initFonts()) {
        // Tratar erro de fontes
        return;
    }
    
    // Inicializa as classes auxiliares
    renderer = new GameRenderer(font);
    logic = new GameLogic();
    
    initGameObjects();
    loadHighScore();
}

Game::~Game() {
    cleanup();
}

void Game::run() {
    gameStartTime = al_get_time();
    lastPipeSpawn = gameStartTime;
    
    while (running) {
        processEvents();
        processInput();
        update();
        render();
        
        al_rest(1.0 / FPS);
    }
}

bool Game::initAllegro() {
    if (!al_init()) {
        return false;
    }
    
    if (!al_init_image_addon()) {
        return false;
    }
    
    if (!al_init_font_addon()) {
        return false;
    }
    
    if (!al_init_ttf_addon()) {
        return false;
    }
    
    if (!al_init_primitives_addon()) {
        return false;
    }
    
    if (!al_install_keyboard()) {
        return false;
    }
    
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        return false;
    }
    
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        return false;
    }
    
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        return false;
    }
    
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    
    al_start_timer(timer);
    
    return true;
}

bool Game::initFonts() {
    font = al_create_builtin_font();
    if (!font) {
        return false;
    }
    return true;
}

void Game::initGameObjects() {
    bird = new Bird(100, SCREEN_HEIGHT / 2);
    playerManager = new PlayerManager();
}

void Game::processEvents() {
    ALLEGRO_EVENT event;
    while (al_get_next_event(eventQueue, &event)) {
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                keys[event.keyboard.keycode] = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                keys[event.keyboard.keycode] = false;
                break;
        }
    }
}

void Game::processInput() {
    switch (currentState) {
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
}

void Game::render() {
    switch (currentState) {
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
}

void Game::cleanupAllegro() {
    if (font) {
        al_destroy_font(font);
    }
    if (timer) {
        al_destroy_timer(timer);
    }
    if (eventQueue) {
        al_destroy_event_queue(eventQueue);
    }
    if (display) {
        al_destroy_display(display);
    }
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