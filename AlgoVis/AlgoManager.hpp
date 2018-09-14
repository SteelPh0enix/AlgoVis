#pragma once
#include <cstddef>

template <typename T>
class AlgoWatcher;

template <typename T>
class AlgoManager {
	using uint = unsigned;

public:
	AlgoManager(AlgoWatcher<T>* parent, unsigned long long sleep_time) :
		m_parent{ parent }, m_comparisons{ 0 }, m_copies{ 0 }, m_iteration_count{ 0 }, m_sleep_time{ sleep_time }
	{}

	void increaseComparisonsCount(uint count = 1) { m_comparisons += count; }
	void increaseCopiesCount(uint count = 1) { m_copies += count; }
	void increaseIterationCount(uint count = 1) { m_iteration_count += count; }

	uint getComparisonsCount() const { return m_comparisons; }
	uint getCopiesCount() const { return m_copies; }
	uint getIterationCount() const { return m_iteration_count; }

	void callHandler() {
		m_parent->m_handler(*(m_parent->m_data), m_comparisons, m_copies, m_iteration_count);
	}

	void sleep() {
		std::this_thread::sleep_for(std::chrono::microseconds(m_sleep_time));
	}

private:
	AlgoWatcher<T>* m_parent;

	uint m_comparisons;
	uint m_copies;
	uint m_iteration_count;

	unsigned long long m_sleep_time;
};
