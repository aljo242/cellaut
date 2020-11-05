#include "ConwayGame.h"
#include <SDL.h>
#include "Log.h"
#include <random>
#include <omp.h>
#include "Timer.h"
#include "VMesh.h"

using namespace std::chrono;

void Cell::UpdateState(const size_t index, const uint32_t width, const uint32_t height, const uint32_t iter)
{
	const auto width_t = static_cast<int32_t>(width);
	const auto height_t = static_cast<int32_t>(height);

	CartCoord coord(index, width_t, height_t);

	const auto n0 = coord.Up(1, width_t, height_t);
	const auto n1 = coord.Down(1, width_t, height_t);
	const auto n2 = coord.Left(1, width_t, height_t);
	const auto n3 = coord.Right(1, width_t, height_t);
	const auto n4 = n0.Left(1, width_t, height_t);
	const auto n5 = n0.Right(1, width_t, height_t);
	const auto n6 = n1.Left(1, width_t, height_t);
	const auto n7 = n1.Right(1, width_t, height_t);

	const auto n0_v = fromVirtual(n0, width_t, height_t);
	const auto n1_v = fromVirtual(n1, width_t, height_t);
	const auto n2_v = fromVirtual(n2, width_t, height_t);
	const auto n3_v = fromVirtual(n3, width_t, height_t);
	const auto n4_v = fromVirtual(n4, width_t, height_t);
	const auto n5_v = fromVirtual(n5, width_t, height_t);
	const auto n6_v = fromVirtual(n6, width_t, height_t);
	const auto n7_v = fromVirtual(n7, width_t, height_t);

	

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

//#pragma omp parallel
	{
	const size_t currentStateIndex = iters % 2;
	const size_t nextStateIndex = (iters + 1) % 2;

		//#pragma omp for schedule(static)
		for (int i = 0; i < world.cells.size(); ++i)
		{	
			const auto index = static_cast<size_t>(i);
			const auto width_t = static_cast<int32_t>(world.Width);
			const auto height_t = static_cast<int32_t>(world.Height);
			//spdlog::debug("{}", index);

			CartCoord coord(index, width_t, height_t);

			const auto n0 = coord.Up(1, width_t, height_t);
			const auto n1 = coord.Down(1, width_t, height_t);
			const auto n2 = coord.Left(1, width_t, height_t);
			const auto n3 = coord.Right(1, width_t, height_t);
			const auto n4 = n2.Up(1, width_t, height_t);
			const auto n5 = n2.Down(1, width_t, height_t);
			const auto n6 = n3.Up(1, width_t, height_t);
			const auto n7 = n3.Down(1, width_t, height_t);

			uint8_t aliveCount = 0;

			const auto n0_v = static_cast<size_t>(fromVirtual(n0, width_t, height_t));
			if (world.cells[n0_v].states[currentStateIndex] == CellState::alive) {++aliveCount;}
			const auto n1_v = static_cast<size_t>(fromVirtual(n1, width_t, height_t));
			if (world.cells[n1_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }
			const auto n2_v = static_cast<size_t>(fromVirtual(n2, width_t, height_t));
			if (world.cells[n2_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }
			const auto n3_v = static_cast<size_t>(fromVirtual(n3, width_t, height_t));
			if(world.cells[n3_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }
			const auto n4_v = static_cast<size_t>(fromVirtual(n4, width_t, height_t));
			if (world.cells[n4_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }
			const auto n5_v = static_cast<size_t>(fromVirtual(n5, width_t, height_t));
			if (world.cells[n5_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }
			const auto n6_v = static_cast<size_t>(fromVirtual(n6, width_t, height_t));
			if (world.cells[n6_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }
			const auto n7_v = static_cast<size_t>(fromVirtual(n7, width_t, height_t));
			if (world.cells[n7_v].states[currentStateIndex] == CellState::alive) { ++aliveCount; }

			if (aliveCount < 1 && aliveCount > 4)
			{
				// if 3 alive neighbors and i am dead, become alive
				if (aliveCount == 3 && world.cells[index].states[currentStateIndex] == CellState::dead)
				{
					world.cells[index].states[nextStateIndex] = CellState::alive;
 				}
				// if 2 alive, my state remains the same
			}
			// for all other cases, if I am alive, make me dead, else remain dead
			else if (world.cells[index].states[currentStateIndex] == CellState::alive)
			{
				world.cells[index].states[nextStateIndex] = CellState::dead;
			}	


			if (world.cells[index].states[nextStateIndex] == CellState::alive)
			{
				setPixel(index, Color(0, 0, 255, 0));
			}
			else
			{
				setPixel(index, Color(255, 255, 255, 255));
			}
		}
	}

	++iters;
	spdlog::debug("Iteration: {}", iters);
}

// index matches with cell index in game
void ConwayGame::setPixel(const size_t index, const Color& color)
{
	world.pixels[index] = color;
}

