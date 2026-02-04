#include "Bullet.h"

Bullet::Bullet() : m_Direction(0, 0)
{
	m_MaxX = 0;
	m_MinX = 0;
	m_MaxY = 0;
	m_MinY = 0;

	m_Shape.setSize(Vector2f(2, 2));
}

bool Bullet::isInFlight() const
{
	return m_InFlight;
}

const RectangleShape& Bullet::getShape() const
{
	return m_Shape;
}

const sf::FloatRect& Bullet::getGlobalBounds() const
{
	return m_Shape.getGlobalBounds();
}

void Bullet::stop()
{
	m_InFlight = false;

}

void Bullet::shoot(Vector2f start, Vector2f target)
{
	m_Position = start;
	m_InFlight = true;

	m_Direction = (target - start).normalized();
	
	float range = 1000;
	m_MaxX = start.x + range;
	m_MinX = start.x - range;
	m_MaxY = start.y + range;
	m_MinY = start.y - range;

	m_Shape.setPosition(m_Position);
}

void Bullet::update(float delta)
{
	m_Position += m_Direction * m_Speed * delta;

	m_Shape.setPosition(m_Position);

	bool outOfBounds = m_Position.x < m_MinX || m_Position.x > m_MaxX ||
					   m_Position.y < m_MinY || m_Position.y > m_MaxY;

	if (outOfBounds)
	{
			m_InFlight = false;
	}
}
