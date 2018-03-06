#include "Game.h"

#include "states/StatePlay.h"

Game::Game(): _window({ 1280, 720 }, "Game Title"){
	_window.setFramerateLimit(100);
	pushState<StatePlay>(*this);
}

void Game::run(){
	constexpr unsigned TPS = 60;                            //ticks per seconds
	const sf::Time     timePerUpdate = sf::seconds(1.0f / float(TPS));
	unsigned ticks = 0;

	sf::Clock timer;
	auto lastTime = sf::Time::Zero;
	auto lag = sf::Time::Zero;

	while (_window.isOpen() && !_states.empty()) {
		auto& state = getCurrentState();

		//Get times
		auto time = timer.getElapsedTime();
		auto elapsed = time - lastTime;

		lastTime = time;
		lag += elapsed;

		//Real time update
		state.handleInput();
		state.update(elapsed);
		_counter.update();

		//Fixed time update
		while (lag >= timePerUpdate) {
			ticks++;
			lag -= timePerUpdate;
			state.fixedUpdate(elapsed);
		}

		//Render
		_window.clear();
		state.render(_window);
		//_counter.render(_window);
		_window.display();


		//Handle window events
		handleEvent();
		tryPop();
	}
}

void Game::tryPop() {
	if (_shouldPop){
		_states.pop_back();
	}
}

void Game::handleEvent() {
	sf::Event e;

	while (_window.pollEvent(e)) {
		getCurrentState().handleEvent(e);
		switch (e.type) {
		case sf::Event::Closed:
			_window.close();
			break;

		default:
			break;

		}
	}
}

StateBase& Game::getCurrentState() {
	return *_states.back();
}

void Game::popState() {
	_shouldPop = true;
}

const sf::RenderWindow& Game::getWindow() const {
	return _window;
}
