#include "Renderer.h"


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
}

Renderer::~Renderer()
{
	SDL_Quit();
}