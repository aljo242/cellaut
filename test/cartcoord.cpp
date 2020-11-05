#include "../src/VMesh.h"
#include <spdlog/spdlog.h>

int main()
{
	int32_t width = 3;
	int32_t height = 3;
	int32_t addr = 0;

	CartCoord coord(addr, width, height);

	const auto n0 = coord.Up(1, width, height);
	const auto n1 = coord.Down(1, width, height);
	const auto n2 = coord.Left(1, width, height);
	const auto n3 = coord.Right(1, width, height);
	const auto n4 = n0.Left(1, width, height);
	const auto n5 = n0.Right(1, width, height);
	const auto n6 = n1.Left(1, width, height);
	const auto n7 = n1.Right(1, width, height);

	const auto n0_v = fromVirtual(n0, width, height);
	const auto n1_v = fromVirtual(n1, width, height);
	const auto n2_v = fromVirtual(n2, width, height);
	const auto n3_v = fromVirtual(n3, width, height);
	const auto n4_v = fromVirtual(n4, width, height);
	const auto n5_v = fromVirtual(n5, width, height);
	const auto n6_v = fromVirtual(n6, width, height);
	const auto n7_v = fromVirtual(n7, width, height);

	int outCode = 0;

	if (n0_v != 3) { outCode = 1; }
	if (n1_v != 6) { outCode = 1; }
	if (n2_v != 2) { outCode = 1; }
	if (n3_v != 1) { outCode = 1; }
	if (n4_v != 5) { outCode = 1; }
	if (n5_v != 4) { outCode = 1; }
	if (n6_v != 8) { outCode = 1; }
	if (n7_v != 7) { outCode = 1; }

	return outCode;
}