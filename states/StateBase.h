#pragma once

#include <SFML\Graphics.hpp>

#include "../util/NonCopyable.h"

class Game;

class StateBase : public NonCopyable{
public: 
	StateBase(Game& game) : _pGame(&game) {
	}

	virtual ~StateBase() = default;

	virtual void handleEvent(sf::Event e) = 0;
	virtual void handleInput() = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void render(sf::RenderTarget & renderer) = 0;

protected:
	Game* _pGame;
};