#pragma once

#include "raylib.h"

class AudioManager {
public:
    bool Initialize();
    void Update();
    void Shutdown();

private:
    Music backgroundMusic_{};
    bool audioDeviceReady_ = false;
    bool musicLoaded_ = false;
};
