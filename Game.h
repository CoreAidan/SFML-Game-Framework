#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "util/FPSCounter.h"
#include "states/StateBase.h"

class Game {
public:
	Game();

	void run();

	template<typename T, typename... Args>
	void pushState(Args&&... args);

	void popState();

	const sf::RenderWindow& getWindow() const;

private:
	void handleEvent();
	void tryPop();

	//will return a state inheiriting from a base state class
	//for now it will return void
	StateBase& getCurrentState();

	sf::RenderWindow _window;

	//vector to hold states that will be pushed on
	//will hold pointers to classes inheiriting from a base state class
	//for now it will hold ints
	std::vector<std::unique_ptr<StateBase>> _states;

	FPSCounter counter;

	bool _shouldPop = false;
};

template<typename T, typename... Args> void Game::pushState(Args&&... args) {
	_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}