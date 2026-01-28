// zombie-arena.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "ZombieArena.h"

int main()
{
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	State currentState = State::GAME_OVER;

	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(vm, "Zombie Arena by Eric", sf::Style::Default, sf::State::Fullscreen);
	window.setKeyRepeatEnabled(false);
	sf::Vector2f screenResolution(vm.size);

	sf::View mainView({{0, 0}, {static_cast<float>(vm.size.x), static_cast<float>(vm.size.y)}});

	sf::Texture playerTexture("graphics/player.png");
	Player player(playerTexture);
	
	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;
	sf::IntRect arenaBounds;

	sf::Time gameTimeTotal;
	sf::Clock clock;
	
	while (window.isOpen())
	{		
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
				{
					window.close();
				}
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && currentState == State::PLAYING)
				{
					currentState = State::PAUSED;
				}
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && currentState == State::PAUSED)
				{
					currentState = State::PLAYING;
					clock.restart();
				}
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && currentState == State::GAME_OVER)
				{
					currentState = State::LEVELING_UP;
				}

				if (currentState == State::PLAYING)
				{
				}
			}
		}

		/*
			**************
			Read Input
			**************
		*/

		if (currentState == State::PLAYING)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}

		if (currentState == State::LEVELING_UP)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
			{
				currentState = State::PLAYING;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
			{
				currentState = State::PLAYING;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
			{
				currentState = State::PLAYING;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
			{
				currentState = State::PLAYING;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
			{
				currentState = State::PLAYING;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
			{
				currentState = State::PLAYING;
			}

			if (currentState == State::PLAYING)
			{
				arenaBounds.size	 = { 500, 500 };
				arenaBounds.position = { 0, 0 };

				int tileSize = 50;

				player.spawn(arenaBounds, screenResolution, tileSize);

				clock.restart();
			}
		}
		
		/*
			**************
			Physics/Game logic
			**************
		*/
		if (currentState == State::PLAYING)
		{
			sf::Time deltaTime = clock.restart();
			float delta = deltaTime.asSeconds();

			gameTimeTotal += deltaTime;
			
			mouseScreenPosition = sf::Mouse::getPosition();
			mouseWorldPosition  = window.mapPixelToCoords(mouseScreenPosition, mainView);

			player.update(delta, mouseScreenPosition);

			sf::Vector2f playerPosition(player.getCenter());
			mainView.setCenter(playerPosition);
		}

		/*
			**************
			Draw the scene
			**************
		*/

		if (currentState == State::PLAYING)
		{
			window.clear(sf::Color::Blue);
			window.setView(mainView);

			sf::CircleShape testCircle(32, 32);
			testCircle.setFillColor(sf::Color::Red);
			testCircle.setPosition(sf::Vector2f(arenaBounds.position));			
			window.draw(testCircle);

			sf::Vector2f endCirclePos(arenaBounds.size);
			endCirclePos.x -= 50;
			endCirclePos.y -= 50;
			testCircle.setPosition(endCirclePos);
			window.draw(testCircle);

			window.draw(player.getSprite());
		}
		if (currentState == State::LEVELING_UP)
		{
		}
		if (currentState == State::PAUSED)
		{
		}
		if (currentState == State::GAME_OVER)
		{
		}

		window.display();
	}
	
	return 0;
}
