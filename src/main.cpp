#include <spdlog/spdlog.h>
#include "Renderer.h"

void run(SDL_Init_Info initInfo)
{
    // init renderer
    Renderer renderer(initInfo);

    // init window and game

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
}


int main()
{
    spdlog::critical("Hello World!");

    SDL_Init_Info initInfo{};
    initInfo.windowWidth = 1280;
    initInfo.windowHeight = 720;
    initInfo.title = "TEST WINDOW";

    run(initInfo);

    return 0;
}