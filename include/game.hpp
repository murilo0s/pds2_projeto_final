#ifndef GAME_HPP
#define GAME_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <vector>


// classes auxiliares que permitem acesso aos objetos do jogo (ponteiros/referências)
class Bird;
class Pipe;
class PlayerManager;
class GameRenderer;
class GameLogic;
class Player;

/**
 * @brief Enumeração para os estados do jogo
 * 
 * Define os possíveis estados que o jogo pode estar:
 * - MENU: Tela inicial do jogo
 * - PLAYING: Jogo em andamento
 * - GAME_OVER: Tela de fim de jogo
 * - GAME_EXIT: Saída do jogo
 * - CADASTRO_JOGADOR: Tela de cadastro de jogador
 * - SELECAO_JOGADOR: Tela de seleção de jogador
 * - RANKING: Tela de ranking
 * - PLAYER_MENU: Tela de menu do jogador
 */
enum GameState {
    PLAYER_MENU,
    CADASTRO_JOGADOR,
    MENU,
    PLAYING,
    GAME_OVER,
    GAME_EXIT,
    SELECAO_JOGADOR,
    RANKING
};

/**
 * @brief Classe principal do jogo
 *
 * Esta classe é responsável por gerenciar o loop principal do jogo,
 * os estados do jogo, e os objetos do jogo. Ela coordena as atividades
 * entre GameRenderer (renderização) e GameLogic (lógica do jogo).
 *
 */
class Game {
private:
    // Componentes Allegro
    ALLEGRO_DISPLAY* display; ///< janela do jogo
    ALLEGRO_TIMER* timer; ///< temporizador que controla o FPS
    ALLEGRO_FONT* font; ///< fonte para o jogo (para renderizar textos)
    ALLEGRO_FONT* fontLarge; ///< ponteiro para fonte grande
    ALLEGRO_FONT* fontMedium; ///< ponteiro para fonte média
    ALLEGRO_FONT* fontTitle;   ///< ponteiro para fonte do título
    ALLEGRO_FONT* fontScore;   ///< ponteiro para fonta da pontuação
    ALLEGRO_FONT* fontRegular; ///< ponteiro para fonte regular
    ALLEGRO_FONT* fontSmall;   ///< ponteiro para fonte pequena

    // Objetos do jogo
    Bird* bird; ///< ponteiro para o pássaro que o jogador controla
    std::vector<Pipe*> pipes; ///< vetor de ponteiros para os canos que o pássaro deve passar
    PlayerManager* playerManager; ///< ponteiro para o gerenciador de jogadores (aqui salva os dados do jogador)

    // Classes auxiliares
    GameRenderer* renderer; ///< classe responsável por renderizar os objetos do jogo
    GameLogic* logic; ///< classe responsável por atualizar a lógica do jogo

    // Estado do jogo
    GameState currentState; ///< Estado atual do jogo
    int score; ///< pontuação do jogador
    int highScore; ///< pontuação máxima do jogador
    bool running; ///< indica se o jogo está em execução
    bool keys[ALLEGRO_KEY_MAX]; ///< array que verifica se cada tecla foi pressionada

    // Controle de tempo
    double lastPipeSpawn; ///< tempo da última geração de cano
    double gameStartTime; ///< tempo de início do jogo

    // Dimensões da tela
    static const int SCREEN_WIDTH = 800; ///< largura da tela em pixels
    static const int SCREEN_HEIGHT = 600; ///< altura da tela em pixels
    static const int FPS = 60; ///< frames por segundo do jogo

    // Gerenciador de jogadores
    Player* jogadorAtual; ///< ponteiro para o jogador atualmente selecionado
    std::string nomeJogadorAtual; ///< nome do jogador atual
    std::string apelidoJogadorAtual; ///< apelido do jogador atual
    bool jogadorSelecionado; ///< indica se o jogador foi selecionado

