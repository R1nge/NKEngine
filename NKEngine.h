//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <list>
#include <SDL_render.h>
#include <string>


class NKEngine {
public:
    NKEngine();
    ~NKEngine();
    SDL_Window *CreateWindow(const char* title, int positionX, int positionY, int width, int height);
    SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string path);
    SDL_Rect *CreateSprite(int positionX, int positionY, int width, int height);
private:
    std::list<SDL_Rect*> *_sprites;
};


#endif //NKENGINE_NKENGINE_H
