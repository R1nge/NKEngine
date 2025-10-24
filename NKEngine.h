//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <list>
#include <memory>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <string>

#include "NKEventDispatcher.h"
#include "NKSprite.h"
#include "NKUuidGenerator.h"


class NKEngine {
public:
    NKEngine();
    ~NKEngine();
    SDL_Window *CreateWindow(const char *title, int positionX, int positionY, int width, int height);
    SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string path);
    std::shared_ptr<NKSprite> CreateSprite(int positionX, int positionY, int width, int height);
    std::shared_ptr<NKSprite> CreateSprite(SDL_Renderer *renderer, std::string path, int positionX, int positionY,int width, int height);
    void Update(SDL_Renderer *renderer);

    SDL_Keycode GetLastKeyInput() const;
    NKEventDispatcher* EventDispatcher;
    NKUuidGenerator* UuidGenerator;
private:
    std::list<std::shared_ptr<NKSprite> > _sprites;
    bool _isPaused;
    SDL_Keycode _lastKeyInput;
};


#endif //NKENGINE_NKENGINE_H
