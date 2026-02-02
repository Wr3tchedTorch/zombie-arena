#include "Zombie.h"
#include <ctime>
#include <cstdlib>
#include "TextureHolder.h"
#include <iostream>

using std::max;

bool Zombie::hit()
{
	m_Health--;
	
	if (m_Health <= 0)
	{
		m_Alive  = false;
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
		m_Speed  = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		break;
	case Chaser:
		m_Speed  = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		break;
	case Crawler:
		m_Speed  = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		break;
	default:
		break;
	}

	srand(time(0) * seed);
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;
	modifier /= 100;

	m_Speed *= modifier;

	m_Position = position;
	m_Sprite.setOrigin({ 25.0f, 25.0f });
	m_Sprite.setPosition(m_Position);
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
	Vector2f direction = positionSubtractionResult.normalized();
	
	float distance = positionSubtractionResult.length();
	if (distance > m_Speed * delta)
	{
		m_Position += direction * m_Speed * delta;
	}
	else
	{
		m_Position = playerPosition;
	}
	
	sf::Angle angle = m_Position.angleTo(playerPosition);

	m_Sprite.setRotation(angle);
	m_Sprite.setPosition(m_Position);
}
