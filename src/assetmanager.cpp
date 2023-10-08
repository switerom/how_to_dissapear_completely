#include "assetmanager.h"
#include "stdafx.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Font& AssetManager::getFont(const std::string& filename)
{
	auto& fontMap = sInstance->_fonts;

	auto pairFound = fontMap.find(filename);

	if (pairFound != fontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& font = fontMap[filename];

		if (!font.loadFromFile(filename))
		{
			// Handle font loading error here
			// For example, throw an exception or log an error message
			// You can also return a default font or an empty font object
		}

		return font;
	}
}

sfe::Movie* AssetManager::getVideo(const std::string& filename)
{
	auto& vidMap = sInstance->_vids;
	vidMap.clear();

	auto pairFound = vidMap.find(filename);

	auto& vid = vidMap[filename];

	if (!vid.openFromFile(filename))
	{
		// Handle font loading error here
		// For example, throw an exception or log an error message
		// You can also return a default font or an empty font object
	}

	return &vid;

}

sf::Texture& AssetManager::getTexture(const std::string& filename)
{
	auto& texMap = sInstance->_texs;

	auto pairFound = texMap.find(filename);

	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& tex = texMap[filename];

		if (!tex.loadFromFile(filename))
		{
			// Handle font loading error here
			// For example, throw an exception or log an error message
			// You can also return a default font or an empty font object
		}

		return tex;
	}
}