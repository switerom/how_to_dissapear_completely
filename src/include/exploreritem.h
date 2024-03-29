#pragma once

#include "stdafx.h"
#include "settings.h"
#include "assetmanager.h"
#include "utility.h"

class ExplorerItem
{
public:
	ExplorerItem(const std::string& str, unsigned int id, float playTime, bool exists = false);
	void Init(const std::string& str, unsigned int id, float playTime, bool exists);
	const sf::Text& getText() const { return _text; };

	void setSelect(bool select);
	bool _isSelected() const { return _selected; };
	const sf::FloatRect& getItemBounds() const { return _bounds; };
	const sf::Time& getPlayTime() { return _playTime; };
	void Draw(sf::RenderWindow& window) const const;

private:
	void fitPreview(const std::string& filename);
	std::string getPreviewFullPath(std::string filename, float playTime);

	sf::Texture _tex;
	sf::Sprite _spr;
	sf::Text _text;
	unsigned int _id;
	bool _selected;
	sf::FloatRect _bounds;
	sf::Time _playTime;
	sf::Text _timeText;
};
