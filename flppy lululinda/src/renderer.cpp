#include "../include/renderer.h"

#include "game.h"

#include "raylib.h"

#include <algorithm>

void Renderer::UpdateColors(float colorLevel) {
    const float darkness = 1.0f - colorLevel;
    const float desaturation = std::min(1.0f, darkness / 0.55f);

    for (int i = 0; i < ColorCount; ++i) {
        const float gray =
            0.299f * PinkPalette[i][0] +
            0.587f * PinkPalette[i][1] +
            0.114f * PinkPalette[i][2];

        float r = PinkPalette[i][0] + (gray - PinkPalette[i][0]) * desaturation;
        float g = PinkPalette[i][1] + (gray - PinkPalette[i][1]) * desaturation;
        float b = PinkPalette[i][2] + (gray - PinkPalette[i][2]) * desaturation;

        if (darkness > 0.55f) {
            const float monochromeProgress =
                (darkness - 0.55f) / 0.45f;
            const float monochrome =
                (gray < 150.0f)
                    ? 25.0f + gray * 0.10f
                    : 205.0f + gray * 0.20f;
            r = r + (monochrome - r) * monochromeProgress;
            g = g + (monochrome - g) * monochromeProgress;
            b = b + (monochrome - b) * monochromeProgress;
        }

        colors_[i] = Color{
            static_cast<unsigned char>(r),
            static_cast<unsigned char>(g),
            static_cast<unsigned char>(b),
            255
        };
    }
}

void Renderer::Draw(const Game& game) {
    if (game.State() == GameState::GameOver) {
        DrawGameOver(game);
        return;
    }

    DrawGame(game);
}

void Renderer::DrawGame(const Game& game) {
    ClearBackground(colors_[Sky]);

    DrawKawaiiDecorations();
    DrawDarkAtmosphere(1.0f - game.ColorLevel());

    if (game.State() == GameState::Playing) {
        for (const auto& pipe : game.Pipes()) {
            const int bottomY = pipe.top + game.CurrentPipeOpening();
            const int bottomHeight = Config::GroundY - bottomY;

            DrawRectangle(
                static_cast<int>(pipe.x), 0,
                Config::PipeWidth, pipe.top, colors_[Pipe]);
            DrawRectangleLines(
                static_cast<int>(pipe.x), 0,
                Config::PipeWidth, pipe.top, colors_[PipeBorder]);

            DrawRectangle(
                static_cast<int>(pipe.x), bottomY,
                Config::PipeWidth, bottomHeight, colors_[Pipe]);
            DrawRectangleLines(
                static_cast<int>(pipe.x), bottomY,
                Config::PipeWidth, bottomHeight, colors_[PipeBorder]);
        }
    }

    DrawRectangle(
        0, Config::GroundY,
        Config::ScreenWidth, Config::ScreenHeight - Config::GroundY,
        colors_[Ground]);
    DrawRectangle(
        0, Config::GroundY,
        Config::ScreenWidth, 10, colors_[GroundTop]);

    const int birdX = static_cast<int>(Config::BirdX);
    const int birdY = static_cast<int>(game.BirdY());
    const float birdRadius = Config::BirdRadius;

    DrawCircle(birdX, birdY, birdRadius, colors_[Bird]);
    DrawCircleLines(birdX, birdY, birdRadius, colors_[BirdBorder]);
    DrawCircle(birdX + 6, birdY - 4, 4, WHITE);
    DrawCircle(birdX + 8, birdY - 4, 2, BLACK);
    DrawTriangle(
        Vector2{Config::BirdX + 12, game.BirdY() - 2},
        Vector2{Config::BirdX + 12, game.BirdY() + 6},
        Vector2{Config::BirdX + 22, game.BirdY() + 2},
        colors_[Beak]);

    if (game.State() == GameState::Start) {
        const char* title = "FLAPPY BIRD";
        const char* start = "Aperte ESPACO ou clique";
        const char* startLine = "para comecar";
        const char* highScore = TextFormat("Recorde: %d", game.HighScore());

        DrawText(
            title,
            (Config::ScreenWidth - MeasureText(title, 50)) / 2 + 3,
            133, 50, WHITE);
        DrawText(
            title,
            (Config::ScreenWidth - MeasureText(title, 50)) / 2,
            130, 50, colors_[Text]);
        DrawText(
            start,
            (Config::ScreenWidth - MeasureText(start, 22)) / 2,
            400, 22, colors_[Text]);
        DrawText(
            startLine,
            (Config::ScreenWidth - MeasureText(startLine, 22)) / 2,
            430, 22, colors_[Text]);
        DrawText(
            highScore,
            (Config::ScreenWidth - MeasureText(highScore, 24)) / 2,
            480, 24, colors_[Text]);
    }

    if (game.State() == GameState::Playing) {
        const char* score = TextFormat("%d", game.Score());
        DrawText(
            score,
            (Config::ScreenWidth - MeasureText(score, 60)) / 2 + 3,
            43, 60, WHITE);
        DrawText(
            score,
            (Config::ScreenWidth - MeasureText(score, 60)) / 2,
            40, 60, colors_[Text]);
    }
}

