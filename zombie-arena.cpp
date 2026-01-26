// zombie-arena.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(vm, "Zombie Arena by Eric", sf::Style::Default, sf::State::Windowed);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);

		window.display();
	}
	
	return 0;
}
