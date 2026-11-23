#include "../include/game.h"

#include "raylib.h"

#include <algorithm>
#include <cmath>

void Game::Start() {
    if (state_ == GameState::Start) {
        BeginRun();
    } else if (state_ == GameState::Playing) {
        velocityY_ = Config::Impulse;
    }
}

void Game::ResetAfterGameOver() {
    colorLevel_ = 1.0f;
    state_ = GameState::Start;
}

void Game::Update(float deltaTime) {
    if (state_ == GameState::Start) {
        birdY_ = 300.0f + sinf(static_cast<float>(GetTime()) * 4.0f) * 10.0f;
        return;
    }

    if (state_ == GameState::GameOver) {
        gameOverTime_ += deltaTime;
        return;
    }

    velocityY_ += Config::Gravity * deltaTime;
    birdY_ += velocityY_ * deltaTime;

    if (birdY_ < Config::BirdRadius) {
        birdY_ = Config::BirdRadius;
        velocityY_ = 0.0f;
    }

    float targetColor =
        1.0f - score_ * Config::ColorLossPerPipe;
    targetColor = std::max(0.0f, targetColor);
    colorLevel_ += (targetColor - colorLevel_) * 3.0f * deltaTime;

    for (Pipe& pipe : pipes_) {
        pipe.x -= CurrentPipeSpeed() * deltaTime;

        if (pipe.x + Config::PipeWidth < 0) {
            pipe.x += 3 * Config::PipeDistance;
            SpawnPipe(pipe);
        }

        if (!pipe.passed && pipe.x + Config::PipeWidth < Config::BirdX) {
            pipe.passed = true;
            ++score_;
        }
    }

    if (HasCollision()) {
        highScore_ = std::max(highScore_, score_);
        gameOverTime_ = 0.0f;
        state_ = GameState::GameOver;
    }
}

void Game::BeginRun() {
    birdY_ = 300.0f;
    velocityY_ = Config::Impulse;
    score_ = 0;
    colorLevel_ = 1.0f;

    for (int i = 0; i < Config::PipeCount; ++i) {
        pipes_[i].x =
            static_cast<float>(Config::ScreenWidth + i * Config::PipeDistance);
        SpawnPipe(pipes_[i]);
    }

    state_ = GameState::Playing;
}

void Game::SpawnPipe(Pipe& pipe) {
    const int opening = CurrentPipeOpening();
    pipe.top = GetRandomValue(
        80,
        Config::GroundY - opening - 80);
    pipe.passed = false;
}

bool Game::HasCollision() {
    for (const Pipe& pipe : pipes_) {
        const Rectangle topPipe = {
            pipe.x,
            0.0f,
            static_cast<float>(Config::PipeWidth),
            static_cast<float>(pipe.top)
        };
        const Rectangle bottomPipe = {
            pipe.x,
            static_cast<float>(pipe.top + CurrentPipeOpening()),
            static_cast<float>(Config::PipeWidth),
            static_cast<float>(
                Config::GroundY - (pipe.top + CurrentPipeOpening()))
        };
        const Vector2 birdCenter = { Config::BirdX, birdY_ };

        if (CheckCollisionCircleRec(birdCenter, Config::BirdRadius, topPipe) ||
            CheckCollisionCircleRec(birdCenter, Config::BirdRadius, bottomPipe)) {
            return true;
        }
    }

    return birdY_ + Config::BirdRadius >= Config::GroundY;
}

GameState Game::State() const {
    return state_;
}

float Game::BirdY() const {
    return birdY_;
}

int Game::Score() const {
    return score_;
}

int Game::HighScore() const {
    return highScore_;
}

float Game::ColorLevel() const {
    return colorLevel_;
}

float Game::GameOverTime() const {
    return gameOverTime_;
}

float Game::CurrentPipeSpeed() const {
    const float progress =
        std::clamp(
            static_cast<float>(score_) /
            static_cast<float>(Config::DifficultyPointsToMaximum),
            0.0f,
            1.0f);
    return Config::InitialPipeSpeed +
        (Config::MaximumPipeSpeed - Config::InitialPipeSpeed) * progress;
}

int Game::CurrentPipeOpening() const {
    const float progress =
        std::clamp(
            static_cast<float>(score_) /
            static_cast<float>(Config::DifficultyPointsToMaximum),
            0.0f,
            1.0f);
    return static_cast<int>(
        Config::InitialPipeOpening +
        (Config::MinimumPipeOpening - Config::InitialPipeOpening) * progress);
}

const std::array<Pipe, Config::PipeCount>& Game::Pipes() const {
    return pipes_;
}
