#pragma once
#include <cstddef>

template <typename T>
class AlgoWatcher;

template <typename T>
class AlgoManager {

public:
	struct AlgoData {
		unsigned comparisons{ 0 };
		unsigned copies{ 0 };
		unsigned iteration_count{ 0 };
	};

	AlgoManager(AlgoWatcher<T>* parent) : m_parent{ parent } {}

	void increaseComparisonsCount(unsigned count = 1) { m_data.comparisons += count; }
	void increaseCopiesCount(unsigned count = 1) { m_data.copies += count; }
	void increaseIterationCount(unsigned count = 1) { m_data.iteration_count += count; }

	AlgoData getAlgoData() const { return m_data; }

	void reset() { 
		m_data.comparisons = 0;
		m_data.copies = 0;
		m_data.iteration_count = 0;
	}

private:
	AlgoWatcher<T>* m_parent{ nullptr };
	AlgoData m_data{};
};
