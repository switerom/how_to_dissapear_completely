#pragma once

#include "stdafx.h"

class Area
{
public:
	// Maximize or minimize Explorer window
	Area(const sf::FloatRect& minBounds);
	void Init(const sf::FloatRect& minBounds);
	void Draw(sf::RenderWindow& window);
	virtual void toggleMaximize();

	sf::FloatRect getTopBoxRect() const { return _topRect.getGlobalBounds(); };
	const sf::View& getAreaView() const { return _areaView; };

protected:
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera
	sf::View _areaView;
	bool _isMaximized;
	sf::FloatRect _minBounds;
};