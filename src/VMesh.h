#ifndef VIRTUAL_MESH_H 
#define VIRTUAL_MESH_H
#include <cstdint>

struct CartCoord
{
	int32_t x{ 0 };
	int32_t y{ 0 };

	CartCoord(const int32_t addr, const int32_t rowSize, const int32_t colSize);
	CartCoord(const int32_t _x, const int32_t _y);


	CartCoord Up(const int32_t n, const int32_t rowSize, const int32_t colSize) const;
	CartCoord Down(const int32_t n, const int32_t rowSize, const int32_t colSize) const;
	CartCoord Left(const int32_t n, const int32_t rowSize, const int32_t colSize) const;
	CartCoord Right(const int32_t n, const int32_t rowSize, const int32_t colSize) const;
};


CartCoord toVirtual(const int32_t addr, const int32_t rowSize, const int32_t colSize);
int32_t fromVirtual(const CartCoord coord, const int32_t rowSize, const int32_t colSize);

#endif // VIRTUAL_MESH_H