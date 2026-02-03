#include "Zombie.h"
#include <ctime>
#include <cstdlib>
#include "TextureHolder.h"
#include <iostream>

using std::max;

Zombie::Zombie() :
	m_Sprite(TextureHolder::GetTexture("graphics/placeholder_50x50.png"))
{
	m_Speed  = 0;
	m_Health = 0;
	m_Alive  = false;
}

bool Zombie::hit()
{
	m_Health--;
	
	if (m_Health <= 0)
	{
		m_Alive   = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));

		return true;
	}

	return false;
}

bool Zombie::isAlive() const
{
	return m_Alive;
}

void Zombie::spawn(Vector2f position, ZombieTypes type, int seed)
{	
	switch (type)
	{
	case Bloater:
		m_Speed   = BLOATER_SPEED;
		m_Health  = BLOATER_HEALTH;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/bloater.png"));		
		break;
	case Chaser:
		m_Speed   = CHASER_SPEED;
		m_Health  = CHASER_HEALTH;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/chaser.png"));
		break;
	case Crawler:
		m_Speed   = CRAWLER_SPEED;
		m_Health  = CRAWLER_HEALTH;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/crawler.png"));
		break;
	default:
		break;
	}

	sf::Vector2i textureSize = sf::Vector2i(m_Sprite.getTexture().getSize());
	m_Sprite.setTextureRect({ {0, 0}, {textureSize.x, textureSize.y} });

	srand(time(0) * seed);
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;
	modifier /= 100;

	m_Speed *= modifier;

	m_Position = position;
	m_Sprite.setOrigin({ 25.0f, 25.0f });
	m_Sprite.setPosition(m_Position);

	m_Alive = true;
}

FloatRect Zombie::getGlobalBounds()
{
	return m_Sprite.getGlobalBounds();
}

const Sprite& Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float delta, Vector2f playerPosition)
{
	Vector2f positionSubtractionResult = playerPosition - m_Position;
	
	float distance = positionSubtractionResult.length();
	if (distance > m_Speed * delta)
	{
		Vector2f direction = positionSubtractionResult.normalized();
		m_Position += direction * m_Speed * delta;
		
		sf::Angle angle = sf::Vector2f({1, 0}).angleTo(direction);
		m_Sprite.setRotation(angle);
	}
	else
	{
		m_Position = playerPosition;
	}
	
	m_Sprite.setPosition(m_Position);
}
