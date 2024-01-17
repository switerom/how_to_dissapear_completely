#pragma once

#include "stdafx.h"
#include "area.h"
#include "exploreritem.h"
#include "searchbox.h"

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
	std::string getCurrentVideo();
	void search(std::wstring wstr);
	const sf::Time& getVideoPlayback() const { return _selectedItem->getPlayTime(); };
	bool isSearchBoxSelected() const {	return _searchBox.isSelected(); };
	void typeInSearchBox(sf::Event& event);
	std::wstring getSearchBoxText() const;

private:
	sf::RectangleShape _bigRect;	// заменить это на текстуру из AssetManagera
	sf::RectangleShape _selectRect;	// заменить это на текстуру из AssetManagera
	SearchBox _searchBox;

	std::list<ExplorerItem>::iterator _selectedItem;
	std::list<ExplorerItem> _explorerItems;
	std::list<ExplorerItem> _watchedVids;
	sf::View _itemsView;
	float _scrollPos;
	float _itemsBounds;
};