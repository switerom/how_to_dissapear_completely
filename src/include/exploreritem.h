#pragma once

#include "stdafx.h"

class ExplorerItem
{
public:
	ExplorerItem(const std::string& str, unsigned int id);
	void Init(const std::string& str, unsigned int id);
	const sf::Text& getText() const { return _text; };

	void setSelect(bool select);
	bool _isSelected() const { return _selected; };
	const sf::FloatRect& getItemBounds() const { return _bounds; };

private:
	sf::Text _text;
	unsigned int _id;
	bool _selected;
	sf::FloatRect _bounds;
};
