#pragma once

#include "stdafx.h"

class ExplorerItem
{
public:
	ExplorerItem(const std::string& str, unsigned int id);
	void Init(const std::string& str, unsigned int id);
	const sf::Text& getText() const { return _text; };

private:
	sf::Text _text;
	unsigned int _id;
};
