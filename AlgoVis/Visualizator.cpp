#include "Visualizator.hpp"
#include <thread>
#include <chrono>
#include <algorithm>
#include <random>
#include "utils.hpp"

void Visualizator::handleInput(sf::Event e) {
	if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::Space) {
			if (m_state == State::Running) {
				pause();
			}
			else if (m_state == State::Paused) {
				resume();
			}
			else if (m_state == State::Idle) {
				start();
			}
		}
	}
}

void Visualizator::step() {
	if (m_ticker.tick()) {
		if (m_state == State::Running) {
			if (m_algoWatcher.step()) {
				updateHUD();
				m_drawer.updateHighlights(m_algoWatcher.getAlgoData().highlighted);
			}
			else {
				m_state = State::Finished;
			}

		} else if (m_state == State::Finished) {
			// Wait 3 seconds
			for (unsigned i = 0; i < 30; i++) {
				while (!m_ticker.tick()) {}
			}

			if (nextAlgorithm()) {
				m_state = State::Running;
			}
			else {
				m_state = State::Idle;
			}
		}
	}
}

bool Visualizator::start() {
	m_algorithms = Settings::get().getAlgorithms();
	m_runningAlgo = m_algorithms.begin();

	if (setToCurrentAlgorithm()) {
		m_state = State::Running;
		return true;
	}

	m_state = State::Idle;
	return false;
}

bool Visualizator::previousAlgorithm() {
	if (m_runningAlgo != m_algorithms.begin()) {
		m_runningAlgo--;
		
		if (setToCurrentAlgorithm()) {
			return true;
		}
	}

	return false;
}

bool Visualizator::nextAlgorithm() {
	auto last_algo = --m_algorithms.end();
	if (m_runningAlgo != last_algo) {
		m_runningAlgo++;

		if (setToCurrentAlgorithm()) {
			return true;
		}
	}

	return false;
}

void Visualizator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_drawer);
	target.draw(m_hud);
}

bool Visualizator::setToCurrentAlgorithm() {
	 bool success = m_algoWatcher.setSort(m_runningAlgo->first);
	 if (success) {
		 m_ticker.setTickTime(m_runningAlgo->second.sleepTime);

		 generateAndSetData();

		 m_hud.reset();
		 m_hud.updateAlgoInfo(m_runningAlgo->first, m_runningAlgo->second.sleepTime, utils::getTimeUnit<TimeT>(), m_runningAlgo->second.samplesCount);

		 m_algoWatcher.start();
	 }

	 return success;
}

void Visualizator::generateAndSetData() {
	std::vector<DataT> data(m_runningAlgo->second.samplesCount);

	int i = 0;
	std::generate(data.begin(), data.end(), [&i]() { return i++; });

	std::mt19937 gen{ static_cast<std::mt19937::result_type>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) };
	std::shuffle(data.begin(), data.end(), gen);

	m_algoWatcher.setData(data);
	m_drawer.setArray(&m_algoWatcher.getData());
}

void Visualizator::updateHUD() {
	auto algoData = m_algoWatcher.getAlgoData();
	m_hud.updateComparisons(algoData.comparisons);
	m_hud.updateCopies(algoData.copies);
	m_hud.updateIterationCount(algoData.iteration_count);
}

void Visualizator::pause() {
	m_hud.showTemporaryMessage("[paused]");
	m_state = State::Paused;
}

void Visualizator::resume() {
	m_hud.hideTemporaryMessage();
	m_state = State::Running;
}