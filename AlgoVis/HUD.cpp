#include "HUD.hpp"

HUD::HUD() {
	m_font.loadFromFile("ShareTechMono-Regular.ttf");
	m_algoNameText.setFont(m_font);
	m_comparisonsText.setFont(m_font);
	m_copiesText.setFont(m_font);
	m_iterCountText.setFont(m_font);
	m_sleepDelayText.setFont(m_font);
	
	m_algoNameText.setStyle(sf::Text::Bold);

	m_algoNameText.setFillColor(sf::Color::White);
	m_comparisonsText.setFillColor(sf::Color::White);
	m_copiesText.setFillColor(sf::Color::White);
	m_iterCountText.setFillColor(sf::Color::White);
	m_sleepDelayText.setFillColor(sf::Color::White);

	m_algoNameText.setOutlineThickness(1);
	m_comparisonsText.setOutlineThickness(1);
	m_copiesText.setOutlineThickness(1);
	m_iterCountText.setOutlineThickness(1);
	m_sleepDelayText.setOutlineThickness(1);

	m_algoNameText.setOutlineColor(sf::Color::Black);
	m_comparisonsText.setOutlineColor(sf::Color::Black);
	m_copiesText.setOutlineColor(sf::Color::Black);
	m_iterCountText.setOutlineColor(sf::Color::Black);
	m_sleepDelayText.setOutlineColor(sf::Color::Black);

	reset();
	setPosition(20, 10);
	setSize(30);
}

void HUD::reset() {
	m_algoNameText.setString("No algorithm selected.");
	m_comparisonsText.setString("Comparisons: 0");
	m_copiesText.setString("Copies: 0");
	m_iterCountText.setString("Iterations: 0");
	m_sleepDelayText.setString("Delay: None");
}

void HUD::updateAlgoName(std::string const& name) {
	m_algoNameText.setString(std::string("Algorithm: ") + name);
}

void HUD::updateComparisons(unsigned comparisons) {
	m_comparisonsText.setString(std::string("Comparisons: ") + std::to_string(comparisons));
}

void HUD::updateCopies(unsigned copies) {
	m_copiesText.setString(std::string("Copies: " ) + std::to_string(copies));
}

void HUD::updateIterationCount(unsigned count) {
	m_iterCountText.setString(std::string("Iterations: ") + std::to_string(count));
}

void HUD::setSleepDelay(unsigned long long time, std::string const& unit) {
	m_sleepDelayText.setString(std::string("Delay: ") + std::to_string(time) + unit);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_algoNameText, states);
	target.draw(m_comparisonsText, states);
	target.draw(m_copiesText, states);
	target.draw(m_iterCountText, states);
	target.draw(m_sleepDelayText, states);
}

void HUD::setPosition(float x, float y, float spacing) {
	m_algoNameText.setPosition(x, y);

	y += m_algoNameText.getLocalBounds().height + spacing;
	m_comparisonsText.setPosition(x, y);

	y += m_comparisonsText.getLocalBounds().height + spacing;
	m_copiesText.setPosition(x, y);

	y += m_copiesText.getLocalBounds().height + spacing;
	m_iterCountText.setPosition(x, y);

	y += m_copiesText.getLocalBounds().height + spacing;
	m_sleepDelayText.setPosition(x, y);

	m_spacing = spacing;
}

void HUD::setSize(unsigned charSize) {
	m_algoNameText.setCharacterSize(charSize);
	m_comparisonsText.setCharacterSize(charSize);
	m_copiesText.setCharacterSize(charSize);
	m_iterCountText.setCharacterSize(charSize);
	m_sleepDelayText.setCharacterSize(charSize);

	setPosition(m_algoNameText.getGlobalBounds().left, m_algoNameText.getGlobalBounds().top, m_spacing);
}