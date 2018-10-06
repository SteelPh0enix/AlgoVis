#pragma once
#include <memory>
#include <string>
#include "Algorithms.hpp"

template <typename T>
class DummySort final : public SortAlgorithm<T> {
 public:
  virtual void begin() override {}
  virtual bool step() override { return false; }
};

class SortAlgorithmFactory {
 public:
  template <typename T>
  static std::unique_ptr<SortAlgorithm<T>> createSort(std::string const& name) {
    if (name == "selection") return std::make_unique<SelectionSort<T>>();

    return std::make_unique<DummySort<T>>();
  }
};
