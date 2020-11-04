#ifndef CONWAY_GAME_H
#define CONWAY_GAME_H

#include <vector>
#include <SDL.h>

enum class CellState
{
	dead,
	alive
};


struct Cell
{
	CellState state;
	void UpdateState(const size_t index);
};


struct WorldDescription
{
	uint32_t Width;
	uint32_t Height;
	std::vector<uint32_t> pixels;
	std::vector<Cell> cells;

	explicit WorldDescription(const uint32_t width, const uint32_t height);
};




class ConwayGame
{
public:
	ConwayGame(const uint32_t worldWidth, const uint32_t worldHeight);
	bool CheckInputs(const SDL_Event& event);

	void initGame();

private:

public:
	WorldDescription world;

private:
	bool leftMouseButtonDown = false;
};

#endif // CONWAY_GAME_H