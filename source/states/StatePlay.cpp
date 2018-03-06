#include "StatePlay.h"

#include "../Game.h"

#include "../input/InputManager.h"

#include <iostream>

std::string test;
sf::CircleShape _shape(100.f);

FPSCounter counter;

InputManager<sf::Keyboard::Key> keyboard;

StatePlay::StatePlay(Game& game): StateBase(game) {
	_shape.setFillColor(sf::Color::Green);
	_shape.setPosition(sf::Vector2f(105.f, 104.f));
	
	sf::RenderWindow& _window = const_cast<sf::RenderWindow&>(_pGame->getWindow());

	keyboard.add(sf::Keyboard::Escape, [&_window](sf::Time) {
		_window.close();
	});
}


void StatePlay::handleEvent(sf::Event e){
	keyboard(e);
}

void StatePlay::handleInput(){
	
}

void StatePlay::update(sf::Time deltaTime){
	counter.update();
}

void StatePlay::fixedUpdate(sf::Time deltaTime){

}

void StatePlay::render(sf::RenderTarget& renderer){
	counter.render(renderer);
	//renderer.draw(shape);
}