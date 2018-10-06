#include "HUD.hpp"

HUD::HUD() {
  m_font.loadFromFile("./Assets/ShareTechMono-Regular.ttf");
  m_algoInfoText.setFont(m_font);
  m_comparisonsText.setFont(m_font);
  m_copiesText.setFont(m_font);
  m_iterCountText.setFont(m_font);

  m_algoInfoText.setStyle(sf::Text::Bold);

  m_algoInfoText.setFillColor(sf::Color::White);
  m_comparisonsText.setFillColor(sf::Color::White);
  m_copiesText.setFillColor(sf::Color::White);
  m_iterCountText.setFillColor(sf::Color::White);

  m_algoInfoText.setOutlineThickness(1);
  m_comparisonsText.setOutlineThickness(1);
  m_copiesText.setOutlineThickness(1);
  m_iterCountText.setOutlineThickness(1);

  m_algoInfoText.setOutlineColor(sf::Color::Black);
  m_comparisonsText.setOutlineColor(sf::Color::Black);
  m_copiesText.setOutlineColor(sf::Color::Black);
  m_iterCountText.setOutlineColor(sf::Color::Black);

  reset();
  setPosition(20, 10);
  setSize(30);
}

void HUD::reset() {
  m_algoInfoText.setString("No algorithm selected.");
  m_comparisonsText.setString("Comparisons: 0");
  m_copiesText.setString("Copies: 0");
  m_iterCountText.setString("Iterations: 0");
}

void HUD::updateAlgoInfo(std::string const& name, unsigned long long time,
                         std::string const& unit, std::size_t samples) {
  m_algoInfoString =
      std::string(std::string("Algorithm: ") + name + std::string(" [") +
                  std::to_string(samples) + std::string(" elements] [") +
                  std::to_string(time) + unit + std::string(" delay]"));
  m_algoInfoText.setString(m_algoInfoString);
}

void HUD::updateComparisons(unsigned comparisons) {
  m_comparisonsText.setString(std::string("Comparisons: ") +
                              std::to_string(comparisons));
}

void HUD::updateCopies(unsigned copies) {
  m_copiesText.setString(std::string("Copies: ") + std::to_string(copies));
}

void HUD::updateIterationCount(unsigned count) {
  m_iterCountText.setString(std::string("Iterations: ") +
                            std::to_string(count));
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_algoInfoText, states);
  target.draw(m_comparisonsText, states);
  target.draw(m_copiesText, states);
  target.draw(m_iterCountText, states);
}

void HUD::setPosition(float x, float y, float spacing) {
  m_algoInfoText.setPosition(x, y);

  y += m_algoInfoText.getLocalBounds().height + spacing;
  m_comparisonsText.setPosition(x, y);

  y += m_comparisonsText.getLocalBounds().height + spacing;
  m_copiesText.setPosition(x, y);

  y += m_copiesText.getLocalBounds().height + spacing;
  m_iterCountText.setPosition(x, y);

  m_spacing = spacing;
}

void HUD::setSize(unsigned charSize) {
  m_algoInfoText.setCharacterSize(charSize);
  m_comparisonsText.setCharacterSize(charSize);
  m_copiesText.setCharacterSize(charSize);
  m_iterCountText.setCharacterSize(charSize);

  setPosition(m_algoInfoText.getGlobalBounds().left,
              m_algoInfoText.getGlobalBounds().top, m_spacing);
}

void HUD::showTemporaryMessage(std::string const& message) {
  m_algoInfoText.setString(m_algoInfoString + " " + message);
}

void HUD::hideTemporaryMessage() { m_algoInfoText.setString(m_algoInfoString); }
