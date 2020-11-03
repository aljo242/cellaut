#include "Log.h"
#include "Renderer.h"
#include "ConwayGame.h"

void run(SDL_Init_Info initInfo)
{
    // init renderer
    Renderer renderer(initInfo);

    // init window and game
    ConwayGame game(renderer.windowWidth, renderer.windowHeight);

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);
        quit = game.CheckInputs(event);

        // iterate game
        renderer.Update(game.world.cells);
        renderer.Render();
    }
}


int main()
{
#if defined(_DEBUG)
    spdlog::set_level(spdlog::level::debug);
#endif

    SDL_Init_Info initInfo{};
    initInfo.windowWidth = 1280;
    initInfo.windowHeight = 720;
    initInfo.title = "TEST WINDOW";
    initInfo.flags = SDL_WINDOW_VULKAN;

    run(initInfo);

    return 0;
}