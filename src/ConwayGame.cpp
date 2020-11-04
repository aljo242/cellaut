#include "ConwayGame.h"
#include <SDL.h>
#include "Log.h"
#include <random>

void Cell::UpdateState(const size_t index)
{
	// count states of neighbors
	
}


WorldDescription::WorldDescription(const uint32_t width, const uint32_t height)
	:
	Width(width),
	Height(height),
	pixels(static_cast<size_t>(width) * static_cast<size_t>(height)),
	cells(static_cast<size_t>(width) * static_cast<size_t>(height))
{}


ConwayGame::ConwayGame(const uint32_t worldWidth, const uint32_t worldHeight)
	:
	world(worldWidth, worldHeight)
{
	spdlog::debug("Created pixel buffer of size {}", world.pixels.size());

	std::memset(world.pixels.data(), 0, world.pixels.size() * sizeof(uint32_t));
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
			world.pixels[mouseY * static_cast<size_t>(world.Width) + mouseX] = 0;
		}
		break;

	case SDL_QUIT:
		return true;
		break;
	}

	return false;
}

void ConwayGame::initGame()
{
	srand(time(NULL));
	std::random_device rd;
	std::uniform_int_distribution<> randomizer(0, 1);

	for (size_t index = 0; index < world.Height * world.Width; ++index)
	{
		world.cells[index].state = (rand() & 1) ? CellState::dead : CellState::alive;
		const int val = randomizer(std::mt19937(rd()));
		if (world.cells[index].state == CellState::alive) 
		{
			std::memset(world.pixels.data() + index, 255, sizeof(uint32_t));
		}
	}
}


