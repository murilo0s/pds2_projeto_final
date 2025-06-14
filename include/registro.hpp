#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Player {

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

//Funções para o rank de jogadores

void salvarRankingEmArquivo(const std::vector<Jogador>& ranking, const std::string& nomeArquivo);
void carregarRankingDoArquivo(std::vector<Jogador>& ranking, const std::string& nomeArquivo);
void ordenarRanking(std::vector<Jogador>& ranking);
void exibirRanking(const std::vector<Jogador>& ranking);
;};
//Uso de "jogador".
//Leitura e persistência dos dados do vetor "jogador".
void salvarRankingEmArquivo(const std::vector<Jogador>& ranking, const std::string& nomeArquivo)
{
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita.\n";
        return;
    }

    for (const auto& jogador : ranking) {
        arquivo << jogador.getNome() << " " << jogador.getPontuacao() << "\n";
    }

    arquivo.close();
}


;
#endif
