#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>
#include "Settings.hpp"
#include "Visualizator.hpp"

int main() {
  try {
    if (!Settings::get().load("settings.json")) {
      std::cerr << "Unable to load settings!\n";
      return 1;
    }
  } catch (std::exception const& e) {
    std::cerr << "Invalid settings JSON: " << e.what() << '\n';
    return 2;
  }

  auto windowDimension = Settings::get().getWindowDimensions();
  sf::RenderWindow mainWindow(
      sf::VideoMode(windowDimension.width, windowDimension.height, 32),
      "AlgoVis", sf::Style::Titlebar | sf::Style::Close);

  Visualizator vis;

  while (mainWindow.isOpen()) {
    sf::Event e;
    while (mainWindow.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        mainWindow.close();
      }
      vis.handleInput(e);
    }

    vis.step();

    mainWindow.clear();
    mainWindow.draw(vis);
    mainWindow.display();
  }
}
