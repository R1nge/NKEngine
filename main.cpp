#include <iostream>
#include <SDL.h>
#include <stdio.h>

//TODO: display png
//TODO: display a part from a png
//TODO: display player as a space ship
//TODO: create an engine class
//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *window = NULL;

//The surface contained by the window
SDL_Surface *screen = NULL;

//Renderer
SDL_Renderer *renderer;

//The image we will load and show on the screen
SDL_Surface *player = NULL;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        window = SDL_CreateWindow("NKEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Get window surface
            screen = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
    player = SDL_LoadBMP("assets/bocchi.bmp");
    if (player == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "assets/bochi.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface(player);
    player = NULL;

    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main() {
    int posX = (SCREEN_WIDTH / 2) - 100;
    int posY = (SCREEN_HEIGHT / 2) - 100;
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Apply the image
            SDL_Rect *imageSize = new SDL_Rect(posX, posY, 200, 200);

            SDL_Surface *surface = SDL_GetWindowSurface(window);
            Uint32 skyblue = SDL_MapRGB(surface->format, 65, 193, 193);

            //Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym) {
                            case SDLK_w:
                                posY--;
                                imageSize->y = posY;
                                break;

                            case SDLK_s:
                                posY++;
                                imageSize->y = posY;
                                break;

                            case SDLK_a:
                                posX--;
                                imageSize->x = posX;
                                std::cout << "Left";
                                break;

                            case SDLK_d:
                                posX++;
                                imageSize->x = posX;
                                break;

                            default:
                                break;
                        }
                    }
                    SDL_FillRect(surface, NULL, skyblue);
                    SDL_BlitScaled(player, NULL, screen, imageSize);
                    //Update the surface
                    SDL_UpdateWindowSurface(window);
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
