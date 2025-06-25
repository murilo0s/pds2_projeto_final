#include "game.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::runtime_error& e) {
        std::cerr << "ERRO CRÍTICO: " << e.what() << std::endl;
        std::cerr << "O jogo não pode continuar. Verifique se todos os arquivos necessários estão presentes." << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Erro desconhecido ocorreu." << std::endl;
        return -1;
    }
    return 0;
}

