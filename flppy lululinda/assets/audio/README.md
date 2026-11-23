# Musica de fundo

Coloque nesta pasta a trilha do jogo com o nome `background.ogg`.

A trilha `backgroundmsc.mp4` foi convertida para `background.ogg`; o arquivo
MP4 original continua salvo em `Downloads`.

O jogo carrega o arquivo em streaming, repete a musica e ajusta o volume em
`include/config.h`. Se o arquivo nao existir ou nao puder ser carregado, o
jogo continua sem musica e registra o motivo no log.

Para usar outro nome ou formato aceito pela raylib, atualize
`Config::BackgroundMusicFile` em `include/config.h`.


