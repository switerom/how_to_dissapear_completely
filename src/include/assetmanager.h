#pragma once
#include "stdafx.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	static sf::Font& getFont(const std::string& filename);
	static sf::Texture& getTexture(const std::string& filename);

private:
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sfe::Movie*> _vids;
	std::map<std::string, sf::Texture> _texs;

	static AssetManager* sInstance;
};

