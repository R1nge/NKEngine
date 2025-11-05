//
// Created by r1nge on 11/5/25.
//

#include "NKAudioPlayer.h"
//TODO: override music(unload, load new)
bool NKAudioPlayer::LoadMusic(const char *path, std::string songTitle) {
    auto music = Mix_LoadMUS(path);
    if (music == nullptr) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    _music[songTitle] = music;

    return true;
}

void NKAudioPlayer::UnloadMusic(std::string songTitle) {
    if (_music.size() > 0) {
        auto music = _music.at(songTitle);
        if (music != nullptr) {
            Mix_FreeMusic(music);
            _music.erase(songTitle);
        }
    }
}

bool NKAudioPlayer::PlayMusic(std::string songTitle) {
    if (_music.contains(songTitle)) {
        Mix_PlayMusic(_music.at(songTitle), -1);
        return true;
    }
    printf("Failed to play music!");
    return false;
}

void NKAudioPlayer::PauseMusic() {
    printf("Music has been paused");
    Mix_PauseMusic();
}

void NKAudioPlayer::ResumeMusic() {
    printf("Music has been resumed");
    Mix_ResumeMusic();
}

void NKAudioPlayer::SetMusicVolume(int volume) {
    Mix_VolumeMusic(volume * 1.28);
}
