#include <SFML/Graphics.hpp>
#include "algowatcher.hpp"
#include "sorts.hpp"
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

template <typename T>
void print_vec(std::vector<T> const& vec) {
	std::cout << "{ ";
	for (auto const& e : vec) {
		std::cout << e << ", ";
	}
	std::cout << " }\n";
}

int main() {
	using uint = unsigned;

	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::mt19937 gen{ static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()) };

	std::shuffle(vec.begin(), vec.end(), gen);
	print_vec(vec);

	AlgoWatcher<int> manager(&vec);
	manager.setSort(sort::selection<int>);
	manager.setHandler([](std::vector<int>& data, uint comparisons, uint copies, uint iterations) {
		std::cout << "Data state: ";
		print_vec(data);
		std::cout << "Comparisons: " << comparisons << ", copies: " << copies << ", iterations: " << iterations << "\n\n";
	});

	manager.runAlgo();

	std::cout << "Finally: ";
	print_vec(vec);
	std::cin.get();
}