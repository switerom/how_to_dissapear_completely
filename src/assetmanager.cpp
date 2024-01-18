#include "assetmanager.h"
#include "stdafx.h"
#include "settings.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

AssetManager::~AssetManager()
{
	for (auto& i : _vids)
		delete i.second;

	_vids.clear();
	_fonts.clear();
	_texs.clear();
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

		std::string filepath = FONTS_DIR + filename;

		if (!font.loadFromFile(filepath))
		{
			// Handle font loading error here
			// For example, throw an exception or log an error message
			// You can also return a default font or an empty font object
		}

		return font;
	}
}

const sf::Texture* AssetManager::getTexture(const std::string& filename)
{
	auto& texMap = sInstance->_texs;

	auto pairFound = texMap.find(filename);

	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
		sf::Texture* tex = new sf::Texture();

		if (!tex->loadFromFile(filename))
		{
			tex = nullptr;
			// Handle font loading error here
			// For example, throw an exception or log an error message
			// You can also return a default font or an empty font object
		}

		texMap[filename] = tex;

		return tex;
	}
}