#pragma once

#include "stdafx.h"

class ExplorerItem
{
public:
	ExplorerItem(const std::string& str, unsigned int id, float playTime);
	void Init(const std::string& str, unsigned int id, float playTime);
	const sf::Text& getText() const { return _text; };

	void setSelect(bool select);
	bool _isSelected() const { return _selected; };
	const sf::FloatRect& getItemBounds() const { return _bounds; };
	const sf::Time& getPlayTime() { return _playTime; };

private:
	sf::Text _text;
	unsigned int _id;
	bool _selected;
	sf::FloatRect _bounds;
	sf::Time _playTime;
};
