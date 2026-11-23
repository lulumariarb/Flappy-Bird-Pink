## Flappy-Bird-Pink
Jogo 2D em linguagem C++, ultizizando biblioteca Raylib.
<img width="473" height="654" alt="image" src="https://github.com/user-attachments/assets/29cb24c0-153e-41de-9783-e7d142bc9a93" />

##Integrantes 
Luiza Maria Ribeiro Barbosa - RA: 26038023
Sofia Real Prado Coraiola Fontes - RA: 26044823

## Compilar no Windows

Com MinGW e raylib configurados:

```powershell
cmake -S . -B build -G "Ninja"
cmake --build build
```

Executar:
Apertar F5


##Como jogar
- O controle do jogo é feito pelo click do mouse ou pela tecla ESPAÇO .
- O objetivo é passar ao máximo pelos canos sem bater.


##Uso da IA
- Ultilizamos para o código bruto
- Auxílio na ataualização do código quando ele não estava rodando.

## Estrutura

- `include/config.h`: dimensoes, fisica e ajustes visuais do jogo.
- `include/game.h`: interface do estado e das regras do jogo.
- `src/game.cpp`: atualizacao, pontuacao e colisao.
- `include/renderer.h`: interface da renderizacao.
- `src/renderer.cpp`: desenho das telas e da paleta.
- `include/audio_manager.h` e `src/audio_manager.cpp`: carregamento, loop e liberacao da musica.
- `src/main.cpp`: inicializacao da janela e loop principal.
- `assets/audio/`: local para arquivos de audio do jogo.

## Musica de fundo

Coloque sua trilha em `assets/audio/background.ogg`. O jogo a reproduz em loop com volume inicial configuravel em `include/config.h`. Se a trilha nao estiver presente ou nao puder ser carregada, o jogo continua sem musica e registra um aviso no log.

## Dificuldade

A dificuldade aumenta gradualmente com a pontuacao:

- Comeca com velocidade de 150 e abertura de 210 pixels.
- Evolui de forma suave ate 240 de velocidade e 160 de abertura.
- A dificuldade maxima e atingida aos 30 pontos.
- O espaco entre os canos continua constante para manter o jogo justo.

## Estetica

- Inicio em rosa claro com nuvens, detalhes fofos e um passarinho branco.
- A paleta muda gradualmente para tons escuros e vermelhos assustadores.
- Aos poucos aparecem sombras e bordas escuras.
- A tela de morte mantem uma lapide, cova, passaro com olhos em X e laço rasgado.

