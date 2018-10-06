#pragma once
#include <vector>
#include "../AlgoManager.hpp"

template <typename T>
class SortAlgorithm {
public:
	virtual ~SortAlgorithm() {}

	virtual void begin() = 0;

	// should return "false" at the end of sorting
	virtual bool step() = 0;

	void setData(std::vector<T>* newData) {
		data = newData;
		dataSize = data->size();
	}

	std::vector<T> const& getData() const { return *data; }

	void setManager(AlgoManager<T>* newManager) { manager = newManager; }

protected:
	std::size_t dataSize;
	std::vector<T>* data;
	AlgoManager<T>* manager;
};