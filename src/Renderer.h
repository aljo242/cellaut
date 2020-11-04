#ifndef RENDERER_H
#define RENDERER_H

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>
#include <vector>]
#include "ConwayGame.h"


struct SDL_Init_Info
{
	std::string title;
	int xPos = SDL_WINDOWPOS_UNDEFINED;
	int yPos = SDL_WINDOWPOS_UNDEFINED;
	int windowWidth = 0;
	int windowHeight = 0;
	uint32_t flags = 0;
};

class Renderer
{
public:
	Renderer(const SDL_Init_Info& windowInfo);
	~Renderer();

	void Update(const std::vector<Color>& pixels);
	void Render();

public:
	uint32_t windowWidth = 0;
	uint32_t windowHeight = 0;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderContext = nullptr;
	SDL_Texture* texture = nullptr;
};

#endif // RENDERER_H