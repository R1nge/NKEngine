//
// Created by r1nge on 10/27/25.
//

#ifndef NKENGINE_NKSPRITECREATOR_H
#define NKENGINE_NKSPRITECREATOR_H
#include <memory>
#include <SDL_render.h>
#include <SDL_image.h>


class NKSpriteCreator {
public:
    NKSpriteCreator(SDL_Renderer *renderer);

    SDL_Texture *LoadTexture(std::string path);

private:
    SDL_Renderer *_renderer;
};


#endif //NKENGINE_NKSPRITECREATOR_H
