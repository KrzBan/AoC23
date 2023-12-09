#pragma once

#include "Common.hpp"

namespace Day09 {

	inline void Part1() {
		const auto parseNumbers = [](const std::string& line) {
			std::vector<int32_t> nums;
			std::stringstream stream{ line };
			int32_t num;
			while (stream >> num) nums.push_back(num);
			return nums;
			};
		const auto diffs = [](const std::vector<int32_t>& nums) {
			std::vector<int32_t> diffs;
			for (const auto& [left, right] : nums | std::views::adjacent<2>) {
				diffs.push_back(right - left);
			}
			return diffs;
			};
		const auto extrapolate = [&](const std::vector<int32_t>& nums) {
			std::vector<std::vector<int32_t>> vecs;
			vecs.push_back(nums);
			while (vecs.back().size() > 1) {
				vecs.push_back(diffs(vecs.back()));
			}
			return std::accumulate(vecs.begin(), vecs.end(), int32_t{ 0 }, [](int32_t sum, const auto& vec) {return sum + vec.back(); });
			};
		std::string inputName = "Input/Input09.txt";
		std::ifstream input(inputName);

		uint32_t sum = 0;
		std::string line;
		while (std::getline(input, line)) {
			const auto nums = parseNumbers(line);
			sum += extrapolate(nums);
		}

		spdlog::info("Sum: {}", sum);
	}

	inline void Part2() {
		const auto parseNumbers = [](const std::string& line) {
			std::vector<int32_t> nums;
			std::stringstream stream{ line };
			int32_t num;
			while (stream >> num) nums.push_back(num);
			return nums;
			};
		const auto diffs = [](const std::vector<int32_t>& nums) {
			std::vector<int32_t> diffs;
			for (const auto& [left, right] : nums | std::views::adjacent<2>) {
				diffs.push_back(right - left);
			}
			return diffs;
			};
		const auto extrapolate = [&](const std::vector<int32_t>& nums) {
			std::vector<std::vector<int32_t>> vecs;
			vecs.push_back(nums);
			while (vecs.back().size() > 1) {
				vecs.push_back(diffs(vecs.back()));
			}
			return std::accumulate(vecs.rbegin(), vecs.rend(), int32_t{ 0 }, [](int32_t sum, const auto& vec) {return vec.front() - sum; });
			};
		std::string inputName = "Input/Input09.txt";
		std::ifstream input(inputName);

		int64_t sum = 0;
		std::string line;
		while (std::getline(input, line)) {
			const auto nums = parseNumbers(line);
			sum += extrapolate(nums);
		}

		spdlog::info("Sum: {}", sum);
	}

}