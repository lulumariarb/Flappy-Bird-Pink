#pragma once

#include "config.h"

#include "raylib.h"

#include <array>

enum class GameState {
    Start,
    Playing,
    GameOver
};

struct Pipe {
    float x = 0.0f;
    int top = 200;
    bool passed = false;
};

class Game {
public:
    void Start();
    void Update(float deltaTime);
    void ResetAfterGameOver();

    [[nodiscard]] GameState State() const;
    [[nodiscard]] float BirdY() const;
    [[nodiscard]] int Score() const;
    [[nodiscard]] int HighScore() const;
    [[nodiscard]] float ColorLevel() const;
    [[nodiscard]] float GameOverTime() const;
    [[nodiscard]] float CurrentPipeSpeed() const;
    [[nodiscard]] int CurrentPipeOpening() const;
    [[nodiscard]] const std::array<Pipe, Config::PipeCount>& Pipes() const;

private:
    void BeginRun();
    void SpawnPipe(Pipe& pipe);
    bool HasCollision();

    GameState state_ = GameState::Start;
    float birdY_ = 300.0f;
    float velocityY_ = 0.0f;
    std::array<Pipe, Config::PipeCount> pipes_{};
    int score_ = 0;
    int highScore_ = 0;
    float colorLevel_ = 1.0f;
    float gameOverTime_ = 0.0f;
};
