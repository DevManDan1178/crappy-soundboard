#pragma once
#include "../audio/audio.hpp"
#include <nlohmann/json.hpp>

struct ConfigData {
    std::vector<std::vector<Audio>> audioTable;
};

class ConfigManager {
public:
    void WriteToJSON();
    ConfigData ReadFromJSON();

private:
    nlohmann::json AudioToJSON(const Audio& audio);
    Audio JSONToAudio(const nlohmann::json& json);
};