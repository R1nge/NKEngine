//
// Created by r1nge on 11/5/25.
//

#include "NKAudioPlayer.h"
bool NKAudioPlayer::LoadSong(const char *path, std::string songTitle) {
    auto music = Mix_LoadMUS(path);
    if (music == nullptr) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    _songs[songTitle] = music;

    return true;
}

void NKAudioPlayer::UnloadSong(std::string songTitle) {
    if (_songs.size() > 0) {
        auto music = _songs.at(songTitle);
        if (music != nullptr) {
            Mix_FreeMusic(music);
            _songs.erase(songTitle);
        }
    }
}

bool NKAudioPlayer::PlaySong(std::string songTitle) {
    if (_songs.contains(songTitle)) {
        Mix_PlayMusic(_songs.at(songTitle), -1);
        return true;
    }
    printf("Failed to play music!");
    return false;
}

bool NKAudioPlayer::ReplaceCurrentSong(const char *path, std::string newSongTitle) {
    PauseMusic();
    if (_songs.size() > 0) {
        UnloadSong(_songs.begin()->first);
    }
    LoadSong(path, newSongTitle);
    PlaySong(newSongTitle);
    return true;
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
