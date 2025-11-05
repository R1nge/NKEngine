//
// Created by r1nge on 11/5/25.
//

#ifndef NKENGINE_NKAUDIOPLAYER_H
#define NKENGINE_NKAUDIOPLAYER_H
#include <map>
#include <SDL_mixer.h>
#include <string>

class NKAudioPlayer {
public:
    bool LoadMusic(const char *path, std::string songTitle);

    void UnloadMusic(std::string songTitle);

    bool PlayMusic(std::string songTitle);

    void PauseMusic();

    void ResumeMusic();

    //Range [0...100]
    void SetMusicVolume(int volume);

private:
    std::map<std::string, Mix_Music *> _music;
};


#endif //NKENGINE_NKAUDIOPLAYER_H
