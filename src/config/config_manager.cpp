#include "config/config_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

const char* PATH_KEY = "path";
const char* VOLUME_KEY = "volume";

void ConfigManager::WriteToJSON() {
    
}

ConfigData ConfigManager::ReadFromJSON() {
    ConfigData data;
    

    return data;
}

json ConfigManager::AudioToJSON(const Audio &audio) {
    return {
        {PATH_KEY, audio.filePath.string()},
        {VOLUME_KEY, audio.volume}
    };
}

Audio ConfigManager::JSONToAudio(const json &json) {
    std::filesystem::path path(json[PATH_KEY].get<std::string>());
    float volume = json[VOLUME_KEY].get<float>();

    return Audio(path, volume);
}