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

	size_t currentVertexIndex = 0;

	for (int x = 0; x < TILE_COUNT_WIDTH; x++)
	{
		for (int y = 0; y < TILE_COUNT_HEIGHT; y++)
		{
			sf::Vector2f topLeftPosition(TILE_SIZE * x, TILE_SIZE * y);
			rVertexArray[currentVertexIndex + 0].position = topLeftPosition;
			rVertexArray[currentVertexIndex + 1].position = sf::Vector2f({topLeftPosition.x + TILE_SIZE, topLeftPosition.y});
			rVertexArray[currentVertexIndex + 2].position = sf::Vector2f({topLeftPosition.x, topLeftPosition.y + TILE_SIZE});
			
			rVertexArray[currentVertexIndex + 3].position = sf::Vector2f({ topLeftPosition.x + TILE_SIZE, topLeftPosition.y });
			rVertexArray[currentVertexIndex + 4].position = sf::Vector2f({ topLeftPosition.x, topLeftPosition.y + TILE_SIZE });
			rVertexArray[currentVertexIndex + 5].position = sf::Vector2f({ topLeftPosition.x + TILE_SIZE, topLeftPosition.y + TILE_SIZE });
			
			int currentTileTextureType = TILE_TYPES;
			if (x != 0 && x != TILE_COUNT_WIDTH  - 1 &&
				y != 0 && y != TILE_COUNT_HEIGHT - 1)
			{
				srand((int) time(0) + y * x - y);
				currentTileTextureType = rand() % TILE_TYPES;				
			}
			
			sf::Vector2f textureTopLeft({0.0f, static_cast<float>(currentTileTextureType * TILE_SIZE)});
			rVertexArray[currentVertexIndex + 0].texCoords = textureTopLeft;
			rVertexArray[currentVertexIndex + 1].texCoords = sf::Vector2f({ textureTopLeft.x + TILE_SIZE, textureTopLeft.y });
			rVertexArray[currentVertexIndex + 2].texCoords = sf::Vector2f({ textureTopLeft.x, textureTopLeft.y + TILE_SIZE });

			rVertexArray[currentVertexIndex + 3].texCoords = sf::Vector2f({ textureTopLeft.x + TILE_SIZE, textureTopLeft.y });
			rVertexArray[currentVertexIndex + 4].texCoords = sf::Vector2f({ textureTopLeft.x, textureTopLeft.y + TILE_SIZE });
			rVertexArray[currentVertexIndex + 5].texCoords = sf::Vector2f({ textureTopLeft.x + TILE_SIZE, textureTopLeft.y + TILE_SIZE });

			currentVertexIndex += VERTICES_IN_TILE;
		}
	}

	return TILE_SIZE;
}