#pragma once

#include "Common.hpp"

namespace Day06 {

	inline void Part1() {
		const auto getNums = [](const std::string& input) {
			std::stringstream stream{ input };
			std::vector<uint32_t> nums;
			uint32_t num;
			while (stream >> num) {
				nums.push_back(num);
			}
			return nums;
			};

		const auto chargeRange = [](int32_t max, int32_t record) -> std::pair<uint32_t, uint32_t> {
			const auto delta = max * max - 4 * record;
			auto x1 = (-max - std::sqrt(delta)) / -2;
			auto x2 = (-max + std::sqrt(delta)) / -2;
			if (x1 < 0) x1 = 0; if (x1 > max) x1 = max;
			if (x2 < 0) x2 = 0; if (x2 > max) x2 = max;
			if (x2 < x1) std::swap(x1, x2);
			return { std::floorl(x1) + 1, std::ceill(x2) - 1};
			};

		std::string inputName = "Input/Input06.txt";
		std::ifstream input(inputName);

		std::string str;
		std::getline(input, str);
		const auto times = getNums(str.substr(12));
		std::getline(input, str);
		const auto distances = getNums(str.substr(12));

		uint64_t globalMultiplier = 1;
		for (const auto& [time, distance] : std::views::zip(times, distances)) {
			const auto [min, max] = chargeRange(time, distance);
			uint32_t waysToBeat = max - min + 1; // +1, range is inclusive
			
			globalMultiplier *= waysToBeat;
		}

		spdlog::info("Global multiplier is: {}", globalMultiplier);
	}

	inline void Part2() {
		const auto getNums = [](std::string input) {
			const auto noBlackEnd = std::remove_if(input.begin(), input.end(), [](char c) {return std::isblank(c); });
			input.erase(noBlackEnd, input.end());
			std::stringstream stream{ input };
			uint64_t num;
			stream >> num;
			return num;
			};

		const auto chargeRange = [](int64_t max, int64_t record) -> std::pair<uint64_t, uint64_t> {
			const auto delta = max * max - 4 * record;
			auto x1 = (-max - std::sqrt(delta)) / -2;
			auto x2 = (-max + std::sqrt(delta)) / -2;
			if (x1 < 0) x1 = 0; if (x1 > max) x1 = max;
			if (x2 < 0) x2 = 0; if (x2 > max) x2 = max;
			if (x2 < x1) std::swap(x1, x2);
			return { std::floorl(x1) + 1, std::ceill(x2) - 1 };
			};

		std::string inputName = "Input/Input06.txt";
		std::ifstream input(inputName);

		std::string str;
		std::getline(input, str);
		const auto time = getNums(str.substr(12));
		std::getline(input, str);
		const auto distance = getNums(str.substr(12));

		const auto [min, max] = chargeRange(time, distance);
		uint32_t waysToBeat = max - min + 1; // +1, range is inclusive

		spdlog::info("Ways to beat: {}", waysToBeat);
	}

}