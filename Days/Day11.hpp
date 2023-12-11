#pragma once

#include "Common.hpp"

namespace Day11 {

	struct Point {
		size_t x; size_t y;
		void swap(Point& rhs){
			std::swap(x, rhs.x);
			std::swap(y, rhs.y);
		}
		friend auto operator<=>(const Point&, const Point&) = default;
	};

	inline void Part1() {
		const std::string inputName = "Input/Input11.txt";
		std::ifstream input(inputName);

		std::set<Point> galaxies;
		size_t row = 0;
		
		std::string line;
		while (std::getline(input, line)) {
			size_t offset = 0;
			size_t pos = 0;
			while ((pos = line.find('#', offset)) != std::string::npos) {
				galaxies.insert(Point{ pos, row });
				offset = pos + 1;
			}
			++row;
		}

		const auto expandXandReverse = [](const std::set<Point>& galaxies) {
			std::set<Point> newGalaxies;
			size_t emptyRows = 0;
			size_t lastRow = galaxies.begin()->x;
			for (const auto& point : galaxies) {
				if (point.x > lastRow) {
					emptyRows += point.x - lastRow - 1;
					lastRow = point.x;
				}

				newGalaxies.insert(Point{ point.y, point.x + emptyRows });
			}
			return newGalaxies;
			};
		
		const auto expandedY = expandXandReverse(galaxies);
		const auto expanded = expandXandReverse(expandedY);

		size_t distance = 0;
		for (const auto point1 : expanded) {
			for (const auto point2 : expanded) {
				if (point1 == point2) {
					continue;
				}

				distance += std::max(point1.x, point2.x) - std::min(point1.x, point2.x);
				distance += std::max(point1.y, point2.y) - std::min(point1.y, point2.y);
			}
		}

		spdlog::info("Distance: {}", distance/2);

	}

	inline void Part2() {
		const std::string inputName = "Input/Input11.txt";

		std::ifstream input(inputName);

		std::set<Point> galaxies;
		size_t row = 0;

		std::string line;
		while (std::getline(input, line)) {
			size_t offset = 0;
			size_t pos = 0;
			while ((pos = line.find('#', offset)) != std::string::npos) {
				galaxies.insert(Point{ pos, row });
				offset = pos + 1;
			}
			++row;
		}

		const auto expandXandReverse = [](const std::set<Point>& galaxies) {
			std::set<Point> newGalaxies;
			size_t emptyRows = 0;
			size_t lastRow = galaxies.begin()->x;
			for (const auto& point : galaxies) {
				if (point.x > lastRow) {
					emptyRows += (point.x - lastRow - 1);
					lastRow = point.x;
				}

				newGalaxies.insert(Point{ point.y, point.x + (emptyRows * 1000000 - emptyRows) });
			}
			return newGalaxies;
			};

		const auto expandedY = expandXandReverse(galaxies);
		const auto expanded = expandXandReverse(expandedY);

		size_t distance = 0;
		for (auto it = expanded.begin(); it != expanded.end(); ++it) {
			for (auto second = std::next(it); second != expanded.end(); ++second) {

				const auto& point1 = *it;
				const auto& point2 = *second;

				distance += (point1.x > point2.x) ? point1.x - point2.x : point2.x - point1.x;
				distance += (point1.y > point2.y) ? point1.y - point2.y : point2.y - point1.y;
			}
		}

		spdlog::info("Distance: {}", distance);
	}

}