    // Variáveis para melhorias na tela de cadastro
    double cursorBlinkTime; ///< tempo para controlar o piscar do cursor
    bool cursorVisible; ///< indica se o cursor está visível
    std::string feedbackMessage; ///< mensagem de feedback para o usuário
    double feedbackStartTime; ///< tempo de início da mensagem de feedback
    bool showFeedback; ///< indica se deve mostrar mensagem de feedback

    // inicialização
    /**
     * @brief Inicializa a biblioteca Allegro
     * 
     * Configura todos os componentes necessários:
     * - Display (janela)
     * - Event queue (fila de eventos)
     * - Timer (temporizador)
     * - Addons (imagem, fonte, TTF)
     * 
     * @return true se inicialização foi bem-sucedida, false caso contrário
     */
    bool initAllegro();
    
    /**
     * @brief Inicializa as fontes do jogo
     * 
     * Carrega a fonte padrão do Allegro para
     * renderização de textos.
     * 
     * @return true se fonte foi carregada, false caso contrário
     */
    bool initFonts();
    
    /**
     * @brief Inicializa os objetos do jogo
     * 
     * Cria e configura:
     * - Pássaro (Bird)
     * - Gerenciador de jogadores (PlayerManager)
     */
    void initGameObjects();

    /**
     * @brief Carrega a melhor pontuação do arquivo
     * 
     * Lê o arquivo "highscore.txt" e carrega
     * a melhor pontuação registrada.
     */
    void loadHighScore();

    // loop principal
    
    /**
     * @brief Processa eventos do Allegro
     * 
     * Captura e processa eventos como:
     * - Pressionar teclas
     * - Fechar janela
     * - Eventos do timer
     */
    void processEvents();
    
    /**
     * @brief Processa entrada do usuário
     * 
     * Delega o processamento de input para a classe
     * GameLogic baseado no estado atual do jogo.
     */
    void processInput();
    
    /**
     * @brief Atualiza a lógica do jogo
     * 
     * Delega a atualização da lógica para a classe
     * GameLogic, que atualiza posições, verifica
     * colisões, etc.
     */
    void update();
    
    /**
     * @brief Renderiza o jogo
     * 
     * Delega a renderização para a classe GameRenderer,
     * que desenha todos os elementos na tela baseado
     * no estado atual do jogo.
     */
    void render();

    // limpeza
    
    /**
     * @brief Limpa todos os recursos do jogo
     * 
     * Chama os métodos de limpeza específicos
     * para garantir que todos os recursos sejam
     * liberados corretamente.
     */
    void cleanup();
    
    /**
     * @brief Limpa os componentes do Allegro
     * 
     * Libera recursos alocados pelo Allegro:
     * - Display
     * - Event queue
     * - Timer
     * - Fontes
     */
    void cleanupAllegro();
    
    /**
     * @brief Limpa os objetos do jogo
     * 
     * Libera memória alocada para:
     * - Pássaro
     * - Pipes
     * - PlayerManager
     * - Classes auxiliares (GameRenderer, GameLogic)
     */
    void cleanupGameObjects();

public:
    ALLEGRO_EVENT_QUEUE* eventQueue;
    std::string inputNome;
    std::string inputApelido;
    int campoPreenchido;
    /**
     * @brief Construtor da classe Game
     *
     * Inicia todos os componentes do jogo:
     * - biblioteca Allegro
     * - fontes
     * - objetos do jogo (bird, pipes, etc.)
     * - classes auxiliares (GameRenderer, GameLogic, ...)
     */
    Game();

    /**
     * @brief Destrutor da classe Game
     *
     * Libera todos os recursos alocados:
     * - componentes Allegro
     * - objetos do jogo
     * - classes auxiliares
     */
    ~Game();

    /**
     * @brief Método principal que executa o jogo
     *
     * Contém o loop principal do jogo que:
     * - processa eventos (teclado, mouse)
     * - atualiza a lógica do jogo
     * - renderiza os elementos na tela
     * - controla o FPS
     */
    void run();
    
