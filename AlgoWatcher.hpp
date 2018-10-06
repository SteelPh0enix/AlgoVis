#pragma once
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "AlgoManager.hpp"
#include "Algorithms/SortAlgorithm.hpp"
#include "Algorithms/SortAlgorithmFactory.hpp"

template <typename T>
class AlgoWatcher {
  friend class AlgoManager<T>;

 public:
  void setData(std::vector<T> data) {
    m_data = data;
    m_algo->setData(&m_data);
  }

  bool setSort(std::string const& sort) {
    m_algo = SortAlgorithmFactory::createSort<T>(sort);
    if (!m_algo) return false;

    m_algo->setManager(&m_manager);
    m_manager.reset();
    return true;
  }

  std::vector<T> const& getData() { return m_data; }
  typename AlgoManager<T>::AlgoData getAlgoData() const {
    return m_manager.getAlgoData();
  }

  void start() { m_algo->begin(); }
  bool step() { return m_algo->step(); }

 private:
  std::vector<T> m_data;
  AlgoManager<T> m_manager{this};
  std::unique_ptr<SortAlgorithm<T>> m_algo;
};
