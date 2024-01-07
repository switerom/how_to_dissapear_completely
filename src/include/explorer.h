#pragma once

#include "stdafx.h"
#include "area.h"
#include "exploreritem.h"

class Explorer: public Area
{
public:
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void toggleMaximize() override;

	virtual void Update(sf::RenderWindow& window, float dt) override;

	Explorer();
	void Init();

	// To count total number of videos
	void loadFiles();

	void scrollView(float scrollDelta, float dt);

	sf::FloatRect getItemsBounds(const sf::FloatRect& explorerBounds);
	const sf::View& getItemsView() const { return _itemsView; };

	void selectItem(sf::RenderWindow& window);

	std::string getCurrentVideo() const;

	void search(const std::wstring& wstr);

private:
	
	sf::RectangleShape _bigRect;	// заменить это на текстуру из AssetManagera
	sf::RectangleShape _selectRect;	// заменить это на текстуру из AssetManagera

	std::list<ExplorerItem>::iterator _selectedItem;
	std::list<ExplorerItem> _explorerItems;
	sf::View _itemsView;
	float _scrollPos;
};