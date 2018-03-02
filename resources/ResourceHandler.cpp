#include "ResourceHandler.h"

ResourceHandler& ResourceHandler::get() {
	static ResourceHandler handler;
	return handler;
}

ResourceHandler::ResourceHandler() : 
	fonts ("fonts", "ttf"), 
	textures ("textures", "png"), 
	soundBuffers ("sfx", "oog"){

}