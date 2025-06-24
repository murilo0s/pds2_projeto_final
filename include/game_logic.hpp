#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <allegro5/allegro.h>
#include "game.hpp"

// Forward declarations
class Game;
enum GameState;

/**
 * @brief Classe que faz a lógica do jogo
 *
 * Esta classe controla:
 * - Criação e movimento dos pipes
 * - Verificação de colisões
 * - Pontuação do jogador
 * - Input do teclado
 */
class GameLogic {
public:
    /**
     * @brief Construtor da classe GameLogic
     */
    GameLogic();

    /**
     * @brief Destrutor da classe GameLogic
     */
    ~GameLogic();

    
    /**
     * @brief Cria um novo pipe no jogo
     * 
     * Verifica se já passou tempo suficiente desde o último pipe
     * e cria um novo com posição aleatória.
     * 
     * @param game referencia para o objeto game
     */
    void spawnPipe(Game& game);
    
    /**
     * @brief Atualiza a posição de todos os pipes
     * 
     * Move todos os pipes para a esquerda para criar
     * o efeito de movimento do jogo.
     * 
     * @param game referencia para o objeto game
     */
    void updatePipes(Game& game);
    
    /**
     * @brief Remove pipes que saíram da tela
     * 
     * Pipes que saem da tela pela esquerda são removidos
     * para economizar memória.
     * 
     * @param game referencia para o objeto game
     */
    void removePipes(Game& game);
    
    /**
     * @brief Verifica colisões entre pássaro e pipes
     * 
     * Se o pássaro bater em um pipe ou sair da tela,
     * o jogo vai para estado GAME_OVER.
     * 
     * @param game referencia para o objeto game
     */
    void checkCollisions(Game& game);
    
    /**
     * @brief Calcula a pontuação do jogador
     * 
     * Aumenta a pontuação quando o pássaro passa por um pipe.
     * Cada pipe vale 1 ponto.
     * 
     * @param game referencia para o objeto game
     */
    void calculateScore(Game& game);
    
    /**
     * @brief Verifica se o jogo acabou
     * 
     * Esta função é chamada quando há colisão.
     * Ela atualiza o high score se necessário.
     * 
     * @param game referencia para o objeto game
     */
    void checkGameOver(Game& game);
    
    /**
     * @brief Reseta o jogo para começar novamente
     * 
     * Limpa a pontuação, pipes e reposiciona o pássaro
     * para o estado inicial.
     * 
     * @param game referencia para o objeto game
     */
    void resetGame(Game& game);
    
    /**
     * @brief Atualiza a melhor pontuação
     * 
     * Se a pontuação atual for maior que a melhor,
     * salva no arquivo "highscore.txt".
     * 
     * @param game referencia para o objeto game
     */
    void updateHighScore(Game& game);

    /**
     * @brief Processa input quando está no menu
     * 
     * - ESPAÇO: inicia o jogo
     * - ESC: sai do jogo
     * 
     * @param game referencia para o objeto game
     */
    void handleMenuInput(Game& game);
    
    /**
     * @brief Processa input durante o jogo
     * 
     * - ESPAÇO: faz o pássaro pular
     * - ESC: sai do jogo
     * 
     * @param game referencia para o objeto game
     */
    void handleGameInput(Game& game);
    
    /**
     * @brief Processa input na tela de game over
     * 
     * - ESPAÇO: volta para o menu
     * - ESC: sai do jogo
     * 
     * @param game referencia para o objeto game
     */
    void handleGameOverInput(Game& game);
    
    /**
     * @brief Processa input quando o jogo está pausado
     * 
     * - P: continua o jogo
     * - ESC: sai do jogo
     * 
     * @param game referencia para o objeto game
     */
    void handlePauseInput(Game& game);
    
    /**
     * @brief Verifica se uma tecla está pressionada
     * 
     * usa a biblioteca Allegro para verificar o estado
     * atual de uma tecla específica.
     * 
     * @param keycode Código da tecla (ex: ALLEGRO_KEY_SPACE)
     * @return true se a tecla está pressionada, false caso contrário
     */
    bool isKeyPressed(int keycode);
    
    /**
     * @brief Verifica se uma tecla foi pressionada apenas uma vez
     * 
     * serve para evitar que uma tecla seja processada
     * várias vezes seguidas.
     * 
     * @param keycode Código da tecla (ex: ALLEGRO_KEY_SPACE)
     * @return true se a tecla foi pressionada uma vez, false caso contrário
     */
    bool isKeyJustPressed(int keycode);

    /**
     * @brief Processa input na tela de cadastro de jogador
     * 
     * @param game é referencia para o objeto game
     */
    void trataCadastroInput(Game& game);

    /**
     * @brief Processa input na tela de seleção de jogador
     * 
     * @param game é referencia para o objeto game
     */
    void trataSelecaoJogadorInput(Game& game);

    /**
     * @brief Processa input na tela de ranking
     * 
     * @param game é referencia para o objeto game
     */
    void trataRankingInput(Game& game);

    /**
     * @brief Processa o cadastro de um jogador
     * 
     * @param game é referencia para o objeto game
     */
    void processarCadastroJogador(Game& game);

    /**
     * @brief Processa a seleção de um jogador
     * 
     * @param game é referencia para o objeto game
     */
    void processarSelecaoJogador(Game& game);

    /**
     * @brief Atualiza as estatísticas do jogador
     * 
     * @param game é referencia para o objeto game
     */
        void atualizarEstatisticasJogador(Game& game);
};

#endif 