#pragma once
#include <cstddef>
#include "../utils.hpp"
#include "SortAlgorithm.hpp"

template <typename T>
class BubbleSort final : public SortAlgorithm<T> {
  using Base = SortAlgorithm<T>;

 public:
  virtual void begin() override {}

  virtual bool step() override {
    if (i < Base::dataSize - 1) {
      for (std::size_t j = 0; j < Base::dataSize - i - 1; j++) {
        if ((*Base::data)[j] > (*Base::data)[j + 1]) {
          utils::swap((*Base::data)[j], (*Base::data)[j + 1]);
          Base::manager->increaseComparisonsCount();
          Base::manager->increaseCopiesCount(3);
          Base::manager->resetHighlighted();
          Base::manager->highlightItem(i, sf::Color(0x45, 0x83, 0xEF));
          Base::manager->highlightItem(j, sf::Color(0xEF, 0xBC, 0x45));
          Base::manager->highlightItem(j + 1, sf::Color(0xEF, 0x7B, 0x45));
        }
      }

      Base::manager->increaseIterationCount();
      i++;
      return true;
    }

    return false;
  }

 private:
  std::size_t i{0};
};
