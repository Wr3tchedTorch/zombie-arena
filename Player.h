#include "SFML/Graphics.hpp"

#pragma once
class Player
{
private:
	const float START_SPEED  = 200.0f;
	const float START_HEALTH = 100.0f;

	sf::Vector2f m_Position;
	sf::Vector2f m_ScreenResolution;
	sf::IntRect  m_ArenaBounds;
	
	sf::Sprite   m_Sprite;

	float m_MaxHealth;
	float m_Health;	
	float m_Speed;
	
	unsigned int m_TileSize;
	
	bool  m_UpPressed	 = false;
	bool  m_DownPressed  = false;
	bool  m_LeftPressed  = false;
	bool  m_RightPressed = false;

	sf::Time m_LastHit;

public:	
	Player(sf::Texture& texture);

	void spawn(sf::IntRect arenaBounds, sf::Vector2f screenResolution, unsigned int tileSize);
	void resetPlayerStats();
	
	bool hit(sf::Time timeHit);
	sf::Time getLastHitTime();

	sf::Sprite getSprite();

	sf::FloatRect getGlobalBounds();
	sf::Vector2f  getCenter();
	float getRotation();

	void update(float delta, sf::Vector2i mousePosition);	

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void stopUp();
	void stopDown();
	void stopLeft();
	void stopRight();

	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	int  getHealth();
};
