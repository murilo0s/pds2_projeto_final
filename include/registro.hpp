#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Jogador {

private:
        string nome;
        int pontuacao;
public:        
        Jogador (string nome , int pontuacao ):
        nome (nome), pontuacao (pontuacao){}

        string getNome() const{
                return nome;

        }
        int getPontuacao() const{
                return pontuacao;
        }
void setPontuacao (int novaPontuacao){
        pontuacao=novaPontuacao;
}

;}




;