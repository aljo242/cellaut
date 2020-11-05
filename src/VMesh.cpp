#include "VMesh.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>


CartCoord toVirtual(const int32_t addr, const int32_t rowSize, const int32_t colSize)
{
	return CartCoord(addr, rowSize, colSize);
}


int32_t fromVirtual(const CartCoord coord, const int32_t rowSize, const int32_t colSize)
{
	return coord.x + rowSize * coord.y;
}


CartCoord::CartCoord(const int32_t addr, const int32_t rowSize, const int32_t colSize)

	: x(addr % rowSize), y(addr / colSize)
{}


CartCoord::CartCoord(const int32_t _x, const int32_t _y)
	:
	x(_x), y(_y)
{}

CartCoord CartCoord::Up(const int32_t n, const int32_t rowSize, const int32_t colSize) const
{
	auto coord = CartCoord(x, y);
	coord.y = (coord.y + n) % colSize;
	return coord;
}

CartCoord CartCoord::Down(const int32_t n, const int32_t rowSize, const int32_t colSize) const
{
	auto coord = CartCoord(x, y);
	coord.y = (coord.y - n) % colSize;
	// wrap around
	if (coord.y < 0)
	{
		coord.y += colSize;
	}
	return coord;
}

CartCoord CartCoord::Left(const int32_t n, const int32_t rowSize, const int32_t colSize) const
{
	auto coord = CartCoord(x, y);
	coord.x = (coord.x - n) % rowSize;
	// wrap around
	if (coord.x < 0)
	{
		coord.x += rowSize;
	}
	return coord;
}

CartCoord CartCoord::Right(const int32_t n, const int32_t rowSize, const int32_t colSize) const
{
	auto coord = CartCoord(x, y);
	coord.x = (coord.x + n) % rowSize;
	return coord;
}
