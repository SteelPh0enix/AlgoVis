#pragma once
#include <SFML/Graphics.hpp>
#include "HUD.hpp"
#include "TickWatcher.hpp"
#include "ArrayDrawer.hpp"
#include "Settings.hpp"

class Visualizator : public sf::Drawable {
public:
	Visualizator();

	void handleInput(sf::Event e);
	void step();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	HUD m_hud;
	ArrayDrawer m_drawer;
	TickWatcher<std::milli> m_watcher{ 100 };

	bool m_running{ false };
};

