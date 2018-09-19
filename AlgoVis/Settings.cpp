#include "Settings.hpp"
#include <fstream>

Settings::Settings() {}

Settings& Settings::get() {
	static Settings settings;
	return settings;
}

bool Settings::load(std::string const& filename) {
	std::fstream json_file(filename);
	nlohmann::json json;

	if (!json_file.is_open()) return false;

	json_file >> json;
	
	{
		auto windowSettings = json.at("window");
		m_winDimensions.width = windowSettings.at("width").get<unsigned>();
		m_winDimensions.height = windowSettings.at("height").get<unsigned>();
	}

	{
		auto algosSettings = json.at("algos");
		for (auto it = algosSettings.begin(); it != algosSettings.end(); it++) {
			Settings::AlgoInfo info;

			info.enabled = it->at("enabled").get<bool>();
			info.samplesCount = it->at("samples").get<unsigned>();
			info.sleepTime = it->at("sleep").get<unsigned long long>();

			m_algos.insert({ it.key(), info });
		}
	}

	return true;
}

Settings::WindowDimensions const& Settings::getWindowDimensions() const {
	return m_winDimensions;
}

Settings::Algorithms const& Settings::getAlgorithms() const {
	return m_algos;
}