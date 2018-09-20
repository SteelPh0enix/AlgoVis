#pragma once
#include <cstddef>
#include "utils.hpp"
#include "SortAlgorithm.hpp"

template <typename T>
class SelectionSort final : public SortAlgorithm<T>  {
	using Base = SortAlgorithm<T>;
public:
	virtual void begin() override {
	}

	virtual bool step() override {
		if (i < Base::dataSize - 1) {
			minimalElementIndex = i;
			for (std::size_t j = i + 1; j < Base::dataSize; j++) {
				if ((*Base::data)[j] < (*Base::data)[minimalElementIndex]) {
					Base::manager->increaseComparisonsCount();
					minimalElementIndex = j;
				}
			}

			utils::swap((*Base::data)[minimalElementIndex], (*Base::data)[i]);
			Base::manager->increaseCopiesCount(3);
			Base::manager->increaseIterationCount();
			i++;
			return true;
		}

		return false;
	}

private:
	std::size_t minimalElementIndex{ 0 };
	std::size_t i{ 0 };
};