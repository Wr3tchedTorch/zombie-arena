#pragma once

#include <SFML/Graphics.hpp>
#include "Zombie.h"

int createBackground(sf::VertexArray& rVertexArray, sf::IntRect arenaBounds);
Zombie* createHorde(int numZombies, sf::IntRect arenaBounds);