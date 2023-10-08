﻿#include "explorer.h"
#include "stdafx.h"
#include "settings.h"
#include "exploreritem.h"
#include "collisiondetection.h"

namespace fs = std::filesystem;

void Explorer::Init()
{
	// Фон окна
	_bigRect.setFillColor(EXPLORER_BACK_COLOR);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	// Верхняя рамка
	_topRect.setFillColor(EXPLORER_FRAME_COLOR);
	_topRect.setSize(sf::Vector2f(WIDTH, EXPLORER_TOP_RECT));

	// Выделенный файл
	_selectRect.setFillColor(EXPLORER_SELECT_COLOR);
	_selectRect.setSize(sf::Vector2f(WIDTH, EXPLORER_ITEM_SIZE_Y));

	// Размер окна
	_windowView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	_windowView.setViewport(EXPLORER_MIN_BOUNDS);	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	// Размер области файлов
	_itemsView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться

	_itemsView.setViewport(getItemsBounds(EXPLORER_MIN_BOUNDS));	
	//_itemsView.setCenter(WIDTH / 2, HEIGHT / 2);
	
	_isMaximized = false;
	_scrollPos = HEIGHT/2;	// ставим позицию скроллинга в центр экрана, чтобы правильно работала функция setCenter()

	loadFiles();

	if (!_explorerItems.empty()) 
		_selectedItem = _explorerItems.begin();

	_selectedItem->setSelect(true);
}

sf::FloatRect Explorer::getItemsBounds(const sf::FloatRect& explorerBounds)
{
	auto itemsBounds = explorerBounds;
	itemsBounds.top = itemsBounds.top + EXPLORER_TOP_RECT / HEIGHT * itemsBounds.height;
	itemsBounds.height = itemsBounds.height - (EXPLORER_TOP_RECT / HEIGHT * itemsBounds.height);

	return itemsBounds;
}

void Explorer::loadFiles()
{
	fs::path folderPath = VID_DIR;

	unsigned int id{};

	try {
		// Check if the folder exists
		if (fs::exists(folderPath) && fs::is_directory(folderPath)) {

			// Iterate through the directory and create items
			for (const auto& entry : fs::directory_iterator(folderPath)) {

				auto filename = entry.path().filename();

				_explorerItems.emplace_back( ExplorerItem(filename.string(), id));

				++id;
			}
		}
		else {
			std::cout << "Folder does not exist or is not a directory." << std::endl;
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Filesystem error: " << ex.what() << std::endl;
	}
}

Explorer::Explorer()
{
	Init();
}

void Explorer::Draw(sf::RenderWindow& window)
{
	window.setView(_windowView);	// применяем View, иначе будет на весь экран
	window.draw(_bigRect);
	window.draw(_topRect);

	window.setView(_itemsView);		// Применяем View конкретно для файлов (чтобы правильно работал скроллинг)

	window.draw(_selectRect);

	for (auto& item : _explorerItems)
	{
		window.draw(item.getText());
	}
}

void Explorer::Update(float dt)
{
}

void Explorer::toggleMaximize()
{
	if (_isMaximized)
	{
		_windowView.setViewport(EXPLORER_MIN_BOUNDS);
		_itemsView.setViewport(getItemsBounds(EXPLORER_MIN_BOUNDS));

		_isMaximized = false;
	}
	else
	{
		_windowView.setViewport(EXPLORER_MAX_BOUNDS);
		_itemsView.setViewport(getItemsBounds(EXPLORER_MAX_BOUNDS));

		_isMaximized = true;
	}
}

void Explorer::scrollView(float scrollDelta, float dt)
{
	float itemsBounds = _explorerItems.size() * EXPLORER_ITEM_SIZE_Y;

	if (itemsBounds <= HEIGHT)
	{
		return;
	}

	float scrollDist = scrollDelta * EXPLORER_SCROLL_SPEED * dt;

	float newScrollPos = _scrollPos - scrollDist;

	float maxScrollPos = _explorerItems.size() * EXPLORER_ITEM_SIZE_Y - HEIGHT / 2;
	float minScrollPos = HEIGHT / 2;

	if (newScrollPos > maxScrollPos)
	{
		_scrollPos = maxScrollPos;
	}
	else if (newScrollPos < minScrollPos)
	{
		_scrollPos = minScrollPos;
	}
	else 
	{
		_scrollPos = newScrollPos;
	}

	_itemsView.setCenter(WIDTH/2, _scrollPos);
}

void Explorer::selectItem(sf::RenderWindow& window)
{
	for (auto it{ _explorerItems.begin() }; it != _explorerItems.end(); ++it)
	{

	//for (auto& item: _explorerItems)
	//{
		if (isColliding(window, _itemsView, *it))
		{
			_selectedItem = it;
			_selectRect.setPosition(_selectedItem->getItemBounds().left, _selectedItem->getItemBounds().top);
		}
	}
}