void Renderer::DrawKawaiiDecorations() {
    DrawCloud(65, 105, 0.85f);
    DrawCloud(365, 165, 1.10f);
    DrawCloud(145, 220, 0.65f);
    DrawCloud(425, 320, 0.55f);
}

void Renderer::DrawCloud(int x, int y, float scale) {
    const Color cloud{255, 248, 251, 205};
    const float s = scale;
    DrawEllipse(
        x, y + static_cast<int>(10 * s),
        static_cast<float>(52 * s), static_cast<float>(16 * s), cloud);
    DrawCircle(
        x - static_cast<int>(24 * s),
        y + static_cast<int>(4 * s),
        18 * s, cloud);
    DrawCircle(
        x,
        y - static_cast<int>(5 * s),
        24 * s, cloud);
    DrawCircle(
        x + static_cast<int>(28 * s),
        y + static_cast<int>(3 * s),
        19 * s, cloud);
}

void Renderer::DrawDarkAtmosphere(float darkness) {
    if (darkness <= 0.01f) {
        return;
    }

    const unsigned char shade =
        static_cast<unsigned char>(darkness * 60.0f);

    DrawRectangle(
        0, 0, 18,
        Config::ScreenHeight, Color{35, 35, 38, shade});
    DrawRectangle(
        Config::ScreenWidth - 18, 0, 18,
        Config::ScreenHeight, Color{35, 35, 38, shade});
}

void Renderer::DrawGameOver(const Game& game) {
    ClearBackground(Color{30, 25, 50, 255});

    for (int i = 0; i < 16; ++i) {
        const int x = (i * 97 + 24) % Config::ScreenWidth;
        const int y = 20 + (i * 53) % 220;
        DrawCircle(x, y, i % 4 == 0 ? 3 : 2, WHITE);
    }

    DrawCircle(80, 92, 38, Color{242, 242, 214, 255});
    DrawCircle(96, 82, 34, Color{30, 25, 50, 255});

    DrawRectangle(
        0, 510, Config::ScreenWidth,
        Config::ScreenHeight - 510, Color{45, 82, 58, 255});
    DrawRectangle(
        0, 510, Config::ScreenWidth,
        8, Color{64, 118, 72, 255});

    DrawEllipse(240, 522, 136, 30, Color{82, 58, 42, 255});

    const int graveLeft = 155;
    const int graveTop = 300;
    const int graveWidth = 170;
    DrawRectangle(
        graveLeft, graveTop, graveWidth, 210,
        Color{100, 100, 105, 255});
    DrawCircle(
        graveLeft + graveWidth / 2, graveTop, 85,
        Color{100, 100, 105, 255});
    DrawRectangle(
        graveLeft + 5, graveTop + 5, graveWidth - 10, 205,
        Color{150, 150, 155, 255});
    DrawCircle(
        graveLeft + graveWidth / 2, graveTop + 5, 80,
        Color{150, 150, 155, 255});

    const char* rip = "RIP";
    const char* score = TextFormat("Pontos: %d", game.Score());
    const char* highScore = TextFormat("Recorde: %d", game.HighScore());

    DrawText(
        rip,
        (Config::ScreenWidth - MeasureText(rip, 60)) / 2,
        265, 60, Color{70, 70, 75, 255});
    DrawText(
        score,
        (Config::ScreenWidth - MeasureText(score, 24)) / 2,
        355, 24, Color{70, 70, 75, 255});
    DrawText(
        highScore,
        (Config::ScreenWidth - MeasureText(highScore, 20)) / 2,
        390, 20, Color{70, 70, 75, 255});

    const float birdX = 385.0f;
    const float birdY = 484.0f;
    const float birdRadius = 25.0f;
    DrawCircle(
        static_cast<int>(birdX), static_cast<int>(birdY),
        birdRadius, Color{255, 240, 245, 255});
    DrawCircleLines(
        static_cast<int>(birdX), static_cast<int>(birdY),
        birdRadius, Color{150, 20, 80, 255});

    DrawLineEx(
        Vector2{birdX - 9, birdY - 9},
        Vector2{birdX + 9, birdY + 9},
        3, BLACK);
    DrawLineEx(
        Vector2{birdX + 9, birdY - 9},
        Vector2{birdX - 9, birdY + 9},
        3, BLACK);

    DrawTriangle(
        Vector2{birdX + birdRadius - 2, birdY - 4},
        Vector2{birdX + birdRadius - 2, birdY + 10},
        Vector2{birdX + birdRadius + 16, birdY + 3},
        Color{255, 110, 110, 255});

    DrawEllipseLines(
        static_cast<int>(birdX), static_cast<int>(birdY) - 43,
        20, 6, GOLD);

    const char* endTitle = "FIM DE JOGO";
    const char* returnText = "Aperte ESPACO para voltar";
    const int titleSize = 40;
    DrawText(
        endTitle,
        (Config::ScreenWidth - MeasureText(endTitle, titleSize)) / 2,
        38, titleSize, Color{238, 78, 98, 255});

    if (game.GameOverTime() > 0.5f) {
        DrawText(
            returnText,
            (Config::ScreenWidth - MeasureText(returnText, 22)) / 2,
            570, 22, WHITE);
    }
}
