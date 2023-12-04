#pragma once

#include "Common.hpp"

namespace Day04 {

	inline void Part1() {
		std::string inputName = "Input/Input04.txt";
		std::ifstream input(inputName);

		uint32_t globalScore = 0;

		std::string line;
		while (std::getline(input, line)) {
			auto colonSplit = line.find(':');
			auto vertSplit = line.find('|');

			const auto cardStr = line.substr(0, colonSplit);
			const auto winningNumsStr = line.substr(colonSplit + 1, vertSplit - colonSplit - 1);
			const auto ownedNumsStr = line.substr(vertSplit + 1);

			std::vector<uint32_t> winningNums;
			{
				uint32_t num;
				std::stringstream stream{ winningNumsStr };
				while (stream >> num) {
					winningNums.push_back(num);
				}
			}

			std::unordered_set<uint32_t> ownedNums;
			{
				uint32_t num;
				std::stringstream stream{ ownedNumsStr };
				while (stream >> num) {
					ownedNums.insert(num);
				}
			}

			uint32_t score = std::accumulate(winningNums.begin(), winningNums.end(), uint32_t{ 0 }, 
				[&](uint32_t prev, uint32_t b) {
					return prev + ownedNums.count(b);
				});

			if (score != 0) {
				score = std::round(std::pow(2, score - 1));
			}
			globalScore += score;
		}
		spdlog::info("Score is: {}", globalScore);
	}

	inline void Part2() {
		std::string inputName = "Input/Input04.txt";
		std::ifstream input(inputName);

		uint32_t scratchcards = 0;
		std::unordered_map<uint32_t, uint32_t> lineRegistry;

		uint32_t lineNumber = 1;
		std::string line;
		while (std::getline(input, line)) {
			auto colonSplit = line.find(':');
			auto vertSplit = line.find('|');

			const auto cardStr = line.substr(0, colonSplit);
			const auto winningNumsStr = line.substr(colonSplit + 1, vertSplit - colonSplit - 1);
			const auto ownedNumsStr = line.substr(vertSplit + 1);

			std::vector<uint32_t> winningNums;
			{
				uint32_t num;
				std::stringstream stream{ winningNumsStr };
				while (stream >> num) {
					winningNums.push_back(num);
				}
			}

			std::unordered_set<uint32_t> ownedNums;
			{
				uint32_t num;
				std::stringstream stream{ ownedNumsStr };
				while (stream >> num) {
					ownedNums.insert(num);
				}
			}

			uint32_t score = std::accumulate(winningNums.begin(), winningNums.end(), uint32_t{ 0 },
				[&](uint32_t prev, uint32_t b) {
					return prev + ownedNums.count(b);
				});
			auto copies = 1 + lineRegistry[lineNumber];
			scratchcards += copies;

			for (uint32_t i = 0; i < score; ++i) {
				lineRegistry[lineNumber + i + 1] += copies;
			}

			++lineNumber;
		}
		spdlog::info("Scratchcards is: {}", scratchcards);
	}
}