#pragma once

#include "stdafx.h"

enum class AreaID
{
	Videoplayer,
	Explorer,
	None,
};

class Area
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(float dt) = 0;
	virtual void toggleMaximize();

	Area(const sf::FloatRect& minBounds);
	void Init(const sf::FloatRect& minBounds);

	sf::FloatRect getTopBoxRect() const { return _topRect.getGlobalBounds(); };
	const sf::View& getAreaView() const { return _areaView; };
	bool isMaximized() const { return _isMaximized; };
	AreaID getAreaID() const { return _areaID; };

protected:
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera
	sf::View _areaView;
	bool _isMaximized;
	sf::FloatRect _minBounds;
	AreaID _areaID;
};