#pragma once

#include "Common.hpp"

namespace Day03 {

	inline void Part1() {
		std::string inputName = "Input/Input03.txt";
		std::ifstream input(inputName);

		using SymbolRegistry_t = std::unordered_map<uint32_t, std::unordered_set<uint32_t>>;
		SymbolRegistry_t symbolRegistry;

		auto readSymbols = 
			[&](uint32_t lineNumber, std::string_view line) {
			symbolRegistry[lineNumber] = {};

				size_t lastFound = 0;
				auto pos = std::string::npos;
				while ((pos = line.find_first_not_of("\n.0123456789", lastFound)) != std::string::npos) {
					symbolRegistry[lineNumber].insert(pos);
					lastFound = pos + 1;
				}
			};

		const auto testSymbol = [&](uint32_t lineNumber, size_t pos) -> bool {
			return symbolRegistry[lineNumber].count(pos);
			};

		const auto rangeNeighborsSymbol =
			[&](uint32_t lineNumber, size_t startPos, size_t length) {

			if (startPos != 0) {
				if (testSymbol(lineNumber+1, startPos - 1)) return true;
				if (testSymbol(lineNumber+0, startPos - 1)) return true;
				if (lineNumber != 0) {
					if (testSymbol(lineNumber-1, startPos - 1)) return true;
				}
			}
			if (testSymbol(lineNumber+1, startPos + length)) return true;
			if (testSymbol(lineNumber+0, startPos + length)) return true;
			if (lineNumber != 0) {
				if (testSymbol(lineNumber-1, startPos + length)) return true;
			}
			for (auto i = startPos; i < startPos + length; ++i) {
				if (lineNumber != 0) {
					if (testSymbol(lineNumber - 1, i)) return true;
				}
				if (testSymbol(lineNumber + 1, i)) return true;
			}

			return false;
			};

		const auto testLine =
			[&](uint32_t lineNumber, std::string_view line) -> uint32_t {

			uint32_t numSum = 0;

			size_t numOffset = 0;
			size_t digitOffset{};
			while ((digitOffset = line.find_first_of("0123456789", numOffset)) != std::string::npos) {
				uint32_t num{};
				auto result = std::from_chars(line.data() + digitOffset, line.data() + line.size(), num);
				auto numLength = result.ptr - (line.data() + digitOffset);
				if (rangeNeighborsSymbol(lineNumber, digitOffset, numLength)) {
					numSum += num;
				}
				numOffset = std::distance(line.data(), result.ptr);
			}
			return numSum;
			};

		uint32_t lineNumber = 0;

		std::string previousLine;
		if (not std::getline(input, previousLine)) {
			throw std::runtime_error(std::format("Input file is empty: {}", inputName));
		}
		//Read first line
		readSymbols(lineNumber++, previousLine);

		uint32_t numberSum = 0;

		std::string nextLine;
		while (std::getline(input, nextLine)) {
			//Read next line
			readSymbols(lineNumber++, nextLine);

			//Test previous line
			numberSum += testLine(lineNumber - 2, previousLine);

			previousLine = std::move(nextLine);
		}

		//Test previous line
		numberSum += testLine(lineNumber - 1, previousLine);

		spdlog::info("Sum is: {}", numberSum);
	}

	inline void Part2() {
		std::string inputName = "Input/Input03.txt";
		std::ifstream input(inputName);

		using GearRegistry_t = std::unordered_map<uint32_t, std::unordered_set<uint32_t>>;
		GearRegistry_t gearRegistry;

		using Vec2d = std::pair<uint32_t, uint32_t>;
		using GearData_t = std::map<Vec2d, std::vector<uint32_t>>;
		GearData_t gearData;

		auto readStars =
			[&](uint32_t lineNumber, std::string_view line) {
			gearRegistry[lineNumber] = {};

			size_t lastFound = 0;
			auto pos = std::string::npos;
			while ((pos = line.find('*', lastFound)) != std::string::npos) {
				gearRegistry[lineNumber].insert(pos);
				lastFound = pos + 1;
			}
			};

		const auto testSymbol = [&](uint32_t lineNumber, size_t pos) -> bool {
			return gearRegistry[lineNumber].count(pos);
			};

		const auto rangeNeighborsGears =
			[&](uint32_t lineNumber, size_t startPos, size_t length) -> std::optional<Vec2d> {

			if (startPos != 0) {
				if (testSymbol(lineNumber + 1, startPos - 1)) return Vec2d{ lineNumber + 1, startPos - 1 };
				if (testSymbol(lineNumber + 0, startPos - 1)) return Vec2d{ lineNumber + 0, startPos - 1 };
				if (lineNumber != 0) {
					if (testSymbol(lineNumber - 1, startPos - 1)) return Vec2d{ lineNumber - 1, startPos - 1 };
				}
			}
			if (testSymbol(lineNumber + 1, startPos + length)) return Vec2d{ lineNumber + 1, startPos + length };
			if (testSymbol(lineNumber + 0, startPos + length)) return Vec2d{ lineNumber + 0, startPos + length };
			if (lineNumber != 0) {
				if (testSymbol(lineNumber - 1, startPos + length)) return Vec2d{ lineNumber - 1, startPos + length };
			}
			for (auto i = startPos; i < startPos + length; ++i) {
				if (lineNumber != 0) {
					if (testSymbol(lineNumber - 1, i)) return Vec2d{ lineNumber - 1, i };
				}
				if (testSymbol(lineNumber + 1, i)) return Vec2d{ lineNumber + 1, i };
			}

			return {};
			};

		const auto testLine =
			[&](uint32_t lineNumber, std::string_view line) {

			uint32_t numSum = 0;

			size_t numOffset = 0;
			size_t digitOffset{};
			while ((digitOffset = line.find_first_of("0123456789", numOffset)) != std::string::npos) {
				uint32_t num{};
				auto result = std::from_chars(line.data() + digitOffset, line.data() + line.size(), num);
				auto numLength = result.ptr - (line.data() + digitOffset);
				auto gearLoc = rangeNeighborsGears(lineNumber, digitOffset, numLength);

				if(gearLoc.has_value()){
					gearData[gearLoc.value()].push_back(num);
				}
				numOffset = std::distance(line.data(), result.ptr);
			}

			};

		uint32_t lineNumber = 0;

		std::string previousLine;
		if (not std::getline(input, previousLine)) {
			throw std::runtime_error(std::format("Input file is empty: {}", inputName));
		}
		//Read first line
		readStars(lineNumber++, previousLine);

		std::string nextLine;
		while (std::getline(input, nextLine)) {
			//Read next line
			readStars(lineNumber++, nextLine);

			//Test previous line
			testLine(lineNumber - 2, previousLine);

			previousLine = std::move(nextLine);
		}

		//Test previous line
		testLine(lineNumber - 1, previousLine);

		uint32_t gearSum = 0;
		for (const auto& [location, elems] : gearData) {
			if (elems.size() == 2) {
				gearSum += (elems[0] * elems[1]);
			}
		}

		spdlog::info("Gear Sum is: {}", gearSum);
	}

}
