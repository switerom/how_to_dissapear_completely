#include "explorer.h"
#include "stdafx.h"
#include "settings.h"
#include "exploreritem.h"
#include "collisiondetection.h"
#include "area.h"
#include "assetmanager.h"
#include "utility.h"

namespace fs = std::filesystem;

Explorer::Explorer(): Area (EXPLORER_MIN_BOUNDS, EXPLORER_VIEWPORT), _currentItems (_explorerAllItems)
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
	_selectRect.setSize(sf::Vector2f(WIDTH, EXPLORER_ITEM_SIZE_Y));

	// Размер окна
	//_windowView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	//_windowView.setViewport(EXPLORER_MIN_BOUNDS);	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	// Размер области файлов
	_itemsView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться

	_itemsView.setViewport(getItemsBounds(EXPLORER_MIN_BOUNDS));	
	//_itemsView.setCenter(WIDTH / 2, HEIGHT / 2);
	
	_isMaximized = false;
	_scrollPos = HEIGHT/2;	// ставим позицию скроллинга в центр экрана, чтобы правильно работала функция setCenter()
	_id = ID::Explorer;

	loadFiles();

	_selectedItem = _explorerAllItems.end();
	//_selectedVisibleItem = _explorerVisibleItems.end();
	finding = false;
}

sf::FloatRect Explorer::getItemsBounds(const sf::FloatRect& explorerBounds)
{
	auto itemsBounds = explorerBounds;
	itemsBounds.top = itemsBounds.top + WINDOW_TOP_RECT / HEIGHT * itemsBounds.height;
	itemsBounds.height = itemsBounds.height - (WINDOW_TOP_RECT / HEIGHT * itemsBounds.height);

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

				_explorerAllItems.emplace_back( ExplorerItem(filename.string(), id));

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

void Explorer::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);	// применяем View, иначе будет на весь экран
	window.draw(_bigRect);
	window.draw(_topRect);

	window.setView(_itemsView);		// Применяем View конкретно для файлов (чтобы правильно работал скроллинг)

	if (!finding)
	{
		if (_selectedItem != _explorerAllItems.end())
			window.draw(_selectRect);

		for (auto& item : _explorerAllItems)
		{
			window.draw(item.getText());
		}
	}
	else
	{
		//if (_selectedItem != _explorerVisibleItems.end())
			window.draw(_selectRect);

		for (auto& item : _explorerVisibleItems)
		{
			window.draw(item.getText());
		}
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
	float itemsBounds = _explorerAllItems.size() * EXPLORER_ITEM_SIZE_Y;

	if (itemsBounds <= HEIGHT)
	{
		return;
	}

	float scrollDist = scrollDelta * EXPLORER_SCROLL_SPEED * dt;

	float newScrollPos = _scrollPos - scrollDist;

	float maxScrollPos = _explorerAllItems.size() * EXPLORER_ITEM_SIZE_Y - HEIGHT / 2;
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
	bool selected { false };
	auto& items = _explorerAllItems;

	if (finding)
	{
		items = _explorerVisibleItems;
	}

	for (auto it{ items.begin() }; it != items.end(); ++it)
	{
		if (isColliding(window, _itemsView, *it))
		{
			_selectedItem = it;

			_selectRect.setPosition(_selectedItem->getItemBounds().left, _selectedItem->getItemBounds().top);

			selected = true;

			return;
		}
	}

	_selectedItem = items.end();
}

std::string Explorer::getCurrentVideo() const
{ 
	if (_selectedItem == _explorerAllItems.end())
		return "";
	else
		return _selectedItem->getText().getString();
}

void Explorer::search(std::wstring wstr)
{
	using json = nlohmann::json;

	// Convert the wstring to lowercase
	std::transform(wstr.begin(), wstr.end(), wstr.begin(), std::towlower);

	std::ifstream f(SEARCH_DIR);
	json data = json::parse(f);
	bool found{ false };
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
					found = true;
					finding = true;
					_selectedItem = _explorerVisibleItems.end();
					//std::cout << "Found!" << "\n";
				}
			}
		}

		if (found)
		{
			for (auto& video : element["videos"])
			{
				std::string filename{ video["video"] };

				for (auto& timestamp : video["timestamps"]) {

					//std::cout << timestamp << " ";

					_explorerVisibleItems.emplace_back(ExplorerItem(filename, id));
					++id;
				}
				//std::cout << "\n";
			}

			return;
		}
	}
}

