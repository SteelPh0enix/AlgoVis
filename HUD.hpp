#pragma once
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>

class HUD : public sf::Drawable {
 public:
  HUD();

  void updateAlgoInfo(std::string const& name, unsigned long long time,
                      std::string const& unit, std::size_t samples);
  void showTemporaryMessage(std::string const& message);
  void hideTemporaryMessage();

  void updateComparisons(unsigned comparisons);
  void updateCopies(unsigned copies);
  void updateIterationCount(unsigned count);
  void reset();

  void setPosition(float x, float y, float spacing = 5.f);
  void setSize(unsigned charSize);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  sf::Font m_font{};
  sf::Text m_algoInfoText{};
  sf::Text m_comparisonsText{};
  sf::Text m_copiesText{};
  sf::Text m_iterCountText{};

  std::string m_algoInfoString{};

  float m_spacing{5.f};
};
