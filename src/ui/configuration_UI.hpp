#pragma once
#include "config/config_manager.hpp"
#include "soundboard/soundboard.hpp"

namespace ConfigurationUI {
    void Render(Soundboard& soundboard);

    void RenderAudioConfigurations(Soundboard& soundboard);
    void RenderHotkeyConfigurations(Soundboard& soundboard);
}