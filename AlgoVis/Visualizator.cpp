#include "Visualizator.hpp"
#include <iostream>

Visualizator::Visualizator() {

}

void Visualizator::handleInput(sf::Event e) {
	if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::Space) {
			m_running = !m_running;
		}
	}
}

void Visualizator::step() {
	if (m_running && m_watcher.tick()) {

	}
}

void Visualizator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_hud);
}