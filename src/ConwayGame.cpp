#include "ConwayGame.h"
#include <SDL.h>
#include "Log.h"

WorldDescription::WorldDescription(const uint32_t width, const uint32_t height)
	:
	Width(width),
	Height(height),
	cells(width * height)
{}


ConwayGame::ConwayGame(const uint32_t worldWidth, const uint32_t worldHeight)
	:
	world(worldWidth, worldHeight)
{
	spdlog::debug("Created pixel buffer of size {}", world.cells.size());

	std::memset(world.cells.data(), 126, world.cells.size() * sizeof(uint32_t));
}

bool ConwayGame::CheckInputs(const SDL_Event& event)
{
	switch(event.type)
	{
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonDown = false;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonDown = true;
		}
		break;

	case SDL_MOUSEMOTION:
		if (leftMouseButtonDown)
		{
			const auto mouseX = static_cast<size_t>(event.motion.x);
			const auto mouseY = static_cast<size_t>(event.motion.y);
			world.cells[mouseY * world.Width + mouseX] = 0;
		}
		break;

	case SDL_QUIT:
		return true;
		break;
	}

	return false;
}