    /**
     * @brief Retorna a pontuação atual do jogador
     * @return Pontuação atual do jogador
     */
    int getScore() const { return score; }
    
    /**
     * @brief Retorna a melhor pontuação registrada
     * @return Melhor pontuação do jogador
     */
    int getHighScore() const { return highScore; }
    
    /**
     * @brief Retorna o estado atual do jogo
     * @return Estado atual (MENU, PLAYING, GAME_OVER)
     */
    GameState getCurrentState() const { return currentState; }
    
    /**
     * @brief Retorna a largura da tela
     * @return Largura da tela em pixels
     */
    int getScreenWidth() const { return SCREEN_WIDTH; }
    
    /**
     * @brief Retorna a altura da tela
     * @return Altura da tela em pixels
     */
    int getScreenHeight() const { return SCREEN_HEIGHT; }
    
    /**
     * @brief Retorna o FPS do jogo
     * @return Frames por segundo configurados
     */
    int getFPS() const { return FPS; }
    
    // setters básicos
    
    /**
     * @brief Define a pontuação do jogador
     * @param newScore Nova pontuação do jogador
     */
    void setScore(int newScore) { score = newScore; }
    
    /**
     * @brief Define a melhor pontuação registrada
     * @param newHighScore Nova melhor pontuação
     */
    void setHighScore(int newHighScore) { highScore = newHighScore; }
    
    /**
     * @brief Define o estado atual do jogo
     * @param newState Novo estado do jogo
     */
    void setCurrentState(GameState newState) { currentState = newState; }
    
    /**
     * @brief Define se o jogo está em execução
     * @param isRunning true se o jogo deve continuar rodando, false para parar
     */
    void setRunning(bool isRunning) { running = isRunning; }
    
    // getters para objetos do jogo
    
    /**
     * @brief Retorna o ponteiro para o pássaro
     * 
     * Usado pelas classes GameLogic e GameRenderer para acessar
     * e modificar o pássaro do jogo.
     * 
     * @return Ponteiro para o objeto Bird
     */
    Bird* getBird() const { return bird; }
    
    /**
     * @brief Retorna a lista de pipes do jogo
     * 
     * Retorna uma referência para o vetor de pipes, permitindo
     * que GameLogic adicione, remova ou modifique pipes.
     * 
     * @return Referência para o vetor de pipes
     */
    std::vector<Pipe*>& getPipes() { return pipes; }
    const std::vector<Pipe*>& getPipes() const { return pipes; }
    
    /**
     * @brief Retorna o gerenciador de jogadores
     * @return Ponteiro para o PlayerManager
     */
    PlayerManager* getPlayerManager() const { return playerManager; }
    
    // getters para componentes allegro
    
    /**
     * @brief Retorna a janela do jogo
     * 
     * Usado pelo GameRenderer para acessar a janela
     * e realizar operações de renderização.
     * 
     * @return Ponteiro para a janela do jogo
     */
    ALLEGRO_DISPLAY* getDisplay() const { return display; }
    
    /**
     * @brief Retorna a fonte do jogo
     * 
     * Usado pelo GameRenderer para renderizar textos
     * na tela.
     * 
     * @return Ponteiro para a fonte do jogo
     */
    ALLEGRO_FONT* getFont() const { return font; }
    
    // controle de tempo
    
    /**
     * @brief Retorna o tempo da última geração de pipe
     * @return Tempo da última geração de pipe
     */
    double getLastPipeSpawn() const { return lastPipeSpawn; }
    
    /**
     * @brief Define o tempo da última geração de pipe
     * @param time Novo tempo da última geração
     */
    void setLastPipeSpawn(double time) { lastPipeSpawn = time; }
    
    /**
     * @brief Retorna o tempo de início do jogo
     * @return Tempo quando o jogo foi iniciado
     */
    double getGameStartTime() const { return gameStartTime; }
    
    // getters para input
    
