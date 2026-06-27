#include "audio_manager.hpp"
#include "audio.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

FilePath AudioManager::getAudioFilePath(const Audio& audio) {
    return audio.filePath.string();
}

AudioManager::AudioManager()
{
    // Engine A (system default)
    if (ma_engine_init(NULL, &systemEngine) != MA_SUCCESS)
    {
        std::cout << "Failed system engine\n";
    }

    // Engine B (device engine starts same as system initially)
    if (ma_engine_init(NULL, &deviceEngine) != MA_SUCCESS)
    {
        std::cout << "Failed device engine\n";
    }
}

AudioManager::~AudioManager()
{
    for (auto& [path, audio] : loadedAudios)
    {
        ma_sound_uninit(&audio.speaker);
        ma_sound_uninit(&audio.virtualDevice);
    }

    ma_engine_uninit(&deviceEngine);
    ma_engine_uninit(&systemEngine);
}

bool AudioManager::LoadAudio(const Audio& audio)
{
    FilePath path = audio.filePath.string();

    LoadedAudio& loaded = loadedAudios[path];

    // System engine sound
    if (ma_sound_init_from_file(
        &systemEngine,
        path.c_str(),
        0,
        NULL,
        NULL,
        &loaded.speaker) != MA_SUCCESS)
    {
        std::cout << "System sound load failed\n";
        return false;
    }

    // Device engine sound
    if (ma_sound_init_from_file(
        &deviceEngine,
        path.c_str(),
        0,
        NULL,
        NULL,
        &loaded.virtualDevice) != MA_SUCCESS)
    {
        std::cout << "Device sound load failed\n";
        return false;
    }

    return true;
}

std::vector<std::string> AudioManager::GetAvailableDrivers()
{
    std::vector<std::string> drivers;

    ma_context_config config = ma_context_config_init();
    ma_context context;

    ma_backend backends[] = {
        ma_backend_wasapi,
        ma_backend_dsound,
        ma_backend_winmm
    };

    if (ma_context_init(backends, 3, &config, &context) != MA_SUCCESS)
    {
        std::cout << "Failed to init context for device enumeration\n";
        return drivers;
    }

    ma_device_info* pPlaybackInfos = nullptr;
    ma_uint32 count = 0;

    if (ma_context_get_devices(
            &context,
            &pPlaybackInfos,
            &count,
            NULL,
            NULL) != MA_SUCCESS)
    {
        std::cout << "Failed to get devices\n";
        ma_context_uninit(&context);
        return drivers;
    }

    // Copy all device infos into our owned vector before the context is destroyed.
    // selectedDeviceID will point into this vector, so it stays valid.
    playbackDevices.assign(pPlaybackInfos, pPlaybackInfos + count);

    // Reset selectedDeviceID — old pointer is about to become invalid
    selectedDeviceID = nullptr;

    for (auto& device : playbackDevices)
        drivers.emplace_back(device.name);

    ma_context_uninit(&context); // safe: data is already copied into playbackDevices
    return drivers;
}

void AudioManager::SetAudioDriver(unsigned int index)
{
    if (index >= playbackDevices.size())
    {
        std::cout << "Invalid device index\n";
        return;
    }

    // Point into our owned vector — stays valid as long as playbackDevices isn't resized
    selectedDeviceID = &playbackDevices[index].id;

    ma_engine_uninit(&deviceEngine);

    ma_engine_config config = ma_engine_config_init();
    config.pPlaybackDeviceID = selectedDeviceID;

    if (ma_engine_init(&config, &deviceEngine) != MA_SUCCESS)
    {
        std::cout << "Failed device engine init\n";
        selectedDeviceID = nullptr;
        return;
    }
}

void AudioManager::PlayMALoadedAudio(LoadedAudio& audio, const float volume)
{
    ma_sound_set_volume(&audio.speaker, volume);
    ma_sound_seek_to_pcm_frame(&audio.speaker, 0);
    ma_sound_start(&audio.speaker);

    ma_sound_set_volume(&audio.virtualDevice, volume);
    ma_sound_seek_to_pcm_frame(&audio.virtualDevice, 0);
    ma_sound_start(&audio.virtualDevice);
}

bool AudioManager::PlayAudio(const Audio& audio)
{
    FilePath audioFilePath = getAudioFilePath(audio);

    if (loadedAudios.find(audioFilePath) == loadedAudios.end())
    {
        if (!LoadAudio(audio))
            return false;
    }

    LoadedAudio& loadedAudio = loadedAudios[audioFilePath];
    PlayMALoadedAudio(loadedAudio, audio.volume * masterVolume);
    return true;
}