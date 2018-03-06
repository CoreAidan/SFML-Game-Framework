#pragma once

#include <map>
#include <string>
#include <functional>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Binding.h"

template<typename T>
class InputManager
{
public:
	using BindingType = Binding<T>;

	void add(T input, const typename BindingType::Callback& f, bool onPress = false)
	{
		bindings.emplace_back(input, f, onPress);
	}

	void operator()(const sf::Event& e)
	{
		for (auto& key : bindings)
		{
			key(e);
		}
	}

private:
	std::vector<BindingType> bindings;
};