    /**
     * @brief Retorna o array de estado das teclas
     * 
     * Usado pelo GameLogic para verificar quais teclas
     * estão pressionadas.
     * 
     * @return Ponteiro para o array de teclas
     */
    bool* getKeys() { return keys; }

    /**
 * @brief Exibe o menu relacionado ao jogador.
 */
void menuJogador();

/**
 * @brief Obtém o ponteiro para o jogador atual.
 * 
 * @return Ponteiro para o jogador atual (modificável).
 */
Player* getJogadorAtual();

/**
 * @brief Obtém o ponteiro constante para o jogador atual.
 * 
 * @return Ponteiro constante para o jogador atual (somente leitura).
 */
const Player* getJogadorAtual() const;

/**
 * @brief Define o jogador atual.
 * 
 * @param jogador Ponteiro para o jogador que será definido como atual.
 */
void setJogadorAtual(Player* jogador);

/**
 * @brief Obtém o tempo de piscar do cursor.
 * 
 * @return Tempo em segundos de piscar do cursor.
 */
double getCursorBlinkTime() const;

/**
 * @brief Verifica se o cursor está visível.
 * 
 * @return `true` se o cursor está visível, `false` caso contrário.
 */
bool getCursorVisible() const;

/**
 * @brief Obtém a mensagem de feedback atual.
 * 
 * @return String com a mensagem de feedback.
 */
std::string getFeedbackMessage() const;

/**
 * @brief Obtém o tempo em que a mensagem de feedback começou a ser exibida.
 * 
 * @return Tempo em segundos desde o início da exibição da mensagem de feedback.
 */
double getFeedbackStartTime() const;

/**
 * @brief Verifica se a mensagem de feedback deve ser exibida.
 * 
 * @return `true` se a mensagem de feedback está ativa, `false` caso contrário.
 */
bool getShowFeedback() const;

/**
 * @brief Define o tempo de piscar do cursor.
 * 
 * @param time Tempo em segundos.
 */
void setCursorBlinkTime(double time);

/**
 * @brief Define a visibilidade do cursor.
 * 
 * @param visible `true` para mostrar o cursor, `false` para ocultar.
 */
void setCursorVisible(bool visible);

/**
 * @brief Define a mensagem de feedback.
 * 
 * @param message Texto da mensagem de feedback.
 */
void setFeedbackMessage(const std::string& message);

/**
 * @brief Define o tempo de início da exibição da mensagem de feedback.
 * 
 * @param time Tempo em segundos.
 */
void setFeedbackStartTime(double time);

/**
 * @brief Define a exibição da mensagem de feedback.
 * 
 * @param show `true` para exibir a mensagem, `false` para ocultar.
 */
void setShowFeedback(bool show);

/**
 * @brief Obtém a fonte grande.
 * 
 * @return Ponteiro para a fonte grande (ALLEGRO_FONT).
 */
ALLEGRO_FONT* getFontLarge() const;

/**
 * @brief Obtém a fonte média.
 * 
 * @return Ponteiro para a fonte média (ALLEGRO_FONT).
 */
ALLEGRO_FONT* getFontMedium() const;

/**
 * @brief Obtém a fonte usada para títulos.
 * 
 * @return Ponteiro para a fonte de título (ALLEGRO_FONT).
 */
ALLEGRO_FONT* getFontTitle() const;

/**
 * @brief Obtém a fonte usada para a pontuação.
 * 
 * @return Ponteiro para a fonte de pontuação (ALLEGRO_FONT).
 */
ALLEGRO_FONT* getFontScore() const;

/**
 * @brief Obtém a fonte regular.
 * 
 * @return Ponteiro para a fonte regular (ALLEGRO_FONT).
 */
ALLEGRO_FONT* getFontRegular() const;

/**
 * @brief Obtém a fonte pequena.
 * 
 * @return Ponteiro para a fonte pequena (ALLEGRO_FONT).
 */
ALLEGRO_FONT* getFontSmall() const;
};
#endif 