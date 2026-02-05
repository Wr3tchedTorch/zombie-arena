#pragma once
#include <SFML/Graphics.hpp>
#include "PickupType.h"

using sf::Sprite, sf::IntRect, sf::FloatRect;

class Pickup
{
private:
	const int HEALTH_START_VALUE	= 50;
	const int AMMO_START_VALUE		= 12;
	const int START_WAIT_TIME		= 10;
	const int START_SECONDS_TO_LIVE = 5;

	Sprite  m_Sprite;
	IntRect m_ArenaBounds;

	int m_Value;
	PickupType m_Type;

	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

public:
	Pickup(PickupType type);

	const Sprite&	 getSprite() const;
	const FloatRect& getGlobalBounds() const;
	bool isSpawned() const;
	
	void setArenaBounds(IntRect toArenaBounds);
	void spawn();
	void update(float delta);
	void upgrade();
	int  gotIt();
};

