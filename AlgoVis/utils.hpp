#pragma once
#include <cstddef>
#include <chrono>
#include <string>
#include <type_traits>

namespace utils {
	template <typename T>
	struct span {
		T* data;
		std::size_t length;

		T& operator[](std::size_t i) {
			return data[i];
		}

		T const& operator[](std::size_t i) const {
			return data[i];
		}
	};

	template <typename TimeUnit>
	std::string getTimeUnit() {
		if (std::is_same<TimeUnit, std::nano>()) {
			return "ns";
		}
		else if (std::is_same<TimeUnit, std::micro>()) {
			return "us";
		}
		else if (std::is_same<TimeUnit, std::milli>()) {
			return "ms";
		}
		else if (std::is_same<TimeUnit, std::ratio<1>>()) {
			return "s";
		}
		else if (std::is_same<TimeUnit, std::ratio<60>>()) {
			return "min";
		}
		else if (std::is_same<TimeUnit, std::ratio<3600>>()) {
			return "h";
		}
	}

	template <typename T>
	void swap(T& a, T& b) {
		T temp{ a };
		a = b;
		b = temp;
	}
}