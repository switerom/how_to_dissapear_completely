﻿#include "explorer.h"
#include "stdafx.h"
#include "settings.h"
#include "exploreritem.h"
#include "collisiondetection.h"
#include "area.h"
#include "assetmanager.h"
#include "utility.h"

namespace fs = std::filesystem;

Explorer::Explorer(): Area (EXPLORER_MIN_BOUNDS, EXPLORER_VIEWPORT)
{
	Init();
}

void Explorer::Init()
{
	// Фон окна
	_bigRect.setFillColor(EXPLORER_BACK_COLOR);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	// Верхняя рамка
	_topRect.setFillColor(WINDOW_FRAME_COLOR);
	_topRect.setSize(sf::Vector2f(WIDTH, WINDOW_TOP_RECT));

	// Выделенный файл
	_selectRect.setFillColor(EXPLORER_SELECT_COLOR);
	_selectRect.setSize(sf::Vector2f(EXPLORER_ITEM_WIDTH, EXPLORER_ITEM_HEIGHT));

	// Размер окна
	//_windowView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	//_windowView.setViewport(EXPLORER_MIN_BOUNDS);	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	// Размер области файлов
	_itemsView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться

	_itemsView.setViewport(getItemsBounds(EXPLORER_MIN_BOUNDS));	
	//_itemsView.setCenter(WIDTH / 2, HEIGHT / 2);
	
	_isMaximized = false;

	_id = ID::Explorer;

	loadFiles();

	_selectedItem = _explorerItems.end();
}

// это нужно переписать, чтобы было в settings.h
sf::FloatRect Explorer::getItemsBounds(const sf::FloatRect& explorerBounds)
{
	auto itemsBounds = explorerBounds;
	itemsBounds.top = itemsBounds.top + (WINDOW_TOP_RECT + SEARCH_RECT_HEIGHT) / HEIGHT * itemsBounds.height;
	itemsBounds.height = itemsBounds.height - ((WINDOW_TOP_RECT + SEARCH_RECT_HEIGHT) / HEIGHT * itemsBounds.height);

	return itemsBounds;
}

void Explorer::loadFiles()
{
	search(START_SEARCH_WORD);
}

void Explorer::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);	// применяем View, иначе будет на весь экран
	window.draw(_bigRect);
	window.draw(_topRect);
	_searchBox.Draw(window);

	window.setView(_itemsView);		// Применяем View конкретно для файлов (чтобы правильно работал скроллинг)

	if (_selectedItem != _explorerItems.end())
		window.draw(_selectRect);

	for (auto& item : _explorerItems)
	{
		item.Draw(window);
	}
}

void Explorer::Update(sf::RenderWindow& window, float dt)
{
}

void Explorer::toggleMaximize()
{
	if (_isMaximized)
	{
		_areaView.setViewport(_minBounds);
		_itemsView.setViewport(getItemsBounds(_minBounds));

		_isMaximized = false;
	}
	else
	{
		_areaView.setViewport(WINDOW_MAX_BOUNDS);
		_itemsView.setViewport(getItemsBounds(WINDOW_MAX_BOUNDS));

		_isMaximized = true;
	}
}

void Explorer::scrollView(float scrollDelta, float dt)
{
	if ((_scroll.maxpos + HEIGHT * 0.5f) <= HEIGHT)
		return;

	float scrollDist = scrollDelta * EXPLORER_SCROLL_SPEED * dt;
	float newpos = _scroll.pos - scrollDist;

	if (newpos > _scroll.maxpos)
		_scroll.pos = _scroll.maxpos;
	else if (newpos < _scroll.minpos)
		_scroll.pos = _scroll.minpos;
	else 
		_scroll.pos = newpos;

	_itemsView.setCenter(WIDTH * 0.5f, _scroll.pos);
}

void Explorer::selectItem(sf::RenderWindow& window)
{
	for (auto it{ _explorerItems.begin() }; it != _explorerItems.end(); ++it)
	{
		if (isColliding(window, _itemsView, *it))
		{
			_selectedItem = it;

			_selectRect.setPosition(_selectedItem->getItemBounds().left, _selectedItem->getItemBounds().top);

			return;
		}
	}

	_selectedItem = _explorerItems.end();
}

std::string Explorer::getCurrentVideo()
{ 
	if (_selectedItem == _explorerItems.end())
		return "";

	std::string vid_name = _selectedItem->getText().getString();

	for (auto& i : _watchedVids)
	{
		std::string watched_vid = i.getText().getString();

		if (watched_vid == vid_name)
		{
			return vid_name;
		}
	}

	auto playTime = _selectedItem->getPlayTime();

	_watchedVids.emplace_back(ExplorerItem(vid_name, _watchedVids.size(), playTime.asSeconds(), true));

	return vid_name;
}

void Explorer::resetScroll()
{
	_scroll.pos = 0.f;
	_itemsView.setCenter(WIDTH * 0.5f, HEIGHT * 0.5f);
}

void Explorer::search(std::wstring wstr)
{
	_explorerItems.clear();
	_selectedItem = _explorerItems.end();
	resetScroll();

	using json = nlohmann::json;

	// Convert the wstring to lowercase
	std::transform(wstr.begin(), wstr.end(), wstr.begin(), std::towlower);

	std::ifstream f(SEARCH_DIR);
	json data = json::parse(f);
	int id{ 0 };
	// Loop over the JSON array
	for (auto& element : data) {

		for (auto& token : element["tokens"])
		{
			if (token.is_string()) 
			{
				// Convert JSON value to std::wstring
				std::wstring wstrToken = convertToWideString(token.get<std::string>());

				if(wstr == wstrToken)
				{
					for (auto& video : element["videos"])
					{
						std::string filename{ video["video"] };

						for (auto& timestamp : video["timestamps"])
						{
							float playtime{ timestamp };

							_explorerItems.emplace_back(ExplorerItem(filename, id, playtime));
							++id;
						}
					}

					_scroll.maxpos = static_cast<int>(_explorerItems.size()) / EXPLORER_ITEM_RAWS * EXPLORER_ITEM_HEIGHT - HEIGHT * 0.5f;

					return;
				}
			}
		}
	}
}

void Explorer::typeInSearchBox(sf::Event& event)
{
	_searchBox.typedOn(event);
}

std::wstring Explorer::getSearchBoxText() const
{
	return _searchBox.getText();
}

bool Explorer::isItemSelected() const
{
	return (_selectedItem == _explorerItems.end()) ? false : true;
}
