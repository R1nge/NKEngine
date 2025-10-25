//
// Created by r1nge on 10/25/25.
//

#ifndef NKENGINE_NKRENDERER_H
#define NKENGINE_NKRENDERER_H
#include <map>
#include <SDL_render.h>
#include <SDL_video.h>

#include "NKSprite.h"
#include "NKSpriteData.h"
#include "NKUuidGenerator.h"
#include "uuid.h"

//TODO: move to ini config
const int SCREEN_WIDTH = 256 * 4; //space invaders
const int SCREEN_HEIGHT = 224 * 4; //space invaders
const int REFERENCE_RESOLUTION_WIDTH = 256;
const int REFERENCE_RESOLUTION_HEIGHT = 224;
const int SCALE_X = SCREEN_WIDTH / REFERENCE_RESOLUTION_WIDTH;
const int SCALE_Y = SCREEN_HEIGHT / REFERENCE_RESOLUTION_HEIGHT;

class NKRenderer {
public:
    NKRenderer(NKUuidGenerator *uuidGenerator);

    void Render();

    SDL_Window *CreateWindow(const char *title, int positionX, int positionY, int width, int height);
    SDL_Renderer* CreateRenderer();

    SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string path);

    std::shared_ptr<NKSprite> CreateSprite(NKSpriteData *data);

    std::shared_ptr<NKSprite> CreateSprite(std::string path, NKSpriteData *data);

    SDL_Window *Window;
    SDL_Renderer *Renderer;
    std::map<uuids::uuid, std::shared_ptr<NKSprite> > Sprites;

private:
    NKUuidGenerator *_uuidGenerator;
};


#endif //NKENGINE_NKRENDERER_H
