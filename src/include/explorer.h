#pragma once

#include "stdafx.h"
#include "exploreritem.h"

class Explorer
{
public:
	void Draw(sf::RenderWindow& window);
	void Update(float dt);

	Explorer();
	void Init();

	// Maximize or minimize Explorer window
	void toggleMaximize();

	// To count total number of videos
	void loadFiles();

	sf::FloatRect getTopBoxRect() const;
	const sf::View& getExplorerView() const;

	void scrollView(float scrollDelta);

	sf::FloatRect getItemsBounds(const sf::FloatRect& explorerBounds);

private:
	
	sf::RectangleShape _bigRect;	// заменить это на текстуру из AssetManagera
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera

	sf::View _windowView;
	bool _isMaximized;

	std::list<ExplorerItem> _explorerItems;
	sf::View _itemsView;
	float _scrollPos;
	//std::list<ExItem> _exItems;
	//std::list<ExItem>::iterator _currentItem;
};