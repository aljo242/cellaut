#include "Renderer.h"
#include <cassert>

Renderer::Renderer(const SDL_Init_Info& windowInfo)
	:
	windowWidth(static_cast<uint32_t>(windowInfo.windowWidth)),
	windowHeight(static_cast<uint32_t>(windowInfo.windowHeight))
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
		windowInfo.title.c_str(),
		windowInfo.xPos,
		windowInfo.yPos,
		windowInfo.windowWidth,
		windowInfo.windowHeight,
		windowInfo.flags
	);
	assert(window != nullptr);


	renderContext = SDL_CreateRenderer(window, -1, 0);
	assert(renderContext != nullptr);

}

Renderer::~Renderer()
{
	// Close and destroy the window
	SDL_DestroyWindow(window);

	SDL_Quit();
}