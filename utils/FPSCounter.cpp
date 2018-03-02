#include "FPSCounter.h"


#include <iostream>

FPSCounter::FPSCounter()
{	
	_font.loadFromFile("../res/arial.ttf");
	_text.move(10, 10);
	_text.setOutlineColor(sf::Color::Black);
	_text.setFillColor({ 255,255,255 });
	_text.setOutlineThickness(2);
	_text.setCharacterSize(25);
}


void FPSCounter::update()
{
	_frameCount++;

	if (_delayTimer.getElapsedTime().asSeconds() > 0.2)
	{
		_fps = _frameCount / _fpsTimer.restart().asSeconds();
		_frameCount = 0;
		_delayTimer.restart();
	}
}

void FPSCounter::render(sf::RenderTarget& renderer)
{
	_text.setString("FPS: " + std::to_string((int)_fps));
	renderer.draw(_text);
}
