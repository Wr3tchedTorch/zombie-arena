#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

using sf::Texture;
using std::string, std::map;

class TextureHolder
{
private:
	map<string, Texture> m_Textures;

	static TextureHolder* m_Instance;

public:
	TextureHolder();
	static Texture& GetTexture(string const& fileName);
};

#endif