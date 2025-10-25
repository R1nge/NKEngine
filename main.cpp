#include <iostream>
#include <SDL2/SDL.h>
#include <cstdio>
#include <SDL2/SDL_image.h>
#include <string>

#include "MyGameEventSubscriber.h"
#include "NKEngine.h"

//TODO: create a separate window class, expose via engine
//TODO: save engine settings into ini file https://github.com/dujingning/inicpp    (resolution, reference resolution, scale (width-height 0-1)

//TODO: store object in dict<uuid, NKObject>, destroy by id
//TODO: target fps + frametime + deltatime (add target fps to the config)


//TODO: transformation matrix (position, scale, rotation)
//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories
//TODO: C# binding jff
//Screen dimension constants
const int SCREEN_WIDTH = 256*4; //space invaders
const int SCREEN_HEIGHT = 224*4; //space invaders
const int REFERENCE_RESOLUTION_WIDTH = 256;
const int REFERENCE_RESOLUTION_HEIGHT = 224;
const int SCALE_X = SCREEN_WIDTH / REFERENCE_RESOLUTION_WIDTH;
const int SCALE_Y = SCREEN_HEIGHT / REFERENCE_RESOLUTION_HEIGHT;

bool init(std::shared_ptr<NKEngine> engine);

bool init(std::shared_ptr<NKEngine> engine) {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        engine->CreateWindow("NKEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT);
        engine->CreateRenderer(engine->Window);
    }

    return success;
}

int main() {
    auto nk_engine = std::make_shared<NKEngine>();

    if (!init(nk_engine)) {
        printf("Failed to initialize!\n");
    } else {
        auto renderer = nk_engine->Renderer;
        nk_engine->CreateSprite(renderer, "assets/space_invaders.png",new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X, 10 * SCALE_Y, 0, 0, 20, 10, 255, 255, 255));
        auto player = nk_engine->CreateSprite(renderer, "assets/space_invaders.png",new NKSpriteData(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20 * SCALE_X, 10 * SCALE_Y, 0, 48, 20, 10, 255, 255,255));
        //Main loop
        NKEventSubscriber *mySub = new MyGameEventSubscriber(player, nk_engine);
        nk_engine->EventDispatcher->AddSubscriber(mySub);

        std::cout << nk_engine->UuidGenerator->Generate();
        nk_engine->Update(renderer);
    }

    return 0;
}
