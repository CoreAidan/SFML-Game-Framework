#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include "../utils/NonCopyable.h"
#include "../utils/NonMoveable.h"

class ResourceHandler : public NonCopyable, public NonMoveable {
public:
	static ResourceHandler& get();

	ResourceManager<sf::Font> fonts;
	ResourceManager<sf::Texture> textures;
	ResourceManager<sf::SoundBuffer> soundBuffers;

private:
	ResourceHandler();
};