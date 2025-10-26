//
// Created by r1nge on 10/25/25.
//

#ifndef NKENGINE_NKRENDERER_H
#define NKENGINE_NKRENDERER_H
#include <SDL_render.h>
#include <SDL_video.h>

#include "NKSystem.h"
#include "../NKUuidGenerator.h"

//TODO: move to ini config
const int SCREEN_WIDTH = 256 * 4; //space invaders
const int SCREEN_HEIGHT = 224 * 4; //space invaders
const int REFERENCE_RESOLUTION_WIDTH = 256;
const int REFERENCE_RESOLUTION_HEIGHT = 224;
const int SCALE_X = SCREEN_WIDTH / REFERENCE_RESOLUTION_WIDTH;
const int SCALE_Y = SCREEN_HEIGHT / REFERENCE_RESOLUTION_HEIGHT;

class NKRenderingSystem : public NKSystem {
public:
    NKRenderingSystem();

    void Update() override;

    void Render();
    void Rewind(int tick);

    //TODO: move it to Engine for now, create a window management class later???
    SDL_Window *CreateWindow(const char *title, int positionX, int positionY, int width, int height);
    SDL_Renderer* CreateRenderer();

    SDL_Texture *LoadTexture(std::string path);

    SDL_Window *Window;
    SDL_Renderer *Renderer;
};


#endif //NKENGINE_NKRENDERER_H
