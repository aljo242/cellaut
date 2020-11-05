#include "ConwayGame.h"
#include <SDL.h>
#include "Log.h"
#include <random>
#include <omp.h>
#include "Timer.h"

using namespace std::chrono;

void Cell::UpdateState(const size_t index, const uint32_t width, const uint32_t height)
{
	const auto width_t = static_cast<int>(width);
	const auto height_t = static_cast<int>(height);

	// count states of neighbors
	int n0 = (index - 1) % width_t;						// neighbor to the left
	if (n0 < 0) {n0 += width_t;}
	int n1 = (index + 1) % width_t;						// neighbor to the right
	int n2 = index - width_t;			// neighbor above
	if (n2 < 0) {n2 += width;}
	int n3 = (index + width_t) % (width_t * height_t);			// neighbor below
	int n4 = (n2 - 1) % width_t;
	if (n4 < 0) { n4 += width_t; }
	int n5 = (n2 + 1) % width_t; 
	int n6 = n3 - 1; 
	if (n6 < 0) { n6 += width_t; }
	int n7 = (n3 + 1) % width_t; 


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

	std::memset(world.pixels.data(), 255, world.pixels.size() * sizeof(Color));
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
			world.pixels[(mouseY * static_cast<size_t>(world.Width) + mouseX)] = Color(0, 0, 0, 255);
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
	spdlog::debug("Initializing grid...");
	Timer timer;

	#pragma omp parallel
	{
		// each thread gets its own random device
		std::random_device rd;
		std::uniform_int_distribution<> randomizer(0, 1);
		
		#pragma omp for schedule(static)
		for (int i = 0; i < world.Height * world.Width; ++i)
		{
			const auto index = static_cast<size_t>(i);
			const int val = randomizer(std::mt19937(rd()));
			world.cells[index].states[0] = (val == 1) ? CellState::dead : CellState::alive;

			if (world.cells[index].states[0] == CellState::alive)
			{
				setPixel(index, Color(0, 0, 255, 0));
			}
		}
	}
	const auto elapsedTimer_ms = timer.Stop();
	spdlog::debug("Grid initialized.");
	spdlog::debug("Elapsed time: {}s", static_cast<double>(elapsedTimer_ms) / 1000.0);
}

void ConwayGame::Update()
{
	for (int i = 0; i < world.cells.size(); ++i)
	{
		const auto index = static_cast<size_t>(i);
		world.cells[index].UpdateState(index, world.Width, world.Height);
	}
}

// index matches with cell index in game
void ConwayGame::setPixel(const size_t index, const Color& color)
{
	world.pixels[index] = color;
}

