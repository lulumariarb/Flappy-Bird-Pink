#pragma once

namespace Config {

constexpr int ScreenWidth = 480;
constexpr int ScreenHeight = 640;
constexpr int GroundY = 580;

constexpr float Gravity = 1000.0f;
constexpr float Impulse = -360.0f;
constexpr float InitialPipeSpeed = 150.0f;
constexpr float MaximumPipeSpeed = 240.0f;
constexpr int PipeWidth = 70;
constexpr int InitialPipeOpening = 210;
constexpr int MinimumPipeOpening = 160;
constexpr int PipeDistance = 240;
constexpr float BirdRadius = 14.0f;
constexpr float BirdX = 120.0f;
constexpr float ColorLossPerPipe = 1.0f / 30.0f;
constexpr int DifficultyPointsToMaximum = 30;

constexpr char BackgroundMusicFile[] = "background.ogg";
constexpr float BackgroundMusicVolume = 0.35f;

constexpr int PipeCount = 3;

} // namespace Config
