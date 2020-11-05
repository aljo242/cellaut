#ifndef CONWAY_GAME_H
#define CONWAY_GAME_H

#include <vector>
#include <array>
#include <SDL.h>


struct Color
{
	uint8_t b = 0;
	uint8_t g = 0;
	uint8_t r = 0;
	uint8_t a = 0;

	Color(const uint8_t _b,
		const uint8_t _g,
		const uint8_t _r,
		const uint8_t _a)
		:
		b(_b), g(_g), r(_r), a(_a)
	{}

	Color() = default;
};

enum class CellState
{
	dead,
	alive
};


struct Cell
{
	std::array<CellState, 2> states; // alternating buffer
	void UpdateState(const size_t index, const uint32_t width, const uint32_t height);
};


struct WorldDescription
{
	uint32_t Width;
	uint32_t Height;
	std::vector<Color> pixels;
	std::vector<Cell> cells;

	explicit WorldDescription(const uint32_t width, const uint32_t height);
};


class ConwayGame
{
public:
	ConwayGame(const uint32_t worldWidth, const uint32_t worldHeight);
	bool CheckInputs(const SDL_Event& event);

	void initGame();
	void Update();

private:
	void setPixel(const size_t index, const Color& color);

public:
	WorldDescription world;

private:
	bool leftMouseButtonDown = false;
};

#endif // CONWAY_GAME_H