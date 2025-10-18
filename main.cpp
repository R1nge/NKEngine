#include <iostream>
#include <SDL2/SDL.h>
#include <cstdio>
#include <SDL2/SDL_image.h>

//TODO: display png
//TODO: display a part from a png
//TODO: display player as a space ship
//TODO: create an engine class
//TODO: engine should use callbacks to allow to sub to the engine events like (Start, Update)
//TODO: load engine as a lib
//TODO: call engine API to do things
//TODO: separate space invaders and engine repositories


//Screen dimension constants
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *window = nullptr;

//The surface contained by the window
SDL_Surface *screen = nullptr;

//Renderer
SDL_Renderer *renderer;

//The image we will load and show on the screen
SDL_Surface *player = nullptr;

SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
        if( optimizedSurface == nullptr)
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

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
        if (window == nullptr) {
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
    if (player == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", "assets/bochi.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface(player);
    player = nullptr;

    //Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

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

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            int imgFlags = IMG_INIT_PNG;
            loadSurface("assets/space_invaders.png");

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
                    SDL_FillRect(surface, nullptr, skyblue);
                    SDL_BlitScaled(player, nullptr, screen, imageSize);
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
