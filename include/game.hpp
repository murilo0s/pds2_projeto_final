#ifndef GAME_HPP
#define GAME_HPP
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <memory>

class Bird;
class Pipe;
class PlayerManager;

enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class Game {
private:

    //Componetes do allegro
    ALLEGRO_DISPLAY* display; // Janela do jogo
    ALLEGRO_EVENT_QUEUE* eventQueue; // Fila de eventos
    ALLEGRO_TIMER* timer; // Temporizador para controle de FPS
    ALLEGRO_FONT* font; // Fonte para renderização de texto

    // Objetos do jogo
    std::unique_ptr<Bird> bird; // Pássaro controlado pelo jogador
    std::vector<std::unique_ptr<Pipe>> pipes; // Pipes que o pássaro deve evitar
    std::unique_ptr<PlayerManager> playerManager; // Gerenciador de jogadores

    // Estado do jogo
    GameState currentState; // Estado atual do jogo
    int score; // Pontuação do jogador
    int highScore; // Melhor pontuação registrada
    bool running; // Flag para controle do loop principal
    bool keys[ALLEGRO_KEY_MAX]; // Array para controle de teclas pressionadas

    // Controle de tempo
    double lastPipeSpawn; // Tempo do último pipe gerado
    double gameStartTime; // Tempo de início do jogo

    // Dimensões da tela
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
    static const int FPS = 60; // Frames por segundo

public:
    Game();
    ~Game();

    void run(); // Inicia o loop principal do jogo

    // Getters
    int getScore() const { return score; } // Retorna a pontuação atual
    int getHighScore() const { return highScore; } // Retorna a melhor pontuação
    GameState getCurrentState() const { return currentState; } // Retorna o estado atual do jogo
    int getScreenWidth() const { return SCREEN_WIDTH; } // Retorna a largura da tela
    int getScreenHeight() const { return SCREEN_HEIGHT; } // Retorna a altura da tela

    // State management
    void changeState(GameState newState); // Altera o estado do jogo

private:
    // Inicialiação
    bool initAllegro(); // Inicializa o Allegro e seus componentes
    bool initFonts(); // Inicializa as fontes
    void initGameObjects(); // Inicializa os objetos do jogo (pássaro, pipes, etc.)

    // Loop principal do jogo
    void processEvents(); // Processa eventos do Allegro
    void processInput(); // Processa entrada do usuário (teclado, mouse)
    void update(); // Atualiza o estado do jogo (movimentação, colisões, etc.)
    void render(); // Renderiza os objetos na tela

    // Entrada do usuário
    void handleMenuInput(); // Processa entrada no menu
    void handleGameInput(); // Processa entrada durante o jogo
    void handleGameOverInput(); // Processa entrada na tela de game over
    void handlePauseInput(); // Processa entrada durante a pausa

    // Atualização de telas
    void updateMenu(); // Atualiza o menu
    void updatePlaying(); // Atualiza o estado de jogo em andamento
    void updateGameOver(); // Atualiza o estado de game over
    void updatePaused(); // Atualiza o estado de pausa

    // Renderização de telas
    void renderMenu(); // Renderiza o menu
    void renderPlaying(); // Renderiza o jogo em andamento
    void renderGameOver(); // Renderiza a tela de game over
    void renderPaused(); // Renderiza a tela de pausa

    // Lógica do jogo
    void spawnPipe(); // Gera um novo pipe
    void updatePipes(); // Atualiza a posição dos pipes
    void removePipes(); // Remove pipes fora da tela
    void checkCollisions(); // Verifica colisões entre o pássaro e os pipes
    void calculateScore(); // Calcula a pontuação do jogador
    void checkGameOver(); // Verifica se o jogo acabou
    void resetGame(); // Reseta o jogo para o estado inicial
    void updateHighScore(); // Salva a melhor pontuação em um arquivo

    // Renderização
    void renderScore(); // Renderiza a pontuação na tela
    void renderBackground(); // Renderiza o fundo do jogo
    void renderUI(); // Renderiza a interface do usuário

    // Funções auxiliares
    void centerText(const char* text, float y); // Centraliza o texto na tela
    bool isKeyPressed(int keycode); // Verifica se uma tecla está pressionada
    bool isKeyJustPressed(int keycode); // Verifica se uma tecla foi pressionada apenas uma vez

    void cleanup(); // Limpa todos os recursos alocados pelo jogo
    void cleanupAllegro(); // Limpa os componentes do Allegro
    void cleanupGameObjects(); // Limpa os objetos do jogo
};
#endif 