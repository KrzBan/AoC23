#pragma once

#include "Common.hpp"

namespace Day01 {

	inline void Part1() {

		std::ifstream input("Input/Input01.txt");

		const auto isDigit = [](char input) { return (input >= '0' && input <= '9'); };
		const auto digitToInt = [](char digit) -> uint32_t { return digit - '0'; };

		std::string line;

		uint32_t sum = 0;
		while (std::getline(input, line)) {

			const auto numbers = line
				| std::views::filter(isDigit)
				| std::ranges::to<std::vector>();

			if (numbers.size() == 0) continue;

			const auto first = digitToInt(numbers.front());
			const auto second = digitToInt(numbers.back());
			const auto num = first * 10 + second;

			sum += num;
		}

		spdlog::info("Resulting sum is: {}", sum);
	}

	inline void Part2() {
		std::ifstream input("Input/Input01.txt");

		const auto isDigit = [](char input) { return (input > '0' && input <= '9'); };
		const auto digitToInt = [](char digit) -> uint8_t { return digit - '0'; };

		std::unordered_map<std::string, uint8_t> wordsToDigits{
			{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
			{"five", 5}, {"six", 6}, {"seven", 7}, 
			{"eight", 8}, {"nine", 9}
		};

		std::regex spelledDigits{ "1|2|3|4|5|6|7|8|9|one|two|three|four|five|six|seven|eight|nine" };

		uint32_t sum = 0;
		std::string line;
		while (std::getline(input, line)) {

			std::vector<uint8_t> numbers;

			std::smatch result;
			while (std::regex_search(line, result, spelledDigits)) {
				auto matched = result[0].str();

				if (isDigit(matched[0])) {
					numbers.push_back(digitToInt(matched[0]));
				}
				else {
					numbers.push_back(wordsToDigits[matched]);
				}

				line = line.substr(result.prefix().length() + 1);
			}

			if (numbers.size() == 0) continue;

			const auto first = numbers.front();
			const auto second = numbers.back();
			const auto num = first * 10 + second;

			sum += num;
		}

		spdlog::info("Resulting sum is: {}", sum);
	}
}