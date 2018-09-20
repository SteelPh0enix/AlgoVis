#pragma once
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>

class HUD : public sf::Drawable {

public:
	HUD();

	void updateAlgoName(std::string const& name);
	void updateComparisons(unsigned comparisons);
	void updateCopies(unsigned copies);
	void updateIterationCount(unsigned count);
	void setSleepDelay(unsigned long long time, std::string const& unit);
	void reset();

	void setPosition(float x, float y, float spacing = 5.f);
	void setSize(unsigned charSize);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Font m_font{};
	sf::Text m_algoNameText{};
	sf::Text m_comparisonsText{};
	sf::Text m_copiesText{};
	sf::Text m_iterCountText{};
	sf::Text m_sleepDelayText{};

	float m_spacing{ 5.f };
};

