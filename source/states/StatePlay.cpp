#include "StatePlay.h"

#include "../Game.h"

#include <iostream>

std::string test;
sf::CircleShape shape(100.f);

FPSCounter counter;

StatePlay::StatePlay(Game& game): StateBase(game){
	
	shape.setFillColor(sf::Color::Green);
}

void StatePlay::handleEvent(sf::Event e){

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
}