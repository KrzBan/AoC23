#pragma once

#include "Common.hpp"

namespace Day08 {

	inline void Part1() {
		enum class Direction {
			left, right
		};
		const auto parseDirections = [](std::string_view input) -> std::vector<Direction> {
			std::vector<Direction> output;
			for (const auto c : input) {
				if (c == 'L') output.push_back(Direction::left);
				else if (c == 'R') output.push_back(Direction::right);
			}
			return output;
			};
		using Map = std::unordered_map<std::string, std::pair<std::string, std::string>>;
		const auto parseMapLine = [](Map& map, const std::string& line) {
			map[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
			};
		std::string inputName = "Input/Input08.txt";
		std::ifstream input(inputName);

		std::string line;
		std::getline(input, line);
		const auto directions = parseDirections(line);

		std::getline(input, line); // Empty line

		Map map;
		while (std::getline(input, line)) {
			parseMapLine(map, line);
		}

		uint64_t steps = 0;
		std::string currentNode = "AAA";
		while (currentNode != "ZZZ") {
			const auto direction = directions.at(steps++ % directions.size());
			if (direction == Direction::left) {
				currentNode = map[currentNode].first;
			}
			else {
				currentNode = map[currentNode].second;
			}
		}

		spdlog::info("Steps: {}", steps);
	}

	inline void Part2() {
		enum class Direction {
			left, right
		};
		const auto parseDirections = [](std::string_view input) -> std::vector<Direction> {
			std::vector<Direction> output;
			for (const auto c : input) {
				if (c == 'L') output.push_back(Direction::left);
				else if (c == 'R') output.push_back(Direction::right);
			}
			return output;
			};
		using Map = std::unordered_map<std::string, std::pair<std::string, std::string>>;
		const auto parseMapLine = [](Map& map, const std::string& line) {
			map[line.substr(0, 3)] = { line.substr(7, 3), line.substr(12, 3) };
			};

		std::string inputName = "Input/Input08.txt";
		std::ifstream input(inputName);

		std::string line;
		std::getline(input, line);
		const auto directions = parseDirections(line);

		std::getline(input, line); // Empty line

		Map map;
		while (std::getline(input, line)) {
			parseMapLine(map, line);
		}

		std::vector<std::string> startNodes = std::views::keys(map)
			| std::views::filter([](const std::string& node) {return node.ends_with('A'); }) 
			| std::ranges::to<std::vector>();

		std::vector<uint64_t> distances;
		for (auto& node : startNodes) {
			uint64_t steps = 0;

			while (true) {
				const auto direction = directions.at(steps++ % directions.size());
				if (direction == Direction::left) {
					node = map[node].first;
				}
				else {
					node = map[node].second;
				}
				if (node.ends_with('Z')) {
					distances.push_back(steps);
					break;
				} 
			}
		}

		uint64_t lcm = std::lcm(distances[0], distances[1]);
		for (size_t i = 2; i < distances.size(); ++i) {
			lcm = std::lcm(lcm, distances[i]);
		}

		spdlog::info("Steps: {}", lcm);
	}

}