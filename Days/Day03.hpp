#pragma once

#include "Common.hpp"

namespace Day03 {

	inline void Part1() {
		std::string inputName = "Input/Input03.txt";
		std::ifstream input(inputName);

		using SymbolRegistry_t = std::unordered_map<uint32_t, std::unordered_set<uint32_t>>;
		SymbolRegistry_t symbolRegistry;

		auto readSymbols = 
			[](uint32_t lineNumber, std::string_view line, SymbolRegistry_t& registry) {
				registry[lineNumber] = {};

				size_t lastFound = 0;
				auto pos = std::string::npos;
				while ((pos = line.find_first_of("!@#$%^&*()_+-=", lastFound)) != std::string::npos) {
					registry[lineNumber].insert(pos);
					lastFound = pos + 1;
				}
			};
		const auto testLine =
			[&](uint32_t lineNumber, std::string_view line) -> uint32_t {
				return 0;
			};

		uint32_t lineNumber = 0;

		std::string previousLine;
		if (not std::getline(input, previousLine)) {
			throw std::runtime_error(std::format("Input file is empty: {}", inputName));
		}
		//Read first line
		readSymbols(lineNumber++, previousLine, symbolRegistry);

		uint32_t numberSum = 0;

		std::string nextLine;
		while (std::getline(input, nextLine)) {
			//Read next line
			readSymbols(lineNumber++, nextLine, symbolRegistry);

			//Test previous line
			numberSum += testLine(lineNumber - 2, previousLine);

			previousLine = std::move(nextLine);
		}

		//Test previous line
		numberSum += testLine(lineNumber - 1, previousLine);
	}

	inline void Part2() {
		spdlog::info("Hello: Part2!");
	}

}