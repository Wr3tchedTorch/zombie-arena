#include "ZombieArena.h"
#include "Zombie.h"

using sf::Vector2f;

Zombie* createHorde(int numZombies, sf::IntRect arenaBounds)
{
	Zombie* zombies = new Zombie[numZombies];

	int minX = arenaBounds.position.x + 20;
	int minY = arenaBounds.position.y + 20;
	int maxX = arenaBounds.position.x + arenaBounds.size.x - 20;
	int maxY = arenaBounds.position.y + arenaBounds.size.y - 20;

	for (int i = 0; i < numZombies; i++)
	{
		srand(time(0) * i);
		int side = rand() % 4;
		int sides[] = { minX, maxX, minY, maxY };

		Vector2f zombiePosition;
		zombiePosition.x = side <= 1  ? sides[side] : (rand() % maxX) + minX;
		zombiePosition.y = side >  1  ? sides[side] : (rand() % maxY) + minY;

		srand(time(0) * i * 2);
		int typeIndex = rand() % static_cast<int>(ZombieTypes::COUNT);

		ZombieTypes zombieType = static_cast<ZombieTypes>(typeIndex);

		zombies[i].spawn(zombiePosition, zombieType, i);
	}

	return zombies;
}