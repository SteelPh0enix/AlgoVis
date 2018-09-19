#pragma once
#include "json.hpp"
#include <utility>
#include <unordered_map>
#include <string>

class Settings {
public:
	struct AlgoInfo {
		bool enabled{ false };
		unsigned samplesCount{ 0 };
		unsigned long long sleepTime{ 0 };
	};

	struct WindowDimensions {
		unsigned width{ 0 };
		unsigned height{ 0 };
	};

	using Algorithms = std::unordered_map<std::string, AlgoInfo>;

	Settings(Settings&) = delete;
	Settings(Settings&&) = delete;
	Settings& operator=(Settings&) = delete;
	Settings& operator=(Settings&&) = delete;

	static Settings& get();

	bool load(std::string const& filename);

	WindowDimensions const& getWindowDimensions() const;
	Algorithms const& getAlgorithms() const;

protected:
	Settings();

private:
	WindowDimensions m_winDimensions{};
	Algorithms m_algos{};
};

