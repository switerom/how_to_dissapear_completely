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

	sf::FloatRect getTopBoxRect() const { return _topRect.getGlobalBounds(); };
	const sf::View& getExplorerView() const { return _windowView; };

	void scrollView(float scrollDelta, float dt);

	sf::FloatRect getItemsBounds(const sf::FloatRect& explorerBounds);

	void selectItem(sf::RenderWindow& window);

private:
	
	sf::RectangleShape _bigRect;	// заменить это на текстуру из AssetManagera
	sf::RectangleShape _topRect;	// заменить это на текстуру из AssetManagera
	sf::RectangleShape _selectRect;	// заменить это на текстуру из AssetManagera

	sf::View _windowView;
	bool _isMaximized;

	std::list<ExplorerItem>::iterator _selectedItem;
	std::list<ExplorerItem> _explorerItems;
	sf::View _itemsView;
	float _scrollPos;
};