#pragma once

#include "Common.hpp"

namespace Day02 {

	inline void Part1() {
		std::ifstream input("Input/Input02.txt");

		struct ScoreInfo {
			std::string color;
			uint32_t count;
		};

		const std::unordered_map<std::string, uint32_t> maxCubes{
			{"red", 12}, {"green", 13}, {"blue", 14}
		};

		const auto parseGameId = [](const std::string& game) {
			std::stringstream sstream(game);
			uint32_t id{};
			std::string empty;

			sstream >> empty;
			sstream >> id;

			return id;
		};
		const auto parseScore = [](const std::string& score) {
			std::stringstream sstream(score);
			uint32_t count{};
			std::string color;

			sstream >> count;
			sstream >> color;

			return ScoreInfo{ color, count };
		};

		uint32_t possibleGameIdSum = 0;

		std::string line;
		while (std::getline(input, line)) {

			auto colonSplit = line | std::views::split(':') | std::ranges::to<std::vector>();
			assert(colonSplit.size() == 2);

			auto gameName = colonSplit.front() | std::ranges::to<std::string>();
			const auto gameId = parseGameId(gameName);

			bool gamePossible = [&]() {
				for (const auto&& set : colonSplit.back() | std::views::split(';')) {
					for (const auto&& score : set | std::views::split(',')) {
						const auto scoreString = score | std::ranges::to<std::string>();
						const auto parsed = parseScore(scoreString);

						assert(maxCubes.count(parsed.color) != 0);

						if (parsed.count > maxCubes.at(parsed.color)) {
							return false;
						}
					}
				}
				return true;
			}();


			if (gamePossible) {
				possibleGameIdSum += gameId;
			}

		}

		spdlog::info("Possible games id sum: {}", possibleGameIdSum);
	}

	inline void Part2() {
		std::ifstream input("Input/Input02.txt");

		struct ScoreInfo {
			std::string color;
			uint32_t count;
		};

		const auto parseScore = [](const std::string& score) {
			std::stringstream sstream(score);
			uint32_t count{};
			std::string color;

			sstream >> count;
			sstream >> color;

			return ScoreInfo{ color, count };
		};

		uint32_t gamePowerSum = 0;

		std::string line;
		while (std::getline(input, line)) {

			auto colonSplit = line | std::views::split(':') | std::ranges::to<std::vector>();
			assert(colonSplit.size() == 2);

			auto gameName = colonSplit.front() | std::ranges::to<std::string>();

			std::unordered_map<std::string, uint32_t> maximums{
				{"red", 0}, {"green", 0}, {"blue", 0}
			};

			for (const auto&& set : colonSplit.back() | std::views::split(';')) {
				for (const auto&& score : set | std::views::split(',')) {
					const auto scoreString = score | std::ranges::to<std::string>();
					const auto parsed = parseScore(scoreString);

					assert(maximums.count(parsed.color) != 0);
					maximums.at(parsed.color) = std::max(parsed.count, maximums.at(parsed.color));
				}
			}

			const auto gamePower = std::accumulate(maximums.begin(), maximums.end(), 1, 
				[](uint32_t total, const std::pair<std::string, uint32_t>& pair) {
					return total * pair.second;
				});

			gamePowerSum += gamePower;
		}

		spdlog::info("Game power sum: {}", gamePowerSum);
	}
}