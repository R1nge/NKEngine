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
#include "NKSpriteData.h"
#include "NKUuidGenerator.h"


class NKEngine {
public:
    NKEngine();
    ~NKEngine();
    SDL_Window *CreateWindow(const char *title, int positionX, int positionY, int width, int height);
    SDL_Renderer* CreateRenderer(SDL_Window* window);
    SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string path);
    std::shared_ptr<NKSprite> CreateSprite(NKSpriteData *data);
    std::shared_ptr<NKSprite> CreateSprite(std::string path, NKSpriteData *data);
    void Update();

    SDL_Keycode GetLastKeyInput() const;
    NKEventDispatcher *EventDispatcher;
    NKUuidGenerator *UuidGenerator;
    SDL_Window *Window;
    SDL_Renderer *Renderer;

private:
    std::list<std::shared_ptr<NKSprite> > _sprites;
    bool _isPaused;
    SDL_Keycode _lastKeyInput;
};


#endif //NKENGINE_NKENGINE_H
