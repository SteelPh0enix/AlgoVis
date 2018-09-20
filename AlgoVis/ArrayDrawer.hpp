#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Settings.hpp"

template <typename T>
class ArrayDrawer : public sf::Drawable {
public:
	ArrayDrawer() {
		m_windowHeight = static_cast<float>(Settings::get().getWindowDimensions().height);
		m_barMaxHeight = m_windowHeight;
	}

	template <typename T>
	void setArray(std::vector<T> const *const vec) {
		m_vec = vec;
		setSamplesCount(vec->size());
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		sf::RectangleShape bar{};
		sf::Vector2f barSize{ m_barWidth, 0 };
		sf::Vector2f barPosition{ 0.f, m_windowHeight - barSize.y };

		bar.setFillColor(sf::Color(0xCC, 0xCC, 0xCC));
		bar.setOutlineThickness(1);
		bar.setOutlineColor(sf::Color(0x50, 0x50, 0x50));

		for (std::size_t i{ 0 }; i < m_samplesCount; i++) {
			barSize.y = (*m_vec)[i] * m_barUnitHeight;
			barPosition.y = m_windowHeight - barSize.y;

			bar.setPosition(barPosition);
			bar.setSize(barSize);

			barPosition.x += m_barWidth + (bar.getOutlineThickness() * 2);

			target.draw(bar);
		}
	}

private:
	void setSamplesCount(std::size_t count) {
		m_samplesCount = count;

		float windowWidth = static_cast<float>(Settings::get().getWindowDimensions().width);

		m_barWidth = windowWidth / static_cast<float>(count);
		m_barWidth -= 2; // for outline

		m_barUnitHeight = m_barMaxHeight / m_samplesCount;
	}

	std::size_t m_samplesCount{ 0 };
	float m_barMaxHeight{ 0 };
	float m_barUnitHeight{ 0 };
	float m_barWidth{ 0 };

	float m_windowHeight{ 0 };
	
	std::vector<T> const* m_vec;
};

