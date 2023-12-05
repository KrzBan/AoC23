#pragma once

#include "Common.hpp"

namespace Day05 {

	inline void Part1() {
		const auto parseSeeds = [](const std::string& str) {
			std::stringstream stream{ str.substr(7) };
			uint64_t num{};
			std::vector<uint64_t> nums;
			while (stream >> num) {
				nums.push_back(num);
			}
			return nums;
			};
		struct Range{
			uint64_t destinationRange;
			uint64_t sourceRange;
			uint64_t length;
		};
		using Map = std::vector<Range>;
		const auto parseMap = [](std::ifstream& input) -> Map {
			std::string name;
			std::getline(input, name);

			Map ranges;

			std::string line;
			while (std::getline(input, line)) {
				if (line.size() == 0) {
					break;
				}
				uint64_t destStart, sourceStart, length;
				std::stringstream stream{ line };
				stream >> destStart >> sourceStart >> length;
				ranges.push_back({ destStart, sourceStart, length });
			}
			return ranges;
			};
		const auto mapLookup = [](uint64_t input, const Map& map) -> uint64_t {
			for (const auto& range : map) {
				if (input >= range.sourceRange && input < (range.sourceRange + range.length)) {
					return range.destinationRange + (input - range.sourceRange);
				}
			}
			return input;
			};

		std::string inputName = "Input/Input05.txt";
		std::ifstream input(inputName);

		std::string seedsStr;
		std::getline(input, seedsStr);
		const auto seeds = parseSeeds(seedsStr);

		std::getline(input, seedsStr);

		const auto seedToSoilMap = parseMap(input);
		const auto soilToFertilizerMap = parseMap(input);
		const auto fertilizerToWater = parseMap(input);
		const auto waterToLight = parseMap(input);
		const auto lightToTemperature = parseMap(input);
		const auto temperatureToHumidity = parseMap(input);
		const auto humidityToLocation = parseMap(input);

		std::vector<uint64_t> locations;
		for (const auto& seed : seeds) {
			const auto soil = mapLookup(seed, seedToSoilMap);
			const auto fertilizer = mapLookup(soil, soilToFertilizerMap);
			const auto water = mapLookup(fertilizer, fertilizerToWater);
			const auto light = mapLookup(water, waterToLight);
			const auto temperature = mapLookup(light, lightToTemperature);
			const auto humidity = mapLookup(temperature, temperatureToHumidity);
			const auto location = mapLookup(humidity, humidityToLocation);
			locations.push_back(location);
		}

		spdlog::info("Smallest location is: {}", *std::ranges::min_element(locations));
	}

	inline void Part2() {
		struct Range {
			uint64_t start;
			uint64_t length;
		};
		const auto parseSeeds = [](const std::string& str) {
			std::stringstream stream{ str.substr(7) };
			uint64_t start{};
			uint64_t length{};
			std::vector<Range> nums;
			while (stream >> start) {
				stream >> length;
				nums.push_back({ start, length });
			}
			return nums;
			};
		const auto subdivideRanges = [](const std::vector<Range>& ranges, uint64_t size) {
			std::vector<Range> smallerRanges;

			for (const auto& range : ranges) {
				auto start = range.start;
				auto remaining = range.length;
				while (remaining > 0) {
					auto newLength = std::min(size, remaining);
					smallerRanges.push_back({ start, newLength });
					start += newLength;
					remaining -= newLength;
				}
			}
			return smallerRanges;
			};
		struct MapRange {
			uint64_t destinationRange;
			uint64_t sourceRange;
			uint64_t length;
		};
		using Map = std::vector<MapRange>;
		const auto parseMap = [](std::ifstream& input) -> Map {
			std::string name;
			std::getline(input, name);

			Map ranges;

			std::string line;
			while (std::getline(input, line)) {
				if (line.size() == 0) {
					break;
				}
				uint64_t destStart, sourceStart, length;
				std::stringstream stream{ line };
				stream >> destStart >> sourceStart >> length;
				ranges.push_back({ destStart, sourceStart, length });
			}
			return ranges;
			};
		const auto mapLookup = [](uint64_t input, const Map& map) -> uint64_t {
			for (const auto& range : map) {
				if (input >= range.sourceRange && input < (range.sourceRange + range.length)) {
					return range.destinationRange + (input - range.sourceRange);
				}
			}
			return input;
			};

		std::string inputName = "Input/Input05.txt";
		std::ifstream input(inputName);

		std::string seedsStr;
		std::getline(input, seedsStr);
		auto seeds = parseSeeds(seedsStr);
		seeds = subdivideRanges(seeds, 1000);
		std::getline(input, seedsStr);

		const auto seedToSoilMap = parseMap(input);
		const auto soilToFertilizerMap = parseMap(input);
		const auto fertilizerToWater = parseMap(input);
		const auto waterToLight = parseMap(input);
		const auto lightToTemperature = parseMap(input);
		const auto temperatureToHumidity = parseMap(input);
		const auto humidityToLocation = parseMap(input);

		uint64_t minLocation = 999999999999999;
		std::mutex minMutex;
		std::for_each(std::execution::par_unseq,seeds.begin(), seeds.end(), [&](const auto& range) {
			for (auto i = 0; i < range.length; ++i) {
				const auto seed = range.start + i;
				const auto soil = mapLookup(seed, seedToSoilMap);
				const auto fertilizer = mapLookup(soil, soilToFertilizerMap);
				const auto water = mapLookup(fertilizer, fertilizerToWater);
				const auto light = mapLookup(water, waterToLight);
				const auto temperature = mapLookup(light, lightToTemperature);
				const auto humidity = mapLookup(temperature, temperatureToHumidity);
				const auto location = mapLookup(humidity, humidityToLocation);

				if (location < minLocation) {
					std::lock_guard<std::mutex> lg{ minMutex };
					if (location < minLocation) {
						minLocation = location;
					}
				}
			}
		});
		
		spdlog::info("Smallest location is: {}", minLocation);
	}
}