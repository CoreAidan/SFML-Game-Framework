#include "StatePlay.h"

#include "../Game.h"

#include <iostream>

std::string test;

StatePlay::StatePlay(Game& game): StateBase(game)
{
	
}

void StatePlay::handleEvent(sf::Event e){

}

void StatePlay::handleInput(){

}

void StatePlay::update(sf::Time deltaTime){

}

void StatePlay::fixedUpdate(sf::Time deltaTime){

}

void StatePlay::render(sf::RenderTarget& renderer){
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	renderer.draw(shape);
}