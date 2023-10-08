#pragma once

#include "stdafx.h"

class Area
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(float dt) = 0;
	virtual void toggleMaximize();

	// Maximize or minimize Explorer window
	Area(const sf::FloatRect& minBounds);
	void Init(const sf::FloatRect& minBounds);

	sf::FloatRect getTopBoxRect() const { return _topRect.getGlobalBounds(); };
	const sf::View& getAreaView() const { return _areaView; };
	bool isMaximized() const { return _isMaximized; };

protected:
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera
	sf::View _areaView;
	bool _isMaximized;
	sf::FloatRect _minBounds;
};