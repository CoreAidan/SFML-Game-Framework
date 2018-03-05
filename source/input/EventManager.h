#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {
	EventInfo() { _code = 0; }
	EventInfo(int event) { _code = event; }
	union {
		int _code;
	};
};

struct EventDetails {
	EventDetails(const std::string& bindName)
		: _name(bindName) {
		Clear();
	}
	std::string _name;

	sf::Vector2i _size;
	sf::Uint32 _textEntered;
	sf::Vector2i _mouse;
	int _mouseWheelDelta;
	int _keyCode; // Single key code.

	void Clear() {
		_size = sf::Vector2i(0, 0);
		_textEntered = 0;
		_mouse = sf::Vector2i(0, 0);
		_mouseWheelDelta = 0;
		_keyCode = -1;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding {
	Binding(const std::string& name) : _name(name), _details(name), c(0) {}
	void BindEvent(EventType type, EventInfo info = EventInfo()) {
		_events.emplace_back(type, info);
	}

	Events _events;
	std::string _name;
	int c; // Count of events that are "happening".

	EventDetails _details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager {
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding *binding);
	bool RemoveBinding(std::string name);

	void SetFocus(const bool& focus);

	// Needs to be defined in the header!
	template<class T>
	bool AddCallback(const std::string& name,
		void(T::*l_func)(EventDetails*), T* instance)
	{
		auto temp = std::bind(func, instance, std::placeholders::_1);
		returnm_callbacks.emplace(name, temp).second;
	}

	void RemoveCallback(const std::string& l_name) {
		_callbacks.erase(l_name);
	}

	void HandleEvent(sf::Event& event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* wind = nullptr) {
		return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
	}
private:
	void LoadBindings();

	Bindings _bindings;
	Callbacks _callbacks;
	bool _hasFocus;
};