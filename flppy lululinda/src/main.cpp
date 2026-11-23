#include "../include/config.h"
#include "../include/audio_manager.h"
#include "../include/game.h"
#include "../include/renderer.h"

#include "raylib.h"

int main() {
    InitWindow(Config::ScreenWidth, Config::ScreenHeight, "Flappy Bird");
    SetTargetFPS(60);

    AudioManager audio;
    audio.Initialize();

    Game game;
    Renderer renderer;

    while (!WindowShouldClose()) {
        const float deltaTime = GetFrameTime();
        audio.Update();
        const bool pressed =
            IsKeyPressed(KEY_SPACE) ||
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        game.Update(deltaTime);

        if (pressed) {
            if (game.State() == GameState::Start) {
                game.Start();
            } else if (game.State() == GameState::GameOver && game.GameOverTime() > 0.5f) {
                game.ResetAfterGameOver();
            } else if (game.State() == GameState::Playing) {
                game.Start();
            }
        }

        renderer.UpdateColors(game.ColorLevel());

        BeginDrawing();
        renderer.Draw(game);
        EndDrawing();
    }

    audio.Shutdown();
    CloseWindow();
    return 0;
}
