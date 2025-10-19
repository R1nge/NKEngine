//
// Created by r1nge on 10/19/25.
//

#ifndef NKENGINE_NKENGINE_H
#define NKENGINE_NKENGINE_H
#include <SDL_render.h>
#include <string>


class NKEngine {
public:
    SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string path, int positionX, int positionY, int width,
                             int height);
};


#endif //NKENGINE_NKENGINE_H
