#pragma once
#include <SFML/Graphics.hpp>
#include "ZombieTypes.h"

using sf::Vector2f, sf::Sprite, sf::Texture, sf::FloatRect;

class Zombie
{
private:
	const int BLOATER_SPEED = 40;
	const int CHASER_SPEED  = 80;
	const int CRAWLER_SPEED = 20;

	const int BLOATER_HEALTH = 5;
	const int CHASER_HEALTH  = 1;
	const int CRAWLER_HEALTH = 3;

	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	Vector2f m_Position;
	Sprite   m_Sprite;
	
	float m_Speed;
	float m_Health;
	bool  m_Alive;

public:
	Zombie();
	bool hit();
	bool isAlive() const;
	void spawn(Vector2f position, ZombieTypes type, int seed);

	FloatRect getGlobalBounds();

	const Sprite& getSprite();

	void update(float delta, Vector2f playerPosition);
};

