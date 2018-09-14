#pragma once
#include "utils.hpp"
#include "AlgoManager.hpp"

namespace sort {
	template <typename T>
	void selection(std::vector<T>& data, AlgoManager<T>& manager) {
		std::size_t minimalElement{};

		for (std::size_t i{ 0 }; i < data.size() - 1; i++) {
			minimalElement = i;
			manager.increaseCopiesCount();

			for (std::size_t j{ i + 1 }; j < data.size(); j++) {
				if (data[j] < data[minimalElement]) {
					minimalElement = j;
					manager.increaseComparisonsCount();
					manager.increaseCopiesCount();
				}
			}

			utils::swap(data[minimalElement], data[i]);
			manager.increaseCopiesCount(3);
			manager.increaseIterationCount();
			manager.callHandler();
			manager.sleep();
		}
	}
}