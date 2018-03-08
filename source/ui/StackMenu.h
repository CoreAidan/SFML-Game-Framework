#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Widget.h"
#include "../utils/NonCopyable.h"

namespace gui
{

	class StackMenu : public NonCopyable
	{
		public:
			StackMenu(const sf::RenderWindow& window);
			StackMenu(const sf::Vector2f& position);

			StackMenu(StackMenu&& other);
			StackMenu& operator =(StackMenu&& other);


			~StackMenu() = default;
			void addWidget(std::unique_ptr<Widget>);

			void handleEvent   (sf::Event e, const sf::RenderWindow& window);
			void render         (sf::RenderTarget& renderer);

		private:
			void initWidget(Widget& w);

			std::vector<std::unique_ptr<Widget>> _widgets;
			sf::RectangleShape _background;

			sf::Vector2f _basePosition;
			sf::Vector2f _baseSize;
	};

}
