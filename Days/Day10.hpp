#pragma once

#include "Common.hpp"

namespace Day10 {

	inline void Part1() {
		std::string inputName = "Input/Input10.txt";
		std::ifstream input(inputName);

		std::string line;
		std::getline(input, line);
		const auto rowLength = line.size();

		std::vector<char> mapData{ line.begin(), line.end() };
		while (std::getline(input, line)) {
			std::ranges::copy(line, std::back_inserter(mapData));
		}

		std::mdspan map(mapData.data(), mapData.size() / rowLength, rowLength);

		size_t startRow = 0, startCol = 0;
		for (std::size_t i = 0; i != map.extent(0); ++i)
			for (std::size_t j = 0; j != map.extent(1); ++j)
				if (map[std::array{i, j}] == 'S') {
					startRow = i;
					startCol = j;
					break;
				}

		enum class Direction { RIGHT, LEFT, UP, DOWN};
		const auto getOppositeDirection = [](Direction dir) {
			if (dir == Direction::RIGHT) return Direction::LEFT;
			if (dir == Direction::LEFT) return Direction::RIGHT;
			if (dir == Direction::UP) return Direction::DOWN;
			if (dir == Direction::DOWN) return Direction::UP;
			};
		struct InOut { Direction end1; Direction end2; };
		std::unordered_map<char, InOut> pipes{ 
			{'|', {Direction::UP, Direction::DOWN}}, {'-', {Direction::LEFT, Direction::RIGHT}},
			{'L', {Direction::UP, Direction::RIGHT}}, {'J', {Direction::UP, Direction::LEFT}},
			{'7', {Direction::LEFT, Direction::DOWN}}, {'F', {Direction::RIGHT, Direction::DOWN}} };
		const auto isPipe = [&](char c) { return pipes.contains(c); };
		const auto nextCoord = [](std::pair<size_t, size_t> pos, Direction dir) -> std::optional<std::pair<size_t, size_t>> {
			switch (dir) {
			case Direction::UP:
				if (pos.second == 0) return {};
				return std::pair{ pos.first, pos.second - 1 };
				break;
			case Direction::DOWN:
				return std::pair{ pos.first, pos.second + 1 };
				break;
			case Direction::LEFT:
				if (pos.first == 0) return {};
				return std::pair{ pos.first - 1, pos.second };
				break;
			case Direction::RIGHT:
				return std::pair{ pos.first + 1, pos.second };
				break;
			}
			};
		const auto getViableDirection = [&](std::pair<size_t, size_t> coords) {
			for (const auto& dir : std::vector{ Direction::UP, Direction::DOWN, Direction::LEFT , Direction::RIGHT }) {
				auto next = nextCoord(coords, dir);
				if (next.has_value()) {
					auto& val = next.value();
					auto symbol = map[std::array{ val.second, val.first }];
					if (not isPipe(symbol)) {
						continue;
					}

					const auto inOut = pipes.at(symbol);
					if (inOut.end1 == getOppositeDirection(dir) || inOut.end2 == getOppositeDirection(dir)) {
						return dir;
					}
				}
			}
			throw std::runtime_error("No viable start direction!");
			};
		
		auto currentDir = getViableDirection({ startCol, startRow });
		auto currentPos = std::pair<uint32_t, uint32_t>{ startCol, startRow };

		uint32_t length = 0;
		while (true) {
			++length;
			currentPos = nextCoord(currentPos, currentDir).value();

			const auto symbol = map[std::array{ currentPos.second, currentPos.first }];

			if (symbol == 'S') {
				break;
			}

			const auto inOut = pipes.at(symbol);
			currentDir = (currentDir == getOppositeDirection(inOut.end1)) ? inOut.end2 : inOut.end1;
		}

		spdlog::info("Furthest away point is: {}, original: {}!", length/2, length);
	}

