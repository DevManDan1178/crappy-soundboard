#pragma once
#include "audio.hpp"
#include "miniaudio.h"
#include <unordered_map>
#include <string>

using FilePath = std::string;

class AudioManager {
public:
    ma_engine engine;

    AudioManager();
    ~AudioManager();
    
     /**
     * @brief loads the audio
     * @param audio the audio to load
     * @return if it was successful or not
     */
    bool LoadAudio(Audio audio);
    /**
     * @brief plays the audio (and loads it first if it is not loaded)
     * (if not loaded) Calls LoadAudio with the audio
     * Calls PlayMASound with the loaded sound at the audio's volume
     * @param audio the audio to play
     * @return if it was successful or not
     */
    bool PlayAudio(Audio audio);

    FilePath getAudioFilePath(Audio audio);

private:
    std::unordered_map<FilePath, ma_sound> loadedAudios;
    /**
     * @brief plays loaded MiniAudio sound 
     * @param sound the loaded sound
     * @param volume the volume to play it at
     */
    void PlayMASound(ma_sound& sound, float volume = 1.0f);
};