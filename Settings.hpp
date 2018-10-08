#pragma once
#include <vector>
#include <string>
#include <utility>
#include "json.hpp"

class Settings {
 public:
  struct AlgoInfo {
    std::string name{""};
    bool enabled{false};
    unsigned samplesCount{0};
    unsigned long long sleepTime{0};
  };

  struct WindowDimensions {
    unsigned width{0};
    unsigned height{0};
  };

  using Algorithms = std::vector<AlgoInfo>;

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
