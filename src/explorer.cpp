#include "explorer.h"
#include "stdafx.h"
#include "settings.h"
#include "exploreritem.h"

namespace fs = std::filesystem;

void Explorer::Init()
{
	// Фон окна
	_bigRect.setFillColor(sf::Color::Red);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	// Верхняя рамка
	_topRect.setFillColor(sf::Color::Blue);
	_topRect.setSize(sf::Vector2f(WIDTH, EXPLORER_TOP_RECT));

	// Размер окна
	_windowView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	_windowView.setViewport(EXPLORER_MIN_BOUNDS);	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	// Размер области файлов
	_itemsView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться

	_itemsView.setViewport(getItemsBounds(EXPLORER_MIN_BOUNDS));	
	
	_isMaximized = false;
	_scrollPos = 0.f;

	loadFiles();
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

	for (auto& i : _explorerItems)
	{
		window.draw(i.getText());
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

sf::FloatRect Explorer::getTopBoxRect() const
{
	return _topRect.getGlobalBounds();
}

const sf::View& Explorer::getExplorerView() const
{
	return _windowView;
}

void Explorer::scrollView(float scrollDelta)
{
	float scrollDist = scrollDelta * EXPLORER_SCROLL_SPEED;

	// Calculate the new scroll position
	float newScrollPos = _scrollPos - scrollDist;


	float maxScrollPos = HEIGHT - _explorerItems.size() * EXPLORER_ITEM_SIZE_Y;

	if (newScrollPos >= maxScrollPos || newScrollPos < 0.f)
		return;

	_scrollPos = newScrollPos;
	_itemsView.move(0.f, scrollDist);
}