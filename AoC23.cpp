#include "AoC23.hpp"

int main()
{
	constexpr uint32_t day = 1;
	switch (day) {
	case 0: {
		Day00::Part1();
		Day00::Part2();
		break;
	}
	case 1: {
		Day01::Part1();
		Day01::Part2();
		break;
	}
	}
}
