#pragma once

#include "stdafx.h"

class Area
{
public:
	enum ID
	{
		Explorer,
		Videoplayer,
		None,
	};

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(sf::RenderWindow& window, float dt) = 0;
	virtual void resetAction() = 0;
	virtual void toggleMaximize();

	Area(const sf::FloatRect& minBounds, const sf::FloatRect& viewport);
	void Init(const sf::FloatRect& minBounds, const sf::FloatRect& viewport);

	sf::FloatRect getTopBoxRect() const { return _topRect.getGlobalBounds(); };
	const sf::View& getAreaView() const { return _areaView; };
	bool isMaximized() const { return _isMaximized; };
	ID getAreaID() const { return _id; };

protected:
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera
	sf::View _areaView;
	bool _isMaximized;
	sf::FloatRect _minBounds;
	ID _id;
};