	inline void Part2() {
		std::string inputName = "Input/Input10.txt";
		std::ifstream input(inputName);

		std::string line;
		std::getline(input, line);
		const auto rowLength = line.size();

		std::vector<char> mapData{ line.begin(), line.end() };
		while (std::getline(input, line)) {
			std::ranges::copy(line, std::back_inserter(mapData));
		}

		std::mdspan map(mapData.data(), mapData.size() / rowLength, rowLength);

		size_t startRow = 0, startCol = 0;
		for (std::size_t i = 0; i != map.extent(0); ++i)
			for (std::size_t j = 0; j != map.extent(1); ++j)
				if (map[std::array{ i, j }] == 'S') {
					startRow = i;
					startCol = j;
					break;
				}

		enum class Direction { RIGHT, LEFT, UP, DOWN };
		const auto getOppositeDirection = [](Direction dir) {
			if (dir == Direction::RIGHT) return Direction::LEFT;
			if (dir == Direction::LEFT) return Direction::RIGHT;
			if (dir == Direction::UP) return Direction::DOWN;
			if (dir == Direction::DOWN) return Direction::UP;
			};
		struct InOut { Direction end1; Direction end2; };
		std::unordered_map<char, InOut> pipes{
			{'|', {Direction::UP, Direction::DOWN}}, {'-', {Direction::LEFT, Direction::RIGHT}},
			{'L', {Direction::UP, Direction::RIGHT}}, {'J', {Direction::UP, Direction::LEFT}},
			{'7', {Direction::LEFT, Direction::DOWN}}, {'F', {Direction::RIGHT, Direction::DOWN}} };
		const auto isPipe = [&](char c) { return pipes.contains(c); };
		const auto nextCoord = [](std::pair<size_t, size_t> pos, Direction dir) -> std::optional<std::pair<size_t, size_t>> {
			switch (dir) {
			case Direction::UP:
				if (pos.second == 0) return {};
				return std::pair{ pos.first, pos.second - 1 };
				break;
			case Direction::DOWN:
				return std::pair{ pos.first, pos.second + 1 };
				break;
			case Direction::LEFT:
				if (pos.first == 0) return {};
				return std::pair{ pos.first - 1, pos.second };
				break;
			case Direction::RIGHT:
				return std::pair{ pos.first + 1, pos.second };
				break;
			}
			};
		const auto getViableDirection = [&](std::pair<size_t, size_t> coords) {
			for (const auto& dir : std::vector{ Direction::UP, Direction::DOWN, Direction::LEFT , Direction::RIGHT }) {
				auto next = nextCoord(coords, dir);
				if (next.has_value()) {
					auto& val = next.value();
					auto symbol = map[std::array{ val.second, val.first }];
					if (not isPipe(symbol)) {
						continue;
					}

					const auto inOut = pipes.at(symbol);
					if (inOut.end1 == getOppositeDirection(dir) || inOut.end2 == getOppositeDirection(dir)) {
						return dir;
					}
				}
			}
			throw std::runtime_error("No viable start direction!");
			};
		const auto processRow = [](const std::vector<std::pair<uint32_t,char>>& row) -> uint32_t {
			if (row.size() == 0) return 0;

			uint32_t inside = 0;
			bool openUp = false;
			bool openDown = false;
			for (size_t i = 0; i < row.size() - 1; ++i) {
				const auto currentElem = row[i];
				const auto nextElem = row[i+1];
				
				const auto symbol = currentElem.second;
				if (symbol == 'L' || symbol == 'J') openUp = not openUp;
				if (symbol == '7' || symbol == 'F') openDown = not openDown;
				if (symbol == '|') {
					openUp = not openUp;
					openDown = not openDown;
				}

				if (openUp || openDown) {
					inside += nextElem.first - currentElem.first - 1;
				}
			}
			return inside;
			};
		auto currentDir = getViableDirection({ startCol, startRow });
		auto currentPos = std::pair<uint32_t, uint32_t>{ startCol, startRow };
		std::set<std::pair<uint32_t, uint32_t>> mapHistory;

		uint32_t length = 0;
		while (true) {
			++length;
			currentPos = nextCoord(currentPos, currentDir).value();
			mapHistory.insert({currentPos.second, currentPos.first});

			const auto symbol = map[std::array{ currentPos.second, currentPos.first }];

			if (symbol == 'S') {
				break;
			}

			const auto inOut = pipes.at(symbol);
			currentDir = (currentDir == getOppositeDirection(inOut.end1)) ? inOut.end2 : inOut.end1;
		}

		uint32_t inside = 0;
		auto begin = mapHistory.begin();
		auto lastRowId = begin->first;
		std::vector<std::pair<uint32_t, char>> row;
		while (begin != mapHistory.end()) {
			if (begin->first == lastRowId) {
				row.push_back({ begin->second, map[std::array{begin->first, begin->second}]});
			}
			else {
				inside += processRow(row);
				lastRowId = begin->first;
				row.clear();
				row.push_back({ begin->second, map[std::array{begin->first, begin->second}] });
			}
			++begin;
		}
		inside += processRow(row);

		spdlog::info("Tiles inside: {}!", inside);
	}

}