#pragma once

#include "Common.hpp"

namespace Day07 {

	inline void Part1() {
		std::string inputName = "Input/Input07.txt";
		std::ifstream input(inputName);

		using Cards_t = std::array<char, 5>;
		struct Hand {
			Cards_t cards;
			uint32_t bid;
			uint32_t typeStrength;
		};

		const auto getTypeStrength = [](auto cardsInput) {
			std::unordered_multiset<char> cards{ cardsInput.begin(), cardsInput.end() };
			std::sort(cardsInput.begin(), cardsInput.end());
			const auto last = std::unique(cardsInput.begin(), cardsInput.end());
			const auto size = std::distance(cardsInput.begin(), last);
			if (size == 5) return 0;	// High-card
			if (size == 4) return 1; // One-Pair

			if (size == 3) {
				if (std::ranges::none_of(cards, [&](const auto& key) {return cards.count(key) == 3; })) {
					return 2; // Two-pair
				} else {
					return 3; // Three-of-a-kind
				}
			}
			if (size == 2) {
				if (std::ranges::none_of(cards, [&](const auto& key) {return cards.count(key) == 4; })) {
					return 4; // Full-house
				} else {
					return 5; // Four-of-a-kind
				}
			}
			return 6; // Five-of-a-kind
			};
		std::unordered_map<char, uint32_t> cardStrength = {
			{'2', 0}, {'3', 1},{'4', 2},{'5', 3},{'6', 4},{'7', 5},{'8', 6},{'9', 7},
			{'T', 8},{'J', 9},{'Q', 10},{'K', 11},{'A', 12}
		};
		const auto singleCardHandScore = [&](const Cards_t& a, const Cards_t& b) -> bool {
			size_t i = 0;
			while (a[i] == b[i]) ++i;

			return cardStrength.at(a[i]) < cardStrength.at(b[i]);
			};

		std::vector<Hand> hands;

		std::string line;
		while (std::getline(input, line)) {
			Hand hand{};
			std::copy(line.begin(), std::next(line.begin(), 5), hand.cards.begin());
			hand.bid = std::strtoul(line.c_str() + 6, nullptr, 10);
			hand.typeStrength = getTypeStrength(hand.cards);
			hands.push_back(hand);
		}

		std::ranges::stable_sort(hands, singleCardHandScore, &Hand::cards);
		std::ranges::stable_sort(hands, {}, &Hand::typeStrength);

		size_t id = 1;
		uint64_t winnings = std::accumulate(hands.begin(), hands.end(), uint32_t{ 0 }, 
			[&](const uint32_t prev, const Hand& hand) {return prev + hand.bid*(id++); });


		spdlog::info("Winnings: {}", winnings);
	}

	inline void Part2() {
		std::string inputName = "Input/Input07.txt";
		std::ifstream input(inputName);

		using Cards_t = std::array<char, 5>;
		struct Hand {
			Cards_t cards;
			uint32_t bid;
			uint32_t typeStrength;
		};

		const auto getTypeStrength = [](auto cardsInput) {
			const auto jokers = std::ranges::count(cardsInput, 'J');
			const auto noJokersEnd = std::remove(cardsInput.begin(), cardsInput.end(), 'J');

			std::unordered_multiset<char> cards{ cardsInput.begin(), noJokersEnd };
			std::sort(cardsInput.begin(), noJokersEnd);
			const auto last = std::unique(cardsInput.begin(), noJokersEnd);
			const auto size = std::distance(cardsInput.begin(), last) + jokers;

			if (size == 5) {
				if(jokers == 0) return 0;	// High-card
				if (jokers == 1) return 1;
				if (jokers == 2) return 3;
				if (jokers == 3) return 5;
				return 6;
			}
			if (size == 4) {
				if(jokers == 0) return 1; // One-Pair
				if (jokers == 1) return 3;
				if (jokers == 2) return 5;
				return 6;
			}

			if (size == 3) {
				if (std::ranges::none_of(cards, [&](const auto& key) {return cards.count(key) == 3; })) {
					if(jokers == 0)	return 2; // Two-pair
					return 4;
				}
				else {
					if (jokers == 0) return 3; // Three-of-a-kind
					if (jokers == 1) return 5;
					return 6;
				}
			}
			if (size == 2) {
				if (std::ranges::none_of(cards, [&](const auto& key) {return cards.count(key) == 4; })) {
					return 4; // Full-house
				}
				else {
					if(jokers == 0) return 5; // Four-of-a-kind
					return 6;
				}
			}
			return 6; // Five-of-a-kind
			};
		std::unordered_map<char, uint32_t> cardStrength = {
			{'J', 0}, {'2', 1}, {'3', 2},{'4', 3},{'5', 4},{'6', 5},{'7', 6},{'8', 7},{'9', 8},
			{'T', 9},{'Q', 10},{'K', 11},{'A', 12}
		};
		const auto singleCardHandScore = [&](const Cards_t& a, const Cards_t& b) -> bool {
			size_t i = 0;
			while (a[i] == b[i]) ++i;

			return cardStrength.at(a[i]) < cardStrength.at(b[i]);
			};

		std::vector<Hand> hands;

		std::string line;
		while (std::getline(input, line)) {
			Hand hand{};
			std::copy(line.begin(), std::next(line.begin(), 5), hand.cards.begin());
			hand.bid = std::strtoul(line.c_str() + 6, nullptr, 10);
			hand.typeStrength = getTypeStrength(hand.cards);
			hands.push_back(hand);
		}

		std::ranges::stable_sort(hands, singleCardHandScore, &Hand::cards);
		std::ranges::stable_sort(hands, {}, &Hand::typeStrength);

		size_t id = 1;
		uint64_t winnings = std::accumulate(hands.begin(), hands.end(), uint32_t{ 0 },
			[&](const uint32_t prev, const Hand& hand) {return prev + hand.bid * (id++); });


		spdlog::info("Winnings with jokers: {}", winnings);
	}

}