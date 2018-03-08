#pragma once

#include <functional>

#include "Widget.h"

namespace gui {
    class TextBox : public gui::Widget {
        public:
            TextBox(std::string& modString);

            void setLabel (const std::string& str);
            void setTexture (const sf::Texture& tex);

            void handleEvent (sf::Event e, const sf::RenderWindow& window) override;
            void render (sf::RenderTarget& renderer) override;
            void setPosition (const sf::Vector2f& pos) override;
            sf::Vector2f getSize() const override;

        private:
            void handleClick    (sf::Event e, const sf::RenderWindow& window);
            void handleTextInput(sf::Event e);

            sf::Vector2f    _position;

            Rectangle       _rect;
            Text            _text;
            Text            _label;
            std::string*    _pModString;

            bool _isActive = false;

    };
}