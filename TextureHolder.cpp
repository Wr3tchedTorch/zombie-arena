#include "TextureHolder.h"

#include <assert.h>
#include <iostream>

TextureHolder* TextureHolder::m_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_Instance == nullptr);
	m_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& fileName)
{
	map<string, Texture> textures = m_Instance->m_Textures;
	
	map<string, Texture>::iterator search = textures.find(fileName);

	if (search == textures.end())
	{
		Texture& newTexture = textures[fileName];
		bool success = newTexture.loadFromFile(fileName);
	}

	return textures[fileName];
}
