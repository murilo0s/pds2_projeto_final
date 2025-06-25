# Cartões CRC - Projeto Flappy Bird PDS2

## Cartão CRC 1: Game

### Classe
**Game**

### Responsabilidades
- Gerenciar o loop principal do jogo
- Controlar os estados do jogo (MENU, PLAYING, GAME_OVER, etc.)
- Inicializar e gerenciar componentes Allegro (display, timer, fontes)
- Coordenar a comunicação entre GameRenderer e GameLogic
- Gerenciar entrada do usuário (teclado)
- Controlar o fluxo de execução do jogo
- Manter pontuação atual e high score
- Gerenciar seleção e cadastro de jogadores
- Controlar interface de menus e telas

### Colaboradores
- **GameRenderer**: Delega a renderização
- **GameLogic**: Delega a lógica do jogo
- **PlayerManager**: Gerencia jogadores
- **Bird**: Objeto controlado pelo jogador
- **Pipe**: Obstáculos do jogo
- **Player**: Informações do jogador atual

---

## Cartão CRC 2: GameRenderer

### Classe
**GameRenderer**

### Responsabilidades
- Renderizar todos os elementos gráficos do jogo
- Desenhar o pássaro na tela
- Desenhar os canos (pipes)
- Renderizar interface de usuário (menus, pontuação)
- Exibir telas de cadastro e seleção de jogadores
- Mostrar tela de game over
- Renderizar ranking de jogadores
- Gerenciar diferentes fontes e tamanhos de texto
- Exibir feedback visual para o usuário

### Colaboradores
- **Game**: Recebe informações sobre estado e objetos
- **Bird**: Obtém posição e estado para renderização
- **Pipe**: Obtém posição e estado para renderização
- **PlayerManager**: Obtém dados dos jogadores para ranking

---

## Cartão CRC 3: GameLogic

### Classe
**GameLogic**

### Responsabilidades
- Implementar a lógica de jogo
- Verificar colisões entre objetos
- Atualizar posições dos objetos
- Gerar novos canos dinamicamente
- Calcular pontuação
- Gerenciar física do pássaro (gravidade, pulo)
- Verificar condições de game over
- Processar entrada do usuário durante o jogo
- Controlar velocidade e dificuldade

### Colaboradores
- **Game**: Recebe estado atual e objetos
- **Bird**: Atualiza posição e estado
- **Pipe**: Atualiza posição e verifica colisões
- **PlayerManager**: Atualiza pontuação do jogador

---

## Cartão CRC 4: GameObject

### Classe
**GameObject** (Classe Base Abstrata)

### Responsabilidades
- Definir interface comum para objetos do jogo
- Gerenciar posição (x, y) dos objetos
- Controlar dimensões (width, height)
- Gerenciar velocidade (speedX, speedY)
- Fornecer métodos para movimento
- Verificar se objeto saiu da tela
- Definir interface para colisões
- Fornecer getters e setters para atributos

### Colaboradores
- **Bird**: Herda de GameObject
- **Pipe**: Herda de GameObject

---

## Cartão CRC 5: Bird

### Classe
**Bird**

### Responsabilidades
- Representar o pássaro controlado pelo jogador
- Implementar física do pássaro (gravidade, pulo)
- Responder a comandos do jogador
- Verificar colisões com canos
- Manter estado de vida/morte
- Renderizar sprite do pássaro
- Atualizar animação do pássaro

### Colaboradores
- **GameObject**: Herda funcionalidades básicas
- **Game**: Recebe comandos do jogador
- **Pipe**: Verifica colisões
- **GameRenderer**: Fornece dados para renderização

---

## Cartão CRC 6: Pipe

### Classe
**Pipe**

### Responsabilidades
- Representar os canos (obstáculos) do jogo
- Mover-se da direita para a esquerda
- Verificar colisões com o pássaro
- Gerar aberturas aleatórias para passagem
- Manter posição e dimensões
- Renderizar sprite dos canos
- Identificar quando saiu da tela

### Colaboradores
- **GameObject**: Herda funcionalidades básicas
- **Bird**: Verifica colisões
- **GameLogic**: Recebe comandos de movimento
- **GameRenderer**: Fornece dados para renderização

---

## Cartão CRC 7: Player

### Classe
**Player**

### Responsabilidades
- Armazenar informações de um jogador
- Manter nome e apelido do jogador
- Controlar pontuação máxima
- Contar total de partidas jogadas
- Atualizar estatísticas do jogador
- Fornecer acesso aos dados do jogador
- Imprimir informações do jogador

### Colaboradores
- **PlayerManager**: É gerenciado por PlayerManager
- **Game**: Fornece dados do jogador atual

---

## Cartão CRC 8: PlayerManager

### Classe
**PlayerManager**

### Responsabilidades
- Gerenciar coleção de jogadores
- Cadastrar novos jogadores
- Remover jogadores existentes
- Salvar dados em arquivo
- Carregar dados do arquivo
- Ordenar ranking de jogadores
- Exibir lista de jogadores
- Fornecer acesso aos jogadores
- Identificar melhor jogador

### Colaboradores
- **Player**: Gerencia objetos Player
- **Game**: Fornece interface para gerenciamento
- **GameRenderer**: Fornece dados para ranking

---

## Diagrama de Relacionamentos

```
Game
├── GameRenderer (delega renderização)
├── GameLogic (delega lógica)
├── PlayerManager (gerencia jogadores)
├── Bird (objeto do jogo)
└── Pipe (objeto do jogo)

GameObject (classe base)
├── Bird (herda)
└── Pipe (herda)

PlayerManager
└── Player (gerencia)

GameRenderer
├── Bird (renderiza)
├── Pipe (renderiza)
└── PlayerManager (exibe ranking)

GameLogic
├── Bird (atualiza)
└── Pipe (atualiza)