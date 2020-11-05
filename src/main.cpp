#include "Log.h"
#include "Renderer.h"
#include "ConwayGame.h"
#include <ctime>
#include <thread>
#include <chrono>

void run(SDL_Init_Info initInfo)
{
    // init renderer
    Renderer renderer(initInfo);

    // init window and game
    ConwayGame game(renderer.windowWidth, renderer.windowHeight);
    game.initGame();

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);
        quit = game.CheckInputs(event);

        // iterate game
        renderer.Update(game.world.pixels);
        renderer.Render();

		game.Update();
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}


int main()
{
#if defined(_DEBUG)
    spdlog::set_level(spdlog::level::debug);
#endif

    SDL_Init_Info initInfo{};
    initInfo.windowWidth = 320;
    initInfo.windowHeight = 320;
    initInfo.title = "TEST WINDOW";
    initInfo.flags = SDL_WINDOW_VULKAN;

    run(initInfo);

    return 0;
}