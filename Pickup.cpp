#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup(PickupType type) : m_Sprite(TextureHolder::GetTexture("graphics/placeholder_50x50.png"))
{
	switch (type)
	{
	case Health:
		m_Value = HEALTH_START_VALUE;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/health_pickup.png"));
		break;
	case Ammo:
		m_Value = AMMO_START_VALUE;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
		break;
	default:
		break;
	}

	m_Sprite.setOrigin({ 25, 25 });
	
	m_SecondsToLive = START_SECONDS_TO_LIVE;
	m_SecondsToWait = START_WAIT_TIME;
}

const Sprite& Pickup::getSprite() const
{
	return m_Sprite;
}

const FloatRect& Pickup::getGlobalBounds() const
{
	return m_Sprite.getGlobalBounds();
}

bool Pickup::isSpawned() const
{
	return m_Spawned;
}

void Pickup::setArenaBounds(IntRect toArenaBounds)
{
	m_ArenaBounds = toArenaBounds;
	m_ArenaBounds.position.x += 50;
	m_ArenaBounds.position.y += 50;
	m_ArenaBounds.size.x -= 50;
	m_ArenaBounds.size.y -= 50;

	spawn();
}

void Pickup::spawn()
{
	srand(time(0) / static_cast<int>(m_Type));
	int x = (rand() % m_ArenaBounds.size.x) + m_ArenaBounds.position.x;

	srand(time(0) * static_cast<int>(m_Type));
	int y = (rand() % m_ArenaBounds.size.y) + m_ArenaBounds.position.y;

	m_Sprite.setPosition({ x, y });
	m_Spawned = true;
	m_SecondsSinceSpawn = 0;
}

void Pickup::update(float delta)
{
	if (isSpawned())
	{
		m_SecondsSinceSpawn	  += delta;
	}
	else
	{
		m_SecondsSinceDeSpawn += delta;
	}

	if (m_Spawned && m_SecondsSinceSpawn > m_SecondsToLive)
	{
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	if (!m_Spawned && m_SecondsSinceDeSpawn > m_SecondsToWait)
	{
		spawn();
	}
}

void Pickup::upgrade()
{
	if (m_Type == PickupType::Health)
	{
		m_Value += HEALTH_START_VALUE * .5f;
	}
	else if (m_Type == PickupType::Ammo)
	{
		m_Value += AMMO_START_VALUE   * .5f;
	}
	m_SecondsToLive += START_SECONDS_TO_LIVE / 10.0f;
	m_SecondsToWait -= START_WAIT_TIME		 / 10.0f;
}

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}
