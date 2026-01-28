#include "ZombieArena.h"

int createBackground(sf::VertexArray& rVertexArray, sf::IntRect arenaBounds)
{
	const int TILE_SIZE		   = 50;
	const int TILE_TYPES	   = 3;
	const int VERTICES_IN_TILE = 6;

	const int TILE_COUNT_WIDTH  = arenaBounds.size.x / TILE_SIZE;
	const int TILE_COUNT_HEIGHT = arenaBounds.size.y / TILE_SIZE;

	rVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
	rVertexArray.resize(static_cast<size_t>(TILE_COUNT_WIDTH) * TILE_COUNT_HEIGHT * VERTICES_IN_TILE);

	int currentVertexIndex = 0;

	return TILE_SIZE;
}