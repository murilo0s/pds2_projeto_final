# Jogo Flappy Bird PDS2

### Equipe
- Murilo Felipe dos Santos Ferreira
- Guilherme Henrique Morangon Gaspar
- Marcelo Areal 
- Julia Natalie
- Samuel Abner


### Descrição do Projeto
O Jogo Flappy Bird PDS é uma aplicação desenvolvida como trabalho final da disciplina de Programação e Desenvolvimento de Software II (PDS II) do curso de Sistemas de Informação na UFMG. Este projeto implementa uma versão completa do clássico jogo Flappy Bird, proporcionando funcionalidades como sistema de cadastro de jogadores, ranking de pontuações, persistência de dados e uma interface gráfica completa.

### Contexto do Projeto
O projeto visa demonstrar os conceitos de programação orientada a objetos em C++, implementando um jogo completo com sistema de gerenciamento de jogadores, persistência de dados e interface gráfica. Aborda desafios comuns no desenvolvimento de jogos como controle de colisões, renderização gráfica, gerenciamento de estados e armazenamento de dados.

### Equipe
* **

### Tecnologias Utilizadas
* **Linguagem de Programação**: C++
* **Biblioteca Gráfica**: Allegro 5
* **Compilação**: Makefile
* **Documentação**: Doxygen
* **Testes**: Framework de testes unitários
* **Controle de Versão**: Git e GitHub

### Estrutura do Projeto
O projeto é organizado em classes, cada uma responsável por aspectos específicos do jogo:
* **`Game`**: Classe principal que gerencia o loop do jogo e os estados.
* **`GameRenderer`**: Responsável pela renderização gráfica.
* **`GameLogic`**: Implementa a lógica do jogo, incluindo colisões.
* **`Bird`**: Representa o pássaro controlado pelo jogador.
* **`Pipe`**: Representa os obstáculos (canos).
* **`Player`**: Gerencia informações de cada jogador.
* **`PlayerManager`**: Sistema de gerenciamento de jogadores.
* **`GameObject`**: Classe base para objetos do jogo.

### Funcionalidades Principais
* **Sistema de Jogadores**: Cadastro, seleção e persistência de dados dos jogadores.
* **Sistema de Jogo**: Controles intuitivos (espaço para pular), física, geração dinâmica de obstáculos e sistema de pontuação.
* **Sistema de Ranking**: Exibe os melhores jogadores ordenados por pontuação e mantém histórico de partidas.
* **Interface do Usuário**: Menu principal, menu do jogador, tela de "Game Over" e feedback visual para o usuário.

### Funcionalidades Extras
* **Sistema de Estados**: Gerenciamento completo das diferentes telas do jogo.
* **Tratamento de Exceções**: Sistema robusto para tratamento de erros.
* **Interface Responsiva**: Adaptação para diferentes resoluções.
* **Sistema de Fontes**: Uso de múltiplas fontes na interface.
* **Persistência de High Score**: Armazenamento da melhor pontuação global.

### Como Jogar
1.  **Iniciar o Jogo**: Execute o arquivo compilado.
2.  **Cadastrar Jogador**: Na primeira vez, cadastre um jogador.
3.  **Selecionar Jogador**: Escolha um jogador para a partida.
4.  **Controles**: Pressione `ESPAÇO` para fazer o pássaro pular.
5.  **Objetivo**: Atravessar o máximo de canos possível sem colidir.

### Compilação e Execução
* **Pré-requisitos**: Compilador C++ (GCC/G++), Biblioteca Allegro 5, Make.
* **Compilação**: `make`
* **Execução**: `make run`
* **Testes**: `make tests` e `make test-run`
* **Limpeza**: `make clean`

### Estrutura de Arquivos

pds2_projeto_final/
├── src/            # Código fonte
├── include/        # Headers
├── assets/         # Recursos (imagens, fontes)
├── tests/          # Testes unitários
├── bin/            # Arquivos compilados
├── obj/            # Objetos intermediários
├── Makefile        # Script de compilação
└── README.md       # Este arquivo


### Aprendizados
Este projeto foi uma oportunidade para aprimorar habilidades em programação orientada a objetos com C++, desenvolvimento de jogos com bibliotecas gráficas, gerenciamento de estados, persistência de dados, tratamento de exceções, uso de Makefile, testes unitários e colaboração em equipe.

### Principais Dificuldades
* **Interface Gráfica**: A criação das telas de menu, cadastro de jogadores e ranking exigiu um esforço considerável para garantir uma boa experiência ao usuário.
* **Refatoração da Classe `Game`**: A classe `Game` tornou-se muito extensa, sendo necessário dividi-la para separar a lógica da renderização, melhorando a organização do código.
* **Implementação de Testes**: Garantir uma cobertura de testes adequada para a lógica do jogo e a interação entre os componentes foi um desafio.
* **Gerenciamento de Versão com Git**: Ocorreram conflitos de `merge` entre os commits, o que demandou atenção e, por vezes, soluções "gambiarras" para unificar o trabalho da equipe.
* **Aplicação de POO**: Integrar múltiplos conceitos de Programação Orientada a Objetos e definir as melhores abordagens de implementação foi um desafio, especialmente por ser o primeiro projeto de grande porte da equipe.
* **Comunicação entre Classes**: Inicialmente, a interação entre as classes não funcionava como esperado, exigindo ajustes nos métodos e na arquitetura geral ao longo do desenvolvimento.

### Documentação
A documentação detalhada do projeto, gerada com Doxygen, está na pasta `documentation/`. Ela inclui detalhes sobre as classes, métodos e a arquitetura geral do sistema.
