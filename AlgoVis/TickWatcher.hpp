#pragma once
#include <chrono>
#include <iostream>

///	<summary>
///	Helper class used to manage and synchronize code with tick time
/// <param name="TimeUnit">Time ratio, for example std::milli. Must be lesser than std::ratio<1, 1></param>
/// </summary>
template <typename TimeUnit = std::milli>
class TickWatcher {
	using Timer = std::chrono::high_resolution_clock;
	using Duration = std::chrono::duration<unsigned, TimeUnit>;
	using TimePoint = std::chrono::time_point<Timer>;
public:
	TickWatcher(unsigned tickrate) {
		setTickrate(tickrate);
	}

	/// <summary>
	/// Sets tick rate for further use
	/// </summary>
	/// <param name="hertz">Tick frequency</param>
	void setTickrate(unsigned hertz) {
		double tick_time_seconds = 1. / static_cast<double>(hertz);
		m_tick_time = Duration{ static_cast<unsigned>(tick_time_seconds * static_cast<double>(TimeUnit::den)) };
	}

	/// <summary>
	/// Sets time for a tick
	/// <param name="time">Time, unit as passed in TimeUnit template argument</param>
	/// </summary>
	void setTickTime(unsigned time) {
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
	unsigned getTickTime() const {
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

private:
	Duration m_tick_time{ 0 };
	TimePoint m_last_tick{ Timer::now() };
};

