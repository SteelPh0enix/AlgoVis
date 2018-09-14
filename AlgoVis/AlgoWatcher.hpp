#pragma once
#include <cstdint>
#include <thread>
#include <vector>
#include <chrono>
#include "AlgoManager.hpp"

template <typename T>
class AlgoWatcher {
	using uint = unsigned;

public:
	using SortF = void(std::vector<T>& data, AlgoManager<T>& manager);
	using HandlerF = void(std::vector<T>& data_view, uint comparisons, uint copies, uint iteration_count);

	AlgoWatcher(std::vector<T>* data = nullptr)
		: m_data{ data }
	{}

	void setData(std::vector<T>* data) { m_data = data; }

	void setHandler(HandlerF handler) { 
		m_handler = handler;
	}

	void setSort(SortF sort) {
		m_sort = sort;
	}

	std::vector<T> const& getData() { return *m_data; }

	void runAlgo(unsigned sleep_time = 1) {
		AlgoManager<T> manager(this, sleep_time);
		m_sort(*m_data, manager);
	}

private:
	std::vector<T>* m_data;
	std::function<HandlerF> m_handler;
	std::function<SortF> m_sort;

	friend class AlgoManager<T>;
};

