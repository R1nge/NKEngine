//
// Created by r1nge on 11/5/25.
//

#include "NKAudioPlayer.h"

bool NKAudioPlayer::LoadMusic(const char *path, std::string songTitle) {
    auto music = Mix_LoadMUS(path);
    if (music == nullptr) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    _music.emplace(songTitle, music);

    return true;
}

bool NKAudioPlayer::PlayMusic(std::string songTitle) {
    if (_music.contains(songTitle)) {
        Mix_PlayMusic(_music.at(songTitle), -1);
        return true;
    }
    printf("Failed to play music!");
    return false;
}

void NKAudioPlayer::SetMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}
