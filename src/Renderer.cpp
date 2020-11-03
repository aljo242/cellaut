#include "Renderer.h"
#include <cassert>
#include "Log.h"

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
	spdlog::debug("Created Window with size {} x {}", windowWidth, windowHeight);

	renderContext = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	assert(renderContext != nullptr);

	texture = SDL_CreateTexture(
		renderContext, 
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		windowInfo.windowWidth,
		windowInfo.windowHeight
	);
	assert(texture != nullptr);


}

Renderer::~Renderer()
{
	// Close and destroy the window
	spdlog::debug("Destroying Rendering objects");
	SDL_DestroyTexture(texture);
	
	SDL_DestroyRenderer(renderContext);

	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Renderer::Update(const std::vector<uint32_t>& pixels)
{
	SDL_UpdateTexture(texture, nullptr, pixels.data(), static_cast<int>(windowWidth * sizeof(uint32_t)));
}

void Renderer::Render()
{
	SDL_RenderClear(renderContext);
	SDL_RenderCopy(renderContext, texture, nullptr, nullptr);
	SDL_RenderPresent(renderContext);
}
