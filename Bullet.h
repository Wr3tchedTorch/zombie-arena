#pragma once
#include <SFML/Graphics.hpp>

using sf::RectangleShape, sf::Vector2f;

class Bullet
{
private:
	Vector2f m_Position;
	RectangleShape m_Shape;

	bool  m_InFlight = false;
	float m_Speed	 = 1000;
	Vector2f m_Direction;

	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

public:
	Bullet();

	bool isInFlight() const;
	
	const RectangleShape& getShape() const;
	const sf::FloatRect&  getGlobalBounds() const;
	
	void stop();
	void shoot(Vector2f start, Vector2f target);
	void update(float delta);
};

