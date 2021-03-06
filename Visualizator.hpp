#pragma once
#include <SFML/Graphics.hpp>
#include "AlgoWatcher.hpp"
#include "ArrayDrawer.hpp"
#include "HUD.hpp"
#include "Settings.hpp"
#include "TickWatcher.hpp"

class Visualizator : public sf::Drawable {
  enum class State { Idle, Running, Finished, Paused };

  using DataT = int;
  using TimeT = std::milli;

 public:
  void handleInput(sf::Event e);
  void step();
  bool start();

  bool previousAlgorithm();
  bool nextAlgorithm();

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  bool setToCurrentAlgorithm();
  void generateAndSetData();
  void updateHUD();

  void pause();
  void resume();

  HUD m_hud;
  ArrayDrawer<DataT> m_drawer;
  TickWatcher<TimeT> m_ticker{100};
  AlgoWatcher<DataT> m_algoWatcher{};

  Settings::Algorithms m_algorithms{};
  Settings::Algorithms::iterator m_runningAlgo{};
  State m_state{State::Idle};
};
