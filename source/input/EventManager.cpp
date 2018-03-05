#include "EventManager.h"

EventManager::EventManager() : _hasFocus(true) { LoadBindings(); }

EventManager::~EventManager() {
	for (auto &itr : _bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding *binding) {
	if (_bindings.find(binding->_name) != _bindings.end())
		return false;

	return _bindings.emplace(binding->_name, binding).second;
}

bool EventManager::RemoveBinding(std::string name) {
	auto itr = _bindings.find(name);
	if (itr == _bindings.end()) { return false; }
	delete itr->second;
	_bindings.erase(itr);
	return true;
}

void EventManager::SetFocus(const bool& focus) { _hasFocus = focus; }

void EventManager::HandleEvent(sf::Event& event) {
	// Handling SFML events.
	for (auto &itr : _bindings) {
		Binding* bind = itr.second;
		for (auto &e_itr : bind->_events) {
			EventType sfmlEvent = (EventType)event.type;
			if (e_itr.first != sfmlEvent) { continue; }
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (e_itr.second._code == event.key.code) {
					// Matching event/keystroke.
					// Increase count.
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (e_itr.second._code == event.mouseButton.button) {
					// Matching event/keystroke.
					// Increase count.
					bind->_details._mouse.x = event.mouseButton.x;
					bind->_details._mouse.y = event.mouseButton.y;
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel) {
					bind->_details._mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->_details._size.x = event.size.width;
					bind->_details._size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->_details._textEntered = event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

void EventManager::Update() {
	if (!_hasFocus) { return; }
	for (auto &itr : _bindings) {
		Binding* bind = itr.second;
		for (auto &e_itr : bind->_events) {
			switch (e_itr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second._code))) {
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second._code))) {
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
				// Up for expansion.
				break;
			}
		}

		if (bind->_events.size() == bind->c) {
			auto callItr = _callbacks.find(bind->_name);
			if (callItr != _callbacks.end()) {
				callItr->second(&bind->_details);
			}
		}
		bind->c = 0;
		bind->_details.Clear();
	}
}

void EventManager::LoadBindings() {
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open()) { std::cout << "! Failed loading keys.cfg." << std::endl; return; }
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { delete bind; bind = nullptr; break; }
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo._code = code;

			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}