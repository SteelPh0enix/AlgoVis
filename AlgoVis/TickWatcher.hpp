#pragma once
#include <chrono>
#include <iostream>
#include <thread>

///	<summary>
///	Helper class used to manage and synchronize code with tick time
/// <param name="TimeUnit">Time ratio, for example std::milli. Must be lesser than std::ratio<1, 1></param>
/// </summary>
template <typename TimeUnit = std::milli>
class TickWatcher {
	using NumberT = unsigned long long;
	using Timer = std::chrono::high_resolution_clock;
	using Duration = std::chrono::duration<NumberT, TimeUnit>;
	using TimePoint = std::chrono::time_point<Timer>;
public:
	using TimeUnitT = TimeUnit;

	TickWatcher(NumberT tickrate) {
		setTickrate(tickrate);
	}

	/// <summary>
	/// Sets tick rate for further use
	/// </summary>
	/// <param name="hertz">Tick frequency</param>
	void setTickrate(NumberT hertz) {
		double tick_time_seconds = 1. / static_cast<double>(hertz);
		m_tick_time = Duration{ static_cast<NumberT>(tick_time_seconds * static_cast<double>(TimeUnit::den)) };
	}

	/// <summary>
	/// Sets time for a tick
	/// <param name="time">Time, unit as passed in TimeUnit template argument</param>
	/// </summary>
	void setTickTime(NumberT time) {
		m_tick_time = Duration{ time };
	}

	/// <summary>
	/// Gets tick rate (in hertz)
	/// </summary>
	double getTickrate() const {
		return 1. / static_cast<double>(m_tick_time.count() / static_cast<typename Duration::rep>(TimeUnit::den));
	}

	/// <summary>
	/// Gets tick time (in TimeUnit)
	/// </summary>
	NumberT getTickTime() const {
		return m_tick_time.count();
	}

	/// <summary>
	/// Returns bool value indicating if next tick time has exceded
	/// </summary>
	bool shouldTick() const {
		return (Timer::now() - m_last_tick) >= m_tick_time;
	}

	/// <summary>
	/// Recalculates next tick time
	/// </summary>
	void nextTick() {
		m_last_tick = Timer::now();
	}

	/// <summary>
	/// If tick time has happened, calculates next tick time and returns true. If not, returns false.
	/// </summary>
	bool tick() {
		if (shouldTick()) {
			nextTick();
			return true;
		}
		else {
			return false;
		}
	}

	/// <summary>
	/// Blocks current thread for one tick
	/// </summary>
	void waitTick() {
		std::this_thread::sleep_for(m_tick_time);
		nextTick();
	}

	/// <summary>
	/// Blocks current thread for specified amount of ticks
	/// </summary>
	/// <param name="ticks">Amount of tick to sleep for</param>
	void waitTicks(NumberT ticks) {
		for (NumberT i = 0; i < ticks; i++) {
			waitTick();
		}
	}

private:
	Duration m_tick_time{ 0 };
	TimePoint m_last_tick{ Timer::now() };
};

