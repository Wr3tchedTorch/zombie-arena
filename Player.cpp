#include "Player.h"
#include <iostream>

Player::Player() : m_Sprite(m_Texture)
{
	bool result = m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setOrigin({ 25.0f, 25.0f });
	
	m_Speed		= START_SPEED;
	m_Health	= START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

void Player::spawn(sf::IntRect arenaBounds, sf::Vector2f screenResolution, unsigned int tileSize)
{
	m_Position.x = arenaBounds.size.x / 2.0f;
	m_Position.y = arenaBounds.size.y / 2.0f;

	m_TileSize = tileSize;

	m_ArenaBounds	   = arenaBounds;
	m_ScreenResolution = screenResolution;
}

void Player::resetPlayerStats()
{
	m_Health	= START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_Speed		= START_SPEED;
}

bool Player::hit(sf::Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 300.0f)
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	return false;
}

sf::Time Player::getLastHitTime()
{
	return m_LastHit;
}

const sf::Sprite& Player::getSprite()
{
	return m_Sprite;
}

sf::FloatRect Player::getGlobalBounds()
{
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation().asDegrees();
}

void Player::update(float delta, sf::Vector2i mousePosition)
{
	int xDirection = m_RightPressed - m_LeftPressed;
	int yDirection = m_DownPressed  - m_UpPressed;

	m_Position.x += m_Speed * xDirection * delta;
	m_Position.y += m_Speed * yDirection * delta;

	m_Sprite.setPosition(m_Position);

	if (m_Position.x > m_ArenaBounds.size.x - m_TileSize)
	{
		m_Position.x = m_ArenaBounds.size.x - m_TileSize;
	}
	else if (m_Position.x > m_ArenaBounds.position.x + m_TileSize)
	{
		m_Position.x = m_ArenaBounds.size.x + m_TileSize;
	}

	if (m_Position.y > m_ArenaBounds.size.y - m_TileSize)
	{
		m_Position.y = m_ArenaBounds.size.y + m_TileSize;
	}
	else if (m_Position.y > m_ArenaBounds.position.y + m_TileSize)
	{
		m_Position.y = m_ArenaBounds.size.y + m_TileSize;
	}

	float deg = (atan2(mousePosition.y - m_ScreenResolution.y / 2,mousePosition.x - m_ScreenResolution.x / 2)* 180) / 3.141;	
	sf::Angle angle = sf::degrees(deg);
	m_Sprite.setRotation(angle);
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::upgradeSpeed()
{
	m_Speed += START_SPEED * .2f;
}

void Player::upgradeHealth()
{
	m_MaxHealth += START_HEALTH * .2f;
}

void Player::increaseHealthLevel(int amount)
{
	m_Health = std::max(m_Health + amount, m_MaxHealth);
}

int Player::getHealth()
{
	return m_Health;
}
