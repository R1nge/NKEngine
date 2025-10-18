#include <iostream>
#include <SDL.h>
#include <stdio.h>

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
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *screen = NULL;

//The image we will load and show on the screen
SDL_Surface *window = NULL;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("NKEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Get window surface
            screen = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
    window = SDL_LoadBMP("assets/bocchi.bmp");
    if (window == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "assets/bochi.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface(window);
    window = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

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
                    SDL_UpdateWindowSurface(gWindow);

                    SDL_BlitScaled(window, NULL, screen, imageSize);

                    //Update the surface
                    SDL_UpdateWindowSurface(gWindow);
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
