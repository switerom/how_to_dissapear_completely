#pragma once

#include "stdafx.h"
#include "settings.h"
#include "assetmanager.h"
#include "utility.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class SearchBox
{
public:
	SearchBox();

	void setSelected(bool isSelected);

	std::wstring getText() const;		//возможно заменить на convertToWideString(_textBox.getString()); 

	void typedOn(sf::Event& input);

	bool isSelected() const { return _isSelected; };

	void Draw(sf::RenderWindow& window) const;

private:
	void inputLogic(int charTyped);
	void deleteLastChar();
	void startSearch() const;

	sf::RectangleShape _searchRect;
	sf::Text _textBox;
	std::wostringstream _text;
	bool _isSelected;
	int _limit;
};