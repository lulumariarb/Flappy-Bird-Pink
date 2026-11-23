#pragma once

#include "game.h"

#include "raylib.h"

class Renderer {
public:
    void UpdateColors(float colorLevel);
    void Draw(const Game& game);

private:
    enum ColorName {
        Sky,
        Pipe,
        PipeBorder,
        Ground,
        GroundTop,
        Bird,
        BirdBorder,
        Beak,
        Text,
        ColorCount
    };

    static constexpr int PinkPalette[ColorCount][3] = {
        {255, 190, 215},
        {225, 80, 140},
        {120, 20, 70},
        {170, 60, 110},
        {110, 20, 60},
        {255, 240, 245},
        {150, 20, 80},
        {255, 110, 110},
        {130, 25, 75}
    };

    Color colors_[ColorCount]{};

    void DrawGame(const Game& game);
    void DrawGameOver(const Game& game);
    void DrawKawaiiDecorations();
    void DrawDarkAtmosphere(float darkness);
    void DrawCloud(int x, int y, float scale = 1.0f);
};
