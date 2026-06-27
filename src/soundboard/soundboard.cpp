#include "soundboard/soundboard.hpp"
#include <optional>


bool Soundboard::PlayAudio(unsigned int tableIndex, unsigned int index, bool ignoreVirtualDevice) {
    std::optional<Audio> audio = audioTable.GetAudio(tableIndex, index);
    if (audio.has_value()) {
        audioManager.PlayAudio(*audio, ignoreVirtualDevice);
        return true;
    }
    return false;
}

unsigned int Soundboard::AudioTableSize() {
    return audioTable.size();
}

std::vector<Audio>* Soundboard::GetAudiosAtIndex(unsigned int index) {
    if (index >= AudioTableSize()) {
        return {};
    }
    return audioTable.GetAudiosAtIdx(index);
}


void Soundboard::StopAllAudio() {
    audioManager.StopAllAudio();
}