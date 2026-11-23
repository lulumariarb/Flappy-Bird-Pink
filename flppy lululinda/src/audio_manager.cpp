#include "../include/audio_manager.h"

#include "../include/config.h"

#include "raylib.h"

#include <string>

bool AudioManager::Initialize() {
    InitAudioDevice();
    audioDeviceReady_ = IsAudioDeviceReady();
    if (!audioDeviceReady_) {
        TraceLog(LOG_WARNING, "Audio device unavailable; continuing without music.");
        return false;
    }

    const std::string musicPath =
        std::string(GetApplicationDirectory()) +
        "../assets/audio/" + Config::BackgroundMusicFile;

    if (!FileExists(musicPath.c_str())) {
        TraceLog(
            LOG_INFO,
            "Background music not found at %s; add a soundtrack to enable it.",
            musicPath.c_str());
        return true;
    }

    backgroundMusic_ = LoadMusicStream(musicPath.c_str());
    if (!IsMusicValid(backgroundMusic_)) {
        TraceLog(
            LOG_WARNING,
            "Could not load background music: %s",
            musicPath.c_str());
        return false;
    }

    backgroundMusic_.looping = true;
    SetMusicVolume(backgroundMusic_, Config::BackgroundMusicVolume);
    PlayMusicStream(backgroundMusic_);
    musicLoaded_ = true;
    return true;
}

void AudioManager::Update() {
    if (musicLoaded_) {
        UpdateMusicStream(backgroundMusic_);
    }
}

void AudioManager::Shutdown() {
    if (musicLoaded_) {
        StopMusicStream(backgroundMusic_);
        UnloadMusicStream(backgroundMusic_);
        musicLoaded_ = false;
    }

    if (audioDeviceReady_) {
        CloseAudioDevice();
        audioDeviceReady_ = false;
    }
}
