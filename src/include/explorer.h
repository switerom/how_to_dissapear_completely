#pragma once

#include "stdafx.h"
//#include "ExItem.h"

class Explorer
{
public:
	void Draw(sf::RenderWindow& window);
	void Update(float dt);

	Explorer();
	void Init();

	// Maximize or minimize Explorer window
	void toggleMaximize();

	sf::FloatRect getTopBoxRect() const;

private:
	
	sf::RectangleShape _bigRect;	// заменить это на текстуру из AssetManagera
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera

	sf::View _exView;
	//std::list<ExItem> _exItems;
	//std::list<ExItem>::iterator _currentItem;
};