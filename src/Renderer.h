#ifndef RENDERER_H
#define RENDERER_H

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>

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

public:
	SDL_Window* window = nullptr;
	uint32_t windowWidth = 0;
	uint32_t windowHeight = 0;
private:


};

#endif // RENDERER_H