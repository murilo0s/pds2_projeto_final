#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>

using namespace std;

// definir classe jogador
class Player {
private:
    string nome;             ///< Nome do jogador 
    string apelido;          ///< Apelido (nick) do jogador 
    int pontuacao_max;       ///< Pontuação máxima alcançada pelo jogador 
    int total_partidas;      ///< Total de partidas jogadas pelo jogador 

public:
    /**
     * @brief Construtor para novos cadastros.
     * 
     * @param _nome Nome do jogador.
     * @param _apelido Apelido (nick) do jogador.
     */
    Player(string _nome, string _apelido);

    /**
     * @brief Construtor para recuperar cadastros do arquivo.
     * 
     * @param _nome Nome do jogador.
     * @param _apelido Apelido (nick) do jogador.
     * @param _pontuacao_max Pontuação máxima alcançada pelo jogador.
     * @param _total_partidas Total de partidas jogadas pelo jogador.
     */
    Player(string _nome, string _apelido, int _pontuacao_max, int _total_partidas);

    /**
     * @brief Incrementa o número total de partidas jogadas.
     * 
     * @return Novo total de partidas após incremento.
     */
    int incrementar_partidas();

    /**
     * @brief Atualiza a pontuação máxima, caso a atual seja maior que a anterior.
     * 
     * @param pontuacao_atual Pontuação obtida na partida mais recente.
     */
    void update_pontuacao_max(int pontuacao_atual);

    /**
     * @brief Obtém o nome do jogador.
     * 
     * @return Nome do jogador.
     */
    string getNome() const;

    /**
     * @brief Obtém o apelido (nick) do jogador.
     * 
     * @return Apelido do jogador.
     */
    string getApelido() const;

    /**
     * @brief Obtém a pontuação máxima registrada.
     * 
     * @return Pontuação máxima.
     */
    int getPonto_max() const;

    /**
     * @brief Obtém o total de partidas jogadas.
     * 
     * @return Número total de partidas.
     */
    int getTotal_partidas() const;

    /**
     * @brief Imprime os dados do jogador no console.
     */
    void imprimir_jogador();
};

#endif