#pragma once
#include "audio.hpp"
#include "miniaudio.h"
#include <unordered_map>
#include <string>
#include <vector>

using FilePath = std::string;

struct LoadedAudio { 
    ma_sound speaker;
    ma_sound virtualDevice;
};

class AudioManager {
public:
    
    float masterVolume = 1.0f;

    AudioManager();
    ~AudioManager();
    
    /**
     * @brief loads the audio
     * @param audio the audio to load
     * @return if it was successful or not
     */
    bool LoadAudio(const Audio& audio);

    /**
     * @brief plays the audio (and loads it first if it is not loaded)
     * (if not loaded) Calls LoadAudio with the audio
     * Calls PlayMALoadedAudio with the loaded sound at the audio's volume
     * @param audio the audio to play
     * @return if it was successful or not
     */
    bool PlayAudio(const Audio& audio);
    
    std::vector<std::string> GetAvailableDrivers();

    void SetAudioDriver(unsigned int driverIndex);

    FilePath getAudioFilePath(const Audio& audio);

private:
    ma_engine systemEngine{};
    ma_engine deviceEngine{};

    // Owned copies of device infos — safe to keep after context is destroyed
    std::vector<ma_device_info> playbackDevices;

    // Points into playbackDevices — valid as long as playbackDevices is not resized
    ma_device_id* selectedDeviceID = nullptr;

    std::unordered_map<FilePath, LoadedAudio> loadedAudios;

    /**
     * @brief plays loaded MiniAudio sound 
     * @param audio the loaded audio
     * @param volume the volume to play it at
     */
    void PlayMALoadedAudio(LoadedAudio& audio, const float volume = 1.0